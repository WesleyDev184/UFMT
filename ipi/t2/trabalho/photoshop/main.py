import sys
import os
# Garante que o diretório pai (trabalho/) está no path para imports relativos funcionarem
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from PyQt5.QtWidgets import QApplication
from PyQt5.QtGui import QPalette, QColor
from PyQt5.QtCore import Qt
from photoshop.ui.main_window import MainWindow


def _dark_palette() -> QPalette:
    p = QPalette()
    dark   = QColor(45, 45, 48)
    mid    = QColor(63, 63, 70)
    bright = QColor(200, 200, 200)
    accent = QColor(0, 122, 204)
    p.setColor(QPalette.Window,          dark)
    p.setColor(QPalette.WindowText,      bright)
    p.setColor(QPalette.Base,            QColor(30, 30, 30))
    p.setColor(QPalette.AlternateBase,   dark)
    p.setColor(QPalette.ToolTipBase,     QColor(255, 255, 220))
    p.setColor(QPalette.ToolTipText,     Qt.black)
    p.setColor(QPalette.Text,            bright)
    p.setColor(QPalette.Button,          mid)
    p.setColor(QPalette.ButtonText,      bright)
    p.setColor(QPalette.BrightText,      Qt.red)
    p.setColor(QPalette.Link,            accent)
    p.setColor(QPalette.Highlight,       accent)
    p.setColor(QPalette.HighlightedText, Qt.white)
    return p


def main():
    app = QApplication(sys.argv)
    app.setStyle("Fusion")
    app.setPalette(_dark_palette())
    app.setApplicationName("PhotoPy")
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
