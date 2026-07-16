from PyQt5.QtWidgets import (
    QDialog, QDialogButtonBox, QFormLayout, QDoubleSpinBox,
    QSpinBox, QComboBox, QLabel, QVBoxLayout, QHBoxLayout,
    QPushButton, QFileDialog, QSlider, QGroupBox, QCheckBox,
    QColorDialog,
)
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QColor
import numpy as np


class _BaseDialog(QDialog):
    def __init__(self, title: str, parent=None):
        super().__init__(parent)
        self.setWindowTitle(title)
        self.setMinimumWidth(320)
        self._form = QFormLayout()
        self._btns = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        self._btns.accepted.connect(self.accept)
        self._btns.rejected.connect(self.reject)
        outer = QVBoxLayout(self)
        outer.addLayout(self._form)
        outer.addWidget(self._btns)

    def _dspin(self, lo, hi, val, step=0.1, dec=2):
        w = QDoubleSpinBox()
        w.setRange(lo, hi)
        w.setValue(val)
        w.setSingleStep(step)
        w.setDecimals(dec)
        return w

    def _ispin(self, lo, hi, val, step=1):
        w = QSpinBox()
        w.setRange(lo, hi)
        w.setValue(val)
        w.setSingleStep(step)
        return w


# ─── Reamostragem ────────────────────────────────────────────────────────────

class ResampleDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Reamostrar Imagem", parent)
        self.scale_h = self._dspin(0.01, 20.0, 1.0, 0.1)
        self.scale_w = self._dspin(0.01, 20.0, 1.0, 0.1)
        self.method = QComboBox()
        self.method.addItems([
            "Vizinho Mais Próximo (manual)",
            "Bilinear (manual)",
            "Bicúbico (OpenCV)",
        ])
        self._form.addRow("Escala Altura:", self.scale_h)
        self._form.addRow("Escala Largura:", self.scale_w)
        self._form.addRow("Método:", self.method)

    def values(self):
        method_map = {
            0: 'manual_nn',
            1: 'manual_bil',
            2: 'bicubic',
        }
        return self.scale_h.value(), self.scale_w.value(), method_map[self.method.currentIndex()]


# ─── Brilho ──────────────────────────────────────────────────────────────────

class BrightnessDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Ajuste de Brilho", parent)
        self.mode = QComboBox()
        self.mode.addItems(["Aditivo RGB", "Multiplicativo RGB", "Canal I (HSI)"])
        self.constant = self._dspin(-255, 255, 30, 5)
        self._form.addRow("Modo:", self.mode)
        self._form.addRow("Constante:", self.constant)

    def values(self):
        modes = ['additive', 'multiplicative', 'hsi']
        return modes[self.mode.currentIndex()], self.constant.value()


# ─── Contraste ───────────────────────────────────────────────────────────────

class NegativeDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Negativo", parent)
        self._form.addRow(QLabel("Aplica s = 255 - r em todos os canais."))

    def values(self):
        return {}


class LogTransformDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Transformação Logarítmica", parent)
        self.c = self._dspin(0.1, 500.0, 255.0 / float(np.log(256)), 1.0)
        self._form.addRow("Constante c:", self.c)
        self._form.addRow(QLabel("g = c·log(1 + f)"))

    def values(self):
        return self.c.value()


class ExpTransformDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Transformação Exponencial", parent)
        self.c = self._dspin(0.1, 20.0, 1.0, 0.5)
        self._form.addRow("Constante c:", self.c)
        self._form.addRow(QLabel("g = (exp(f·c)−1) / (exp(c)−1)"))

    def values(self):
        return self.c.value()


class GammaDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Correção Gamma (Power-Law)", parent)
        self.gamma = self._dspin(0.01, 10.0, 1.0, 0.1)
        self._form.addRow("γ (gamma):", self.gamma)
        self._form.addRow(QLabel("g = c·f^γ   (c normaliza para [0,255])"))

    def values(self):
        return self.gamma.value()


class PiecewiseDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Linear por Partes", parent)
        self.r1 = self._dspin(0, 254, 60, 1)
        self.s1 = self._dspin(0, 255, 0, 1)
        self.r2 = self._dspin(1, 255, 180, 1)
        self.s2 = self._dspin(0, 255, 255, 1)
        self._form.addRow("r1 (entrada):", self.r1)
        self._form.addRow("s1 (saída):", self.s1)
        self._form.addRow("r2 (entrada):", self.r2)
        self._form.addRow("s2 (saída):", self.s2)
        self._form.addRow(QLabel("3 segmentos: [0,r1]→[0,s1], [r1,r2]→[s1,s2], [r2,255]→[s2,255]"))

    def values(self):
        return self.r1.value(), self.s1.value(), self.r2.value(), self.s2.value()


# ─── Limiarização ────────────────────────────────────────────────────────────

class ThresholdGrayDialog(_BaseDialog):
    def __init__(self, preserve=False, parent=None):
        title = "Limiarização – Preservar Original" if preserve else "Limiarização Binária"
        super().__init__(title, parent)
        self.a = self._dspin(0, 254, 100, 1)
        self.b = self._dspin(1, 255, 200, 1)
        self._form.addRow("Limite inferior A:", self.a)
        self._form.addRow("Limite superior B:", self.b)
        hint = "Faixa [A,B] destacada; fora preservado." if preserve else "Pixels em [A,B]→255; resto→0."
        self._form.addRow(QLabel(hint))

    def values(self):
        return self.a.value(), self.b.value()


class ThresholdColorDialog(_BaseDialog):
    def __init__(self, mode: str = 'cube', parent=None):
        title = "Limiarização por Cubo" if mode == 'cube' else "Limiarização por Esfera"
        super().__init__(title, parent)
        self._color = (128, 128, 128)
        self._btn = QPushButton("Escolher Cor de Referência")
        self._btn.clicked.connect(self._pick)
        self._swatch = QLabel("  ")
        self._swatch.setAutoFillBackground(True)
        self._update_swatch()
        row = QHBoxLayout()
        row.addWidget(self._btn)
        row.addWidget(self._swatch)
        self._form.addRow("Cor alvo:", row)
        if mode == 'cube':
            self.param = self._dspin(1, 255, 60, 5)
            self._form.addRow("Largura W:", self.param)
            self._form.addRow(QLabel("|R-r|≤W/2 AND |G-g|≤W/2 AND |B-b|≤W/2"))
        else:
            self.param = self._dspin(1, 442, 60, 5)
            self._form.addRow("Raio R₀:", self.param)
            self._form.addRow(QLabel("dist_euclidiana(pixel, ref) ≤ R₀"))
        self._mode = mode

    def _pick(self):
        col = QColorDialog.getColor(QColor(*self._color), self)
        if col.isValid():
            self._color = (col.red(), col.green(), col.blue())
            self._update_swatch()

    def _update_swatch(self):
        r, g, b = self._color
        p = self._swatch.palette()
        p.setColor(self._swatch.backgroundRole(), QColor(r, g, b))
        self._swatch.setPalette(p)
        self._swatch.setText(f"  ({r},{g},{b})")

    def values(self):
        return self._color, self.param.value()


# ─── Histograma ──────────────────────────────────────────────────────────────

class LocalEqualDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Equalização Local de Histograma", parent)
        self.ksize = self._ispin(3, 51, 11, 2)
        self._form.addRow("Tamanho da janela:", self.ksize)
        self._form.addRow(QLabel("Janela deslizante ksize×ksize.\n⚠ Pode ser lento em imagens grandes."))

    def values(self):
        k = self.ksize.value()
        return k if k % 2 == 1 else k + 1


class HistMatchDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Casamento de Histograma", parent)
        self._ref_path = ""
        btn = QPushButton("Selecionar Imagem de Referência…")
        btn.clicked.connect(self._pick)
        self._lbl = QLabel("Nenhuma selecionada")
        self._form.addRow(btn)
        self._form.addRow(self._lbl)

    def _pick(self):
        path, _ = QFileDialog.getOpenFileName(
            self, "Imagem de Referência", "",
            "Imagens (*.png *.jpg *.jpeg *.bmp *.tif *.tiff)"
        )
        if path:
            self._ref_path = path
            self._lbl.setText(path.split("/")[-1])

    def values(self):
        return self._ref_path


# ─── Filtros ─────────────────────────────────────────────────────────────────

class FilterDialog(_BaseDialog):
    def __init__(self, filter_type: str = 'box', parent=None):
        titles = {'box': 'Filtro Box (Média)', 'gaussian': 'Filtro Gaussiano'}
        super().__init__(titles.get(filter_type, 'Filtro'), parent)
        self._ftype = filter_type

        if filter_type == 'gaussian':
            self.sigma = self._dspin(0.1, 20.0, 1.0, 0.5)
            self._form.addRow("σ (sigma):", self.sigma)
            self._form.addRow(QLabel("Tamanho = ⌈6σ⌉ (ímpar automático)"))
        else:
            self.ksize = self._ispin(3, 101, 5, 2)
            self._form.addRow("Tamanho do kernel:", self.ksize)

        self.padding = QComboBox()
        self.padding.addItems(['reflect', 'replicate', 'zero', 'wrap'])
        self._form.addRow("Padding:", self.padding)

        self.separable = QCheckBox("Usar kernels separáveis (mais rápido)")
        self.separable.setChecked(True)
        self._form.addRow(self.separable)

        self.convolve = QCheckBox("Convolução (vs. Correlação)")
        self._form.addRow(self.convolve)

    def values(self):
        pad = self.padding.currentText()
        sep = self.separable.isChecked()
        conv = self.convolve.isChecked()
        if self._ftype == 'gaussian':
            return self.sigma.value(), pad, sep, conv
        k = self.ksize.value()
        return (k if k % 2 == 1 else k + 1), pad, sep, conv


class MedianDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Filtro da Mediana", parent)
        self.ksize = self._ispin(3, 51, 3, 2)
        self._form.addRow("Tamanho da janela:", self.ksize)
        self._form.addRow(QLabel("Não-linear. Ideal para ruído sal-e-pimenta."))

    def values(self):
        k = self.ksize.value()
        return k if k % 2 == 1 else k + 1


class LaplacianDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Aguçamento Laplaciano", parent)
        self.kernel_type = QComboBox()
        self.kernel_type.addItems(['8-conn', '4-conn', '4-conn+', '8-conn+'])
        self.c = self._dspin(-10.0, 10.0, -1.0, 0.5)
        self.padding = QComboBox()
        self.padding.addItems(['reflect', 'replicate', 'zero'])
        self._form.addRow("Máscara:", self.kernel_type)
        self._form.addRow("Constante c:", self.c)
        self._form.addRow("Padding:", self.padding)
        self._form.addRow(QLabel("g = f + c·∇²f"))

    def values(self):
        return self.kernel_type.currentText(), self.c.value(), self.padding.currentText()


class SobelDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Aguçamento por Gradiente (Sobel)", parent)
        self.c = self._dspin(0.0, 5.0, 0.5, 0.1)
        self.padding = QComboBox()
        self.padding.addItems(['reflect', 'replicate', 'zero'])
        self._form.addRow("Constante c:", self.c)
        self._form.addRow("Padding:", self.padding)
        self._form.addRow(QLabel("g = f + c·√(Gx²+Gy²)"))

    def values(self):
        return self.c.value(), self.padding.currentText()


class UnsharpDialog(_BaseDialog):
    def __init__(self, parent=None):
        super().__init__("Unsharp Masking", parent)
        self.sigma = self._dspin(0.1, 20.0, 2.0, 0.5)
        self.c = self._dspin(0.0, 10.0, 1.0, 0.5)
        self.padding = QComboBox()
        self.padding.addItems(['reflect', 'replicate', 'zero'])
        self._form.addRow("σ suavização:", self.sigma)
        self._form.addRow("Força c:", self.c)
        self._form.addRow("Padding:", self.padding)
        self._form.addRow(QLabel("o = f + c·(f − blur(f))"))

    def values(self):
        return self.sigma.value(), self.c.value(), self.padding.currentText()
