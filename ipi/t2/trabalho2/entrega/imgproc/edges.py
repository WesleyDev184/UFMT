"""Detector de bordas de Canny (item 4, Aula08 slides 44-52) — substitui o
watershed morfológico: nenhuma das 3 aulas do curso cobre watershed, mas o
detector de Canny é o assunto central de segmentação por descontinuidade em
Aula08. Tudo numpy puro (convolução via `sliding_window_view`), sem cv2.

Passos (slides 45-52):
  1. Suavização gaussiana de f(x,y) (reduz falsos positivos por ruído).
  2. Gradiente (Sobel): magnitude |∇f| e orientação α(x,y).
  3. Supressão de não-máximos: afina as "cristas" largas da magnitude,
     quantizando α em 4 direções (0°, 45°, 90°, 135°) e comparando cada
     pixel aos 2 vizinhos na direção perpendicular à borda.
  4. Histerese com dois limiares T_baixo/T_alto: pixels fortes (>=T_alto)
     são borda; pixels fracos (>=T_baixo) só viram borda se conectados
     (conectividade-8) a um pixel forte — implementado reaproveitando
     `connected_components.extract_components` com B=SQUARE3 em vez de
     escrever o algoritmo de encadeamento do zero.
"""
import numpy as np
from numpy.lib.stride_tricks import sliding_window_view

from .morphology import SQUARE3
from .connected_components import extract_components

SOBEL_X = np.array([[-1, 0, 1],
                     [-2, 0, 2],
                     [-1, 0, 1]], dtype=np.float64)

SOBEL_Y = np.array([[-1, -2, -1],
                     [0, 0, 0],
                     [1, 2, 1]], dtype=np.float64)


def gaussian_kernel(size=5, sigma=1.4):
    """Kernel gaussiano 2D normalizado (slide 46: g(x,y) da convolução)."""
    ax = np.arange(-(size // 2), size // 2 + 1)
    xx, yy = np.meshgrid(ax, ax)
    kernel = np.exp(-(xx ** 2 + yy ** 2) / (2 * sigma ** 2))
    return kernel / kernel.sum()


def convolve(img, kernel):
    """Convolução 2D via broadcast (`sliding_window_view` + `einsum`),
    replicando a borda (evita escurecer as bordas com zero-padding)."""
    kh, kw = kernel.shape
    pad_h, pad_w = kh // 2, kw // 2
    padded = np.pad(img.astype(np.float64), ((pad_h, pad_h), (pad_w, pad_w)), mode="edge")
    win = sliding_window_view(padded, (kh, kw))
    return np.einsum("ijkl,kl->ij", win, kernel)


def sobel_gradient(img):
    """Magnitude e orientação do gradiente (slide 47): |∇f|=hypot(gx,gy),
    α em graus, normalizada pra [0,180) (a direção da borda não distingue
    sentido, só orientação)."""
    gx = convolve(img, SOBEL_X)
    gy = convolve(img, SOBEL_Y)
    mag = np.hypot(gx, gy)
    angle = np.degrees(np.arctan2(gy, gx)) % 180
    return mag, angle


def non_max_suppression(mag, angle):
    """Afina as cristas da magnitude (slides 48-50): quantiza α em 4
    direções e mantém só os pixels que são máximo local ao longo da
    direção perpendicular à borda (vetorizado com vizinhos deslocados,
    sem loop por pixel)."""
    padded = np.pad(mag, 1, mode="constant", constant_values=0)
    north = padded[0:-2, 1:-1]
    south = padded[2:, 1:-1]
    west = padded[1:-1, 0:-2]
    east = padded[1:-1, 2:]
    nw = padded[0:-2, 0:-2]
    ne = padded[0:-2, 2:]
    sw = padded[2:, 0:-2]
    se = padded[2:, 2:]

    d0 = (angle < 22.5) | (angle >= 157.5)     # borda vertical -> normal horizontal
    d45 = (angle >= 22.5) & (angle < 67.5)     # normal a 45°
    d90 = (angle >= 67.5) & (angle < 112.5)    # borda horizontal -> normal vertical
    d135 = (angle >= 112.5) & (angle < 157.5)  # normal a 135°

    n1 = np.select([d0, d45, d90, d135], [west, sw, north, nw])
    n2 = np.select([d0, d45, d90, d135], [east, ne, south, se])

    keep = (mag >= n1) & (mag >= n2)
    return np.where(keep, mag, 0.0)


def hysteresis(nms, low_ratio=0.06, high_ratio=0.15):
    """Limiarização dupla + encadeamento de bordas (slides 51-52). T_alto e
    T_baixo são fração do gradiente máximo (razão ~2.5:1, dentro da faixa
    2:1-3:1 sugerida no slide). Em vez do procedimento pixel-a-pixel do
    slide (percorrer bordas fortes e marcar fracas 8-conectadas), roda
    `extract_components` (8-conectividade) sobre fortes∪fracas e mantém só
    os componentes que contêm pelo menos um pixel forte — mesmo resultado,
    vetorizado."""
    high = nms.max() * high_ratio
    low = nms.max() * low_ratio
    strong = nms >= high
    weak = (nms >= low) & ~strong

    combined = ((strong | weak) * 255).astype(np.uint8)
    labels, n = extract_components(combined, B=SQUARE3)
    if n == 0:
        return np.zeros_like(nms, dtype=bool)
    strong_ids = np.unique(labels[strong & (labels > 0)])
    return np.isin(labels, strong_ids) & (labels > 0)


def canny(img, sigma=1.4, kernel_size=5, low_ratio=0.06, high_ratio=0.15):
    """Pipeline completo. Retorna (bordas uint8 0/255, magnitude, nms)."""
    smoothed = convolve(img, gaussian_kernel(kernel_size, sigma))
    mag, angle = sobel_gradient(smoothed)
    nms = non_max_suppression(mag, angle)
    edges = hysteresis(nms, low_ratio, high_ratio)
    return (edges * 255).astype(np.uint8), mag, nms
