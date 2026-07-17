"""Extração de componentes conectados via dilatação morfológica (item 2),
versão otimizada: em vez de rodar X_k=(X_{k-1}⊕B)∩I uma vez por
componente (loop Python por componente, como no math_morphology.ipynb
original), propaga TODOS os rótulos simultaneamente num único array,
um passe vetorizado por iteração.

Ideia: cada pixel de objeto começa com um rótulo único (seu índice
linear). A cada iteração, cada pixel adota o MENOR rótulo entre seus
vizinhos (dentro do elemento estruturante B) que também sejam objeto —
isso é exatamente a dilatação X_k=(X_{k-1}⊕B)∩I generalizada de
binário (0/1, OR) para multi-rótulo (inteiros, MIN), rodando todos os
componentes ao mesmo tempo. Converge quando cada região conectada
estabiliza no menor rótulo original presente nela — O(iterações×H×W)
no total, em vez de O(nº_componentes×iterações×H×W).

Não precisa de sementes manuais: todo pixel de objeto é sua própria
semente inicial.
"""
import numpy as np
from numpy.lib.stride_tricks import sliding_window_view

from .morphology import CROSS3, default_anchor


def extract_components(binary_img, B=CROSS3, max_iter=10_000):
    """Retorna (labels, n_componentes). labels: int32, 0=fundo, 1..n=componentes."""
    fg = binary_img > 0
    H, W = fg.shape
    B = np.asarray(B).astype(bool)
    kh, kw = B.shape
    anchor = default_anchor(B)
    top, left = anchor
    bottom, right = kh - 1 - top, kw - 1 - left

    labels = np.where(fg, np.arange(1, H * W + 1, dtype=np.int64).reshape(H, W), 0)
    sentinel = H * W + 1

    for _ in range(max_iter):
        work = np.where(fg, labels, sentinel)
        padded = np.pad(work, ((top, bottom), (left, right)),
                         mode="constant", constant_values=sentinel)
        win = sliding_window_view(padded, (kh, kw))
        masked = np.where(B, win, sentinel)
        candidate = masked.min(axis=(2, 3))
        new_labels = np.where(fg, candidate, 0)
        if np.array_equal(new_labels, labels):
            labels = new_labels
            break
        labels = new_labels

    return relabel_consecutive(labels)


def relabel_consecutive(labels):
    """Renomeia rótulos esparsos para 1..n contíguos."""
    uniq = np.unique(labels)
    uniq = uniq[uniq != 0]
    out = np.zeros_like(labels, dtype=np.int32)
    for new_id, old_id in enumerate(uniq, start=1):
        out[labels == old_id] = new_id
    return out, len(uniq)


def colorize(labels, seed=0):
    """Atribui uma cor RGB aleatória por rótulo (0 = preto) via indexação
    fancy (broadcast): colors[labels] expande (H,W) -> (H,W,3)."""
    rng = np.random.default_rng(seed)
    n = int(labels.max())
    colors = rng.integers(50, 256, size=(n + 1, 3), dtype=np.uint8)
    colors[0] = 0
    return colors[labels]


def component_bboxes(labels, n):
    """Bounding box (r0,r1,c0,c1) por rótulo 1..n, usado pelo convex hull
    pra restringir o crescimento a cada objeto."""
    boxes = {}
    for lbl in range(1, n + 1):
        ys, xs = np.where(labels == lbl)
        if ys.size == 0:
            continue
        boxes[lbl] = (ys.min(), ys.max() + 1, xs.min(), xs.max() + 1)
    return boxes
