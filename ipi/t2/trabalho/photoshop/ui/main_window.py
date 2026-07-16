import numpy as np
from PyQt5.QtWidgets import (
    QMainWindow, QWidget, QHBoxLayout, QVBoxLayout,
    QLabel, QScrollArea, QAction, QFileDialog, QMessageBox,
    QStatusBar, QToolBar, QSizePolicy, QFrame, QProgressDialog,
    QPushButton,
)
from PyQt5.QtGui import QImage, QPixmap, QKeySequence
from PyQt5.QtCore import Qt, QThread, pyqtSignal

from .histogram_widget import HistogramWidget
from .dialogs import (
    ResampleDialog, BrightnessDialog,
    NegativeDialog, LogTransformDialog, ExpTransformDialog,
    GammaDialog, PiecewiseDialog,
    ThresholdGrayDialog, ThresholdColorDialog,
    LocalEqualDialog, HistMatchDialog,
    FilterDialog, MedianDialog, LaplacianDialog, SobelDialog, UnsharpDialog,
)
from ..utils.image_utils import load_image, save_image, image_info
from ..processing.resampling import nearest_neighbor, bilinear, bicubic
from ..processing.intensity import (
    brightness_additive, brightness_multiplicative, brightness_hsi,
    negative, log_transform, exp_transform, gamma_transform,
    piecewise_linear, threshold_binary, threshold_preserve,
    threshold_color_cube, threshold_color_sphere,
)
from ..processing.histogram_ops import equalize_global, histogram_matching, equalize_local
from ..processing.filters import (
    box_filter, gaussian_filter, median_filter,
    laplacian_sharpen, sobel_sharpen, unsharp_mask,
)

MAX_HISTORY = 20
_THUMB_W, _THUMB_H = 64, 48


# ─── Helpers ─────────────────────────────────────────────────────────────────

def _to_pixmap(img: np.ndarray, w: int = _THUMB_W, h: int = _THUMB_H) -> QPixmap:
    arr = np.clip(img, 0, 255).astype(np.uint8)
    if arr.ndim == 2:
        ih, iw = arr.shape
        qimg = QImage(arr.tobytes(), iw, ih, iw, QImage.Format_Grayscale8)
    else:
        ih, iw = arr.shape[:2]
        qimg = QImage(arr.tobytes(), iw, ih, iw * 3, QImage.Format_RGB888)
    return QPixmap.fromImage(qimg).scaled(w, h, Qt.KeepAspectRatio, Qt.SmoothTransformation)


# ─── Background worker ───────────────────────────────────────────────────────

class _Worker(QThread):
    finished = pyqtSignal(object)
    error = pyqtSignal(str)

    def __init__(self, fn, *args, **kwargs):
        super().__init__()
        self._fn = fn
        self._args = args
        self._kwargs = kwargs

    def run(self):
        try:
            self.finished.emit(self._fn(*self._args, **self._kwargs))
        except Exception as e:
            self.error.emit(str(e))


# ─── History item widget ──────────────────────────────────────────────────────

class HistoryItemWidget(QFrame):
    restore_clicked = pyqtSignal(int)

    _STYLE_CURRENT = (
        "QFrame { border: 2px solid #007acc; border-radius: 4px;"
        " background: #1e3a52; margin: 1px; }"
    )
    _STYLE_PAST = (
        "QFrame { border: 1px solid #3a3a3a; border-radius: 4px;"
        " background: #252526; margin: 1px; }"
        "QFrame:hover { border-color: #555; background: #2d2d2d; }"
    )

    def __init__(self, index: int, img: np.ndarray, label: str,
                 is_current: bool = False, parent=None):
        super().__init__(parent)
        self._index = index
        self.setFixedHeight(70)
        self.setStyleSheet(self._STYLE_CURRENT if is_current else self._STYLE_PAST)

        row = QHBoxLayout(self)
        row.setContentsMargins(5, 4, 5, 4)
        row.setSpacing(7)
        row.setAlignment(Qt.AlignVCenter)

        thumb = QLabel()
        thumb.setFixedSize(_THUMB_W, _THUMB_H)
        thumb.setAlignment(Qt.AlignCenter)
        thumb.setStyleSheet("border: 1px solid #333; background: #1a1a1a;")
        thumb.setPixmap(_to_pixmap(img))
        row.addWidget(thumb, 0, Qt.AlignVCenter)

        col = QVBoxLayout()
        col.setSpacing(2)
        col.setContentsMargins(0, 0, 0, 0)

        badge_text = "● ATUAL" if is_current else f"# {index + 1}"
        badge_color = "#007acc" if is_current else "#666"
        badge = QLabel(badge_text)
        badge.setStyleSheet(
            f"color:{badge_color}; font-size:8px; font-weight:bold; border:none;"
        )
        col.addWidget(badge)

        lbl = QLabel(label)
        lbl.setWordWrap(True)
        lbl.setMaximumWidth(160)
        lbl.setStyleSheet("color:#c8c8c8; font-size:10px; border:none;")
        col.addWidget(lbl)

        if not is_current:
            btn = QPushButton("Restaurar")
            btn.setFixedHeight(18)
            btn.setCursor(Qt.PointingHandCursor)
            btn.setStyleSheet(
                "QPushButton{background:#3d5a80;color:white;border:none;"
                "border-radius:3px;font-size:9px;padding:0 4px;}"
                "QPushButton:hover{background:#007acc;}"
                "QPushButton:pressed{background:#005f99;}"
            )
            btn.clicked.connect(lambda: self.restore_clicked.emit(self._index))
            col.addWidget(btn)

        row.addLayout(col, 1)


# ─── Main Window ─────────────────────────────────────────────────────────────

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self._image: np.ndarray = None
        self._original: np.ndarray = None
        self._filepath: str = None
        self._source_filepath: str = None
        self._zoom: float = 1.0
        self._worker: _Worker = None

        self._history: list = []
        self._history_labels: list = []
        self._redo: list = []
        self._redo_labels: list = []
        self._current_label: str = "Original"

        self.setWindowTitle("PhotoPy – Editor de Imagens")
        self.resize(1260, 780)
        self._build_ui()
        self._build_menus()
        self._build_toolbar()
        self._update_status()

    # ─── UI construction ─────────────────────────────────────────────────────

    def _build_ui(self):
        central = QWidget()
        self.setCentralWidget(central)
        root = QHBoxLayout(central)
        root.setContentsMargins(4, 4, 4, 4)
        root.setSpacing(4)

        self._scroll = QScrollArea()
        self._scroll.setAlignment(Qt.AlignCenter)
        self._scroll.setStyleSheet("background:#2b2b2b;")
        self._canvas = QLabel()
        self._canvas.setAlignment(Qt.AlignCenter)
        self._canvas.setSizePolicy(QSizePolicy.Ignored, QSizePolicy.Ignored)
        self._scroll.setWidget(self._canvas)
        self._scroll.setWidgetResizable(False)
        root.addWidget(self._scroll, stretch=4)

        right = QFrame()
        right.setFrameShape(QFrame.StyledPanel)
        right.setFixedWidth(290)
        rl = QVBoxLayout(right)
        rl.setContentsMargins(4, 4, 4, 4)
        rl.setSpacing(4)

        self._hist_widget = HistogramWidget()
        self._hist_widget.setFixedHeight(215)
        rl.addWidget(self._hist_widget)

        self._info_label = QLabel("Nenhuma imagem carregada")
        self._info_label.setAlignment(Qt.AlignCenter)
        self._info_label.setWordWrap(True)
        self._info_label.setStyleSheet("color:#aaa; font-size:10px;")
        rl.addWidget(self._info_label)

        zoom_row = QHBoxLayout()
        zoom_row.setSpacing(2)
        for txt, fn in [("－", lambda: self._zoom_by(0.8)),
                        ("＋", lambda: self._zoom_by(1.25)),
                        ("Ajustar", self._zoom_fit),
                        ("100%", lambda: self._set_zoom(1.0))]:
            lbl = QLabel(f"<a href='#'>{txt}</a>")
            lbl.linkActivated.connect(lambda _, f=fn: f())
            zoom_row.addWidget(lbl)
        rl.addLayout(zoom_row)

        sep = QFrame()
        sep.setFrameShape(QFrame.HLine)
        sep.setStyleSheet("color:#444;")
        rl.addWidget(sep)

        hist_header = QLabel("Histórico")
        hist_header.setStyleSheet("color:#888; font-size:9px; font-weight:bold;")
        rl.addWidget(hist_header)

        self._hist_scroll = QScrollArea()
        self._hist_scroll.setWidgetResizable(True)
        self._hist_scroll.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        self._hist_scroll.setStyleSheet(
            "QScrollArea { border: none; background: transparent; }"
        )

        self._hist_list_container = QWidget()
        self._hist_list_container.setStyleSheet("background: transparent;")
        self._hist_list_layout = QVBoxLayout(self._hist_list_container)
        self._hist_list_layout.setContentsMargins(0, 0, 0, 0)
        self._hist_list_layout.setSpacing(3)
        self._hist_list_layout.addStretch()

        self._hist_scroll.setWidget(self._hist_list_container)
        rl.addWidget(self._hist_scroll, stretch=1)

        root.addWidget(right)
        self.setStatusBar(QStatusBar())

    def _build_toolbar(self):
        tb = QToolBar("Ferramentas rápidas")
        tb.setMovable(False)
        self.addToolBar(tb)
        for label, fn in [
            ("Abrir",    self._open),
            ("Salvar",   self._save),
            ("Desfazer", self._undo),
            ("Refazer",  self._redo_action),
            ("Resetar",  self._reset),
        ]:
            act = QAction(label, self)
            act.triggered.connect(fn)
            tb.addAction(act)

    def _build_menus(self):
        mb = self.menuBar()

        m_file = mb.addMenu("&Arquivo")
        self._add_action(m_file, "Abrir…",       self._open,    "Ctrl+O")
        self._add_action(m_file, "Salvar",        self._save,    "Ctrl+S")
        self._add_action(m_file, "Salvar Como…",  self._save_as, "Ctrl+Shift+S")
        m_file.addSeparator()
        self._add_action(m_file, "Sair",          self.close,    "Ctrl+Q")

        m_edit = mb.addMenu("&Editar")
        self._add_action(m_edit, "Desfazer",  self._undo,        "Ctrl+Z")
        self._add_action(m_edit, "Refazer",   self._redo_action, "Ctrl+Y")
        m_edit.addSeparator()
        self._add_action(m_edit, "Resetar Imagem Original", self._reset)

        m_res = mb.addMenu("&Reamostrar")
        self._add_action(m_res, "Redimensionar…", self._do_resample)

        m_bri = mb.addMenu("&Brilho")
        self._add_action(m_bri, "Ajuste de Brilho…", self._do_brightness)

        m_con = mb.addMenu("&Contraste")
        self._add_action(m_con, "Negativo",                    self._do_negative)
        self._add_action(m_con, "Transformação Logarítmica…",  self._do_log)
        self._add_action(m_con, "Transformação Exponencial…",  self._do_exp)
        self._add_action(m_con, "Correção Gamma…",             self._do_gamma)
        self._add_action(m_con, "Linear por Partes…",          self._do_piecewise)

        m_thr = mb.addMenu("&Limiarização")
        self._add_action(m_thr, "Binária (cinza)…",            self._do_thresh_binary)
        self._add_action(m_thr, "Preservar Original (cinza)…", self._do_thresh_preserve)
        m_thr.addSeparator()
        self._add_action(m_thr, "Cubo de Cor (RGB)…",          self._do_thresh_cube)
        self._add_action(m_thr, "Esfera de Cor (RGB)…",        self._do_thresh_sphere)

        m_his = mb.addMenu("&Histograma")
        self._add_action(m_his, "Equalização Global",          self._do_eq_global)
        self._add_action(m_his, "Casamento de Histograma…",    self._do_hist_match)
        self._add_action(m_his, "Equalização Local…",          self._do_eq_local)

        m_flt = mb.addMenu("&Filtros")
        sub_smooth = m_flt.addMenu("Suavização")
        self._add_action(sub_smooth, "Box (Média)…", self._do_box)
        self._add_action(sub_smooth, "Gaussiano…",   self._do_gaussian)
        self._add_action(sub_smooth, "Mediana…",     self._do_median)
        sub_sharp = m_flt.addMenu("Aguçamento")
        self._add_action(sub_sharp, "Laplaciano…",       self._do_laplacian)
        self._add_action(sub_sharp, "Gradiente Sobel…",  self._do_sobel)
        self._add_action(sub_sharp, "Unsharp Masking…",  self._do_unsharp)

        m_view = mb.addMenu("&Ver")
        self._add_action(m_view, "Zoom +",   lambda: self._zoom_by(1.25), "Ctrl+=")
        self._add_action(m_view, "Zoom −",   lambda: self._zoom_by(0.8),  "Ctrl+-")
        self._add_action(m_view, "Ajustar",  self._zoom_fit,              "Ctrl+0")
        self._add_action(m_view, "100%",     lambda: self._set_zoom(1.0), "Ctrl+1")

    def _add_action(self, menu, label, slot, shortcut=None):
        act = QAction(label, self)
        if shortcut:
            act.setShortcut(QKeySequence(shortcut))
        act.triggered.connect(slot)
        menu.addAction(act)
        return act

    # ─── Image display ────────────────────────────────────────────────────────

    def _display(self):
        if self._image is None:
            self._canvas.clear()
            return
        img = self._image
        if img.ndim == 2:
            h, w = img.shape
            qimg = QImage(img.tobytes(), w, h, w, QImage.Format_Grayscale8)
        else:
            h, w, _ = img.shape
            qimg = QImage(img.tobytes(), w, h, w * 3, QImage.Format_RGB888)
        px = QPixmap.fromImage(qimg)
        nw, nh = int(w * self._zoom), int(h * self._zoom)
        self._canvas.setPixmap(px.scaled(nw, nh, Qt.KeepAspectRatio, Qt.SmoothTransformation))
        self._canvas.resize(nw, nh)
        self._hist_widget.update_histogram(img)
        self._info_label.setText(image_info(img))
        self._update_status()

    def _update_status(self):
        if self._image is None:
            self.statusBar().showMessage("Nenhuma imagem")
        else:
            h, w = self._image.shape[:2]
            self.statusBar().showMessage(
                f"{self._filepath or 'sem título'}  |  {w}×{h}"
                f"  |  zoom {self._zoom:.0%}  |  histórico: {len(self._history)}"
            )

    # ─── Zoom ─────────────────────────────────────────────────────────────────

    def _zoom_by(self, factor: float):
        self._set_zoom(self._zoom * factor)

    def _set_zoom(self, z: float):
        self._zoom = max(0.05, min(z, 16.0))
        self._display()

    def _zoom_fit(self):
        if self._image is None:
            return
        vw = self._scroll.viewport().width()
        vh = self._scroll.viewport().height()
        h, w = self._image.shape[:2]
        self._set_zoom(min(vw / w, vh / h) * 0.97)

    def wheelEvent(self, event):
        if event.modifiers() & Qt.ControlModifier:
            self._zoom_by(1.15 if event.angleDelta().y() > 0 else 1 / 1.15)
        else:
            super().wheelEvent(event)

    # ─── History panel ────────────────────────────────────────────────────────

    def _rebuild_history_panel(self):
        while self._hist_list_layout.count() > 1:
            item = self._hist_list_layout.takeAt(0)
            if item.widget():
                item.widget().deleteLater()

        insert_pos = 0

        if self._image is not None:
            w = HistoryItemWidget(-1, self._image, self._current_label, is_current=True)
            self._hist_list_layout.insertWidget(insert_pos, w)
            insert_pos += 1

        for i in range(len(self._history) - 1, -1, -1):
            w = HistoryItemWidget(i, self._history[i], self._history_labels[i],
                                  is_current=False)
            w.restore_clicked.connect(self._restore_from_history)
            self._hist_list_layout.insertWidget(insert_pos, w)
            insert_pos += 1

    def _restore_from_history(self, idx: int):
        self._redo.append(self._image.copy())
        self._redo_labels.append(self._current_label)

        for i in range(len(self._history) - 1, idx, -1):
            self._redo.append(self._history[i].copy())
            self._redo_labels.append(self._history_labels[i])

        self._image = self._history[idx].copy()
        self._current_label = self._history_labels[idx]
        self._history = self._history[:idx]
        self._history_labels = self._history_labels[:idx]

        self._display()
        self._rebuild_history_panel()

    # ─── Internal history stack ops ───────────────────────────────────────────

    def _push_history(self, state_label: str):
        if self._image is None:
            return
        self._history.append(self._image.copy())
        self._history_labels.append(state_label)
        if len(self._history) > MAX_HISTORY:
            self._history.pop(0)
            self._history_labels.pop(0)
        self._redo.clear()
        self._redo_labels.clear()

    def _undo(self):
        if not self._history:
            self.statusBar().showMessage("Nada para desfazer.", 2000)
            return
        self._redo.append(self._image.copy())
        self._redo_labels.append(self._current_label)
        self._image = self._history.pop()
        self._current_label = self._history_labels.pop()
        self._display()
        self._rebuild_history_panel()

    def _redo_action(self):
        if not self._redo:
            self.statusBar().showMessage("Nada para refazer.", 2000)
            return
        self._history.append(self._image.copy())
        self._history_labels.append(self._current_label)
        self._image = self._redo.pop()
        self._current_label = self._redo_labels.pop()
        self._display()
        self._rebuild_history_panel()

    def _reset(self):
        if self._original is None:
            return
        self._push_history(self._current_label)
        self._image = self._original.copy()
        self._current_label = "Original"
        self._display()
        self._rebuild_history_panel()

    # ─── File operations ──────────────────────────────────────────────────────

    def _open(self):
        path, _ = QFileDialog.getOpenFileName(
            self, "Abrir Imagem", "",
            "Imagens (*.png *.jpg *.jpeg *.bmp *.tif *.tiff *.gif);;Todos (*)"
        )
        if not path:
            return
        try:
            img = load_image(path)
            self._image = img
            self._original = img.copy()
            self._history.clear()
            self._history_labels.clear()
            self._redo.clear()
            self._redo_labels.clear()
            self._current_label = "Original"
            self._filepath = path
            self._source_filepath = path
            self._zoom = 1.0
            self._zoom_fit()
            self._rebuild_history_panel()
        except Exception as e:
            QMessageBox.critical(self, "Erro", f"Não foi possível abrir a imagem:\n{e}")

    @staticmethod
    def _edited_path(original: str) -> str:
        import os
        base, ext = os.path.splitext(original)
        return f"{base}_editada{ext}"

    def _save(self):
        if self._image is None:
            return
        # Nunca sobrescrever o arquivo original — gera sufixo _editada na 1ª vez
        if self._filepath and self._filepath == self._source_filepath:
            self._filepath = self._edited_path(self._source_filepath)
        if self._filepath:
            try:
                save_image(self._filepath, self._image)
                self.statusBar().showMessage(f"Salvo: {self._filepath}", 3000)
            except Exception as e:
                QMessageBox.critical(self, "Erro", str(e))
        else:
            self._save_as()

    def _save_as(self):
        if self._image is None:
            return
        path, _ = QFileDialog.getSaveFileName(
            self, "Salvar Como", "",
            "PNG (*.png);;JPEG (*.jpg *.jpeg);;BMP (*.bmp);;TIFF (*.tif)"
        )
        if not path:
            return
        try:
            save_image(path, self._image)
            self._filepath = path
            self.statusBar().showMessage(f"Salvo: {path}", 3000)
        except Exception as e:
            QMessageBox.critical(self, "Erro", str(e))

    # ─── Guard + apply ────────────────────────────────────────────────────────

    def _need_image(self) -> bool:
        if self._image is None:
            QMessageBox.warning(self, "Aviso", "Nenhuma imagem carregada.")
            return False
        return True

    def _apply(self, fn, *args, label: str = "Operação", **kwargs):
        if not self._need_image():
            return
        self._push_history(self._current_label)

        progress = QProgressDialog("Processando…", None, 0, 0, self)
        progress.setWindowModality(Qt.WindowModal)
        progress.setCancelButton(None)
        progress.show()

        self._worker = _Worker(fn, self._image, *args, **kwargs)

        def on_done(result):
            progress.close()
            self._image = result
            self._current_label = label
            self._display()
            self._rebuild_history_panel()

        def on_err(msg):
            progress.close()
            self._history.pop()
            self._history_labels.pop()
            QMessageBox.critical(self, "Erro no processamento", msg)

        self._worker.finished.connect(on_done)
        self._worker.error.connect(on_err)
        self._worker.start()

    # ─── Operation handlers ───────────────────────────────────────────────────

    def _do_resample(self):
        if not self._need_image():
            return
        dlg = ResampleDialog(self)
        if dlg.exec_() != ResampleDialog.Accepted:
            return
        sh, sw, mode = dlg.values()
        method_names = {
            'manual_nn': 'Vizinho Mais Próximo',
            'manual_bil': 'Bilinear',
            'bicubic': 'Bicúbico',
        }
        lbl = f"Reamostrar ({method_names.get(mode, mode)})"

        def _fn(img, sh, sw, mode):
            if mode == 'manual_nn':
                return nearest_neighbor(img, sh, sw)
            if mode == 'manual_bil':
                return bilinear(img, sh, sw)
            return bicubic(img, sh, sw)

        self._apply(_fn, sh, sw, mode, label=lbl)

    def _do_brightness(self):
        if not self._need_image():
            return
        dlg = BrightnessDialog(self)
        if dlg.exec_() != BrightnessDialog.Accepted:
            return
        mode, c = dlg.values()
        fn = {'additive': brightness_additive,
              'multiplicative': brightness_multiplicative,
              'hsi': brightness_hsi}[mode]
        mode_lbl = {'additive': 'Aditivo', 'multiplicative': 'Multiplicativo', 'hsi': 'HSI'}[mode]
        self._apply(fn, c, label=f"Brilho {mode_lbl} ({c:+.0f})")

    def _do_negative(self):
        self._apply(lambda img: negative(img), label="Negativo")

    def _do_log(self):
        if not self._need_image():
            return
        dlg = LogTransformDialog(self)
        if dlg.exec_() != LogTransformDialog.Accepted:
            return
        c = dlg.values()
        self._apply(log_transform, c, label=f"Log (c={c:.1f})")

    def _do_exp(self):
        if not self._need_image():
            return
        dlg = ExpTransformDialog(self)
        if dlg.exec_() != ExpTransformDialog.Accepted:
            return
        c = dlg.values()
        self._apply(exp_transform, c, label=f"Exponencial (c={c:.1f})")

    def _do_gamma(self):
        if not self._need_image():
            return
        dlg = GammaDialog(self)
        if dlg.exec_() != GammaDialog.Accepted:
            return
        gamma = dlg.values()
        self._apply(gamma_transform, gamma, label=f"Gamma γ={gamma:.2f}")

    def _do_piecewise(self):
        if not self._need_image():
            return
        dlg = PiecewiseDialog(self)
        if dlg.exec_() != PiecewiseDialog.Accepted:
            return
        r1, s1, r2, s2 = dlg.values()
        self._apply(piecewise_linear, r1, s1, r2, s2, label="Linear por Partes")

    def _do_thresh_binary(self):
        if not self._need_image():
            return
        dlg = ThresholdGrayDialog(preserve=False, parent=self)
        if dlg.exec_() != ThresholdGrayDialog.Accepted:
            return
        a, b = dlg.values()
        self._apply(threshold_binary, a, b, label=f"Limiar Binário [{a:.0f},{b:.0f}]")

    def _do_thresh_preserve(self):
        if not self._need_image():
            return
        dlg = ThresholdGrayDialog(preserve=True, parent=self)
        if dlg.exec_() != ThresholdGrayDialog.Accepted:
            return
        a, b = dlg.values()
        self._apply(threshold_preserve, a, b, label=f"Limiar Preservar [{a:.0f},{b:.0f}]")

    def _do_thresh_cube(self):
        if not self._need_image():
            return
        dlg = ThresholdColorDialog(mode='cube', parent=self)
        if dlg.exec_() != ThresholdColorDialog.Accepted:
            return
        ref, w = dlg.values()
        self._apply(threshold_color_cube, ref, w, label=f"Cubo Cor W={w:.0f}")

    def _do_thresh_sphere(self):
        if not self._need_image():
            return
        dlg = ThresholdColorDialog(mode='sphere', parent=self)
        if dlg.exec_() != ThresholdColorDialog.Accepted:
            return
        ref, r = dlg.values()
        self._apply(threshold_color_sphere, ref, r, label=f"Esfera Cor R={r:.0f}")

    def _do_eq_global(self):
        self._apply(equalize_global, label="Equalização Global")

    def _do_hist_match(self):
        if not self._need_image():
            return
        dlg = HistMatchDialog(self)
        if dlg.exec_() != HistMatchDialog.Accepted:
            return
        ref_path = dlg.values()
        if not ref_path:
            QMessageBox.warning(self, "Aviso", "Nenhuma imagem de referência selecionada.")
            return
        try:
            ref = load_image(ref_path)
        except Exception as e:
            QMessageBox.critical(self, "Erro", str(e))
            return
        self._apply(histogram_matching, ref, label="Casamento Histograma")

    def _do_eq_local(self):
        if not self._need_image():
            return
        dlg = LocalEqualDialog(self)
        if dlg.exec_() != LocalEqualDialog.Accepted:
            return
        ksize = dlg.values()
        self._apply(equalize_local, ksize, label=f"Equalização Local {ksize}×{ksize}")

    def _do_box(self):
        if not self._need_image():
            return
        dlg = FilterDialog(filter_type='box', parent=self)
        if dlg.exec_() != FilterDialog.Accepted:
            return
        ksize, pad, sep, conv = dlg.values()
        self._apply(box_filter, ksize, pad, sep, conv, label=f"Box {ksize}×{ksize}")

    def _do_gaussian(self):
        if not self._need_image():
            return
        dlg = FilterDialog(filter_type='gaussian', parent=self)
        if dlg.exec_() != FilterDialog.Accepted:
            return
        sigma, pad, sep, conv = dlg.values()
        self._apply(gaussian_filter, sigma, pad, sep, conv, label=f"Gaussiano σ={sigma:.1f}")

    def _do_median(self):
        if not self._need_image():
            return
        dlg = MedianDialog(self)
        if dlg.exec_() != MedianDialog.Accepted:
            return
        ksize = dlg.values()
        self._apply(median_filter, ksize, label=f"Mediana {ksize}×{ksize}")

    def _do_laplacian(self):
        if not self._need_image():
            return
        dlg = LaplacianDialog(self)
        if dlg.exec_() != LaplacianDialog.Accepted:
            return
        ktype, c, pad = dlg.values()
        self._apply(laplacian_sharpen, ktype, c, pad, label=f"Laplaciano {ktype}")

    def _do_sobel(self):
        if not self._need_image():
            return
        dlg = SobelDialog(self)
        if dlg.exec_() != SobelDialog.Accepted:
            return
        c, pad = dlg.values()
        self._apply(sobel_sharpen, c, pad, label=f"Sobel c={c:.1f}")

    def _do_unsharp(self):
        if not self._need_image():
            return
        dlg = UnsharpDialog(self)
        if dlg.exec_() != UnsharpDialog.Accepted:
            return
        sigma, c, pad = dlg.values()
        self._apply(unsharp_mask, sigma, c, pad, label=f"Unsharp σ={sigma:.1f} c={c:.1f}")
