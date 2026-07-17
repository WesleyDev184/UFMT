"""Núcleo de morfologia matemática — erosão e hit-or-miss. Tudo
vetorizado com broadcast via `sliding_window_view` (sem cv2, sem
scipy.ndimage).

Convenção: imagens binárias usam 0 (fundo) e 255 (objeto). Elemento
estruturante B é um array 2D de 0/1; `anchor` é (linha, coluna) da
origem dentro de B (padrão: centro).
"""
import numpy as np
from numpy.lib.stride_tricks import sliding_window_view

CROSS3 = np.array([[0, 1, 0],
                    [1, 1, 1],
                    [0, 1, 0]], dtype=np.uint8)

SQUARE3 = np.ones((3, 3), dtype=np.uint8)


def default_anchor(B):
    return (B.shape[0] // 2, B.shape[1] // 2)


def _pad(img, kh, kw, anchor, value):
    top, left = anchor
    bottom, right = kh - 1 - top, kw - 1 - left
    return np.pad(img, ((top, bottom), (left, right)), mode="constant",
                  constant_values=value)


def _windows(img, B, anchor, neutral):
    kh, kw = B.shape
    padded = _pad(img, kh, kw, anchor, neutral)
    return sliding_window_view(padded, (kh, kw))


def erode(img, B, anchor=None, border_value=None):
    """A ⊖ B: min sobre a janela nas posições onde B==1.

    `border_value` controla o que existe fora da imagem: padrão
    `img.max()` (erosão clássica, borda não "some" sozinha). Hit-or-miss
    usa `border_value=0` — fora da imagem não deve satisfazer nem a
    condição de objeto nem a de fundo, senão o algoritmo "vaza" pela
    borda (falso positivo tratando o exterior como objeto).
    """
    B = np.asarray(B)
    anchor = anchor or default_anchor(B)
    dont_care = int(img.max())  # identidade do min: nunca deve afetar o resultado
    pad_value = dont_care if border_value is None else border_value
    win = _windows(img, B, anchor, pad_value)
    masked = np.where(B.astype(bool), win, dont_care)
    return masked.min(axis=(2, 3)).astype(img.dtype)


def hit_or_miss(img, B1, B2, anchor=None):
    """I ⊛ (B1,B2) = (A ⊖ B1) ∩ (Aᶜ ⊖ B2).

    B1 marca posições que devem ser objeto (255), B2 marca posições
    que devem ser fundo (0); posições fora de ambos são "don't care".
    """
    B1 = np.asarray(B1)
    anchor = anchor or default_anchor(B1)
    fg = (img > 0).astype(np.uint8) * 255
    bg = 255 - fg
    e1 = erode(fg, B1, anchor, border_value=0)
    e2 = erode(bg, B2, anchor, border_value=0)
    return np.minimum(e1, e2)
