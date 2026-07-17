"""E/S de imagens e utilidades de exibição.

cv2 é usado aqui apenas para leitura/escrita de arquivo — todo o
processamento (frequência, morfologia, componentes, hull, watershed)
fica em módulos separados e não usa cv2.
"""
import cv2
import numpy as np
import matplotlib.pyplot as plt


def load_image(path, grayscale=True):
    """Carrega imagem do disco. RGB uint8 (ou 2D uint8 se grayscale=True)."""
    flag = cv2.IMREAD_GRAYSCALE if grayscale else cv2.IMREAD_COLOR
    img = cv2.imread(path, flag)
    if img is None:
        raise FileNotFoundError(path)
    if not grayscale:
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    return img


def to_uint8(img):
    """Normaliza um array float para uint8 [0,255]."""
    img = img.astype(np.float64)
    lo, hi = img.min(), img.max()
    if hi - lo < 1e-12:
        return np.zeros_like(img, dtype=np.uint8)
    return ((img - lo) / (hi - lo) * 255).astype(np.uint8)


def otsu_threshold(img):
    """Limiar de Otsu (maximiza variância entre classes) — implementação
    manual, sem cv2.threshold, pra binarizar antes de componentes/hull/
    watershed."""
    hist, _ = np.histogram(img, bins=256, range=(0, 256))
    hist = hist.astype(np.float64)
    total = img.size
    sum_total = np.dot(np.arange(256), hist)
    sum_bg = weight_bg = best_var = threshold = 0.0
    for t in range(256):
        weight_bg += hist[t]
        if weight_bg == 0:
            continue
        weight_fg = total - weight_bg
        if weight_fg == 0:
            break
        sum_bg += t * hist[t]
        mean_bg = sum_bg / weight_bg
        mean_fg = (sum_total - sum_bg) / weight_fg
        between_var = weight_bg * weight_fg * (mean_bg - mean_fg) ** 2
        if between_var > best_var:
            best_var = between_var
            threshold = t
    return threshold


def binarize(img, threshold=None, invert=False):
    """Limiariza img (grayscale) em 0/255. threshold=None usa Otsu.
    invert=True se o objeto for mais escuro que o fundo."""
    if threshold is None:
        threshold = otsu_threshold(img)
    mask = img <= threshold if invert else img > threshold
    return (mask * 255).astype(np.uint8)


def show_grid(images, titles=None, cmap="gray", figsize=None, cols=None):
    """Mostra uma lista de imagens lado a lado com matplotlib."""
    n = len(images)
    cols = cols or n
    rows = (n + cols - 1) // cols
    figsize = figsize or (4 * cols, 4 * rows)
    fig, axs = plt.subplots(rows, cols, figsize=figsize, squeeze=False)
    for idx in range(rows * cols):
        ax = axs[idx // cols][idx % cols]
        ax.axis("off")
        if idx < n:
            im = images[idx]
            im_cmap = None if (im.ndim == 3) else cmap
            ax.imshow(im, cmap=im_cmap, vmin=0 if im_cmap else None,
                      vmax=255 if im_cmap else None)
            if titles:
                ax.set_title(titles[idx])
    fig.tight_layout()
    plt.show()
