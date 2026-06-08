import numpy as np
from PyQt5.QtWidgets import QWidget, QVBoxLayout
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure


class HistogramWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setMinimumWidth(260)
        self.setMinimumHeight(200)
        self._fig = Figure(figsize=(3, 2.5), tight_layout=True)
        self._canvas = FigureCanvas(self._fig)
        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.addWidget(self._canvas)

    def update_histogram(self, img: np.ndarray) -> None:
        self._fig.clear()
        ax = self._fig.add_subplot(111)
        ax.set_title("Histograma", fontsize=9)
        ax.set_xlabel("Intensidade", fontsize=8)
        ax.set_ylabel("Frequência", fontsize=8)
        ax.tick_params(labelsize=7)

        if img is None:
            self._canvas.draw()
            return

        if img.ndim == 2:
            ax.hist(img.ravel(), bins=256, range=(0, 256),
                    color='gray', alpha=0.85)
        else:
            colors = ['red', 'green', 'blue']
            labels = ['R', 'G', 'B']
            for c, col, lbl in zip(range(3), colors, labels):
                ax.hist(img[:, :, c].ravel(), bins=256, range=(0, 256),
                        color=col, alpha=0.5, label=lbl)
            ax.legend(fontsize=7)

        self._canvas.draw()
