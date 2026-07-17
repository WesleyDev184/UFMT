"""Watershed morfológico (item 4) — abordagem por distance transform +
marcadores, escolhida por ficar inteiramente dentro do capítulo de
morfologia (nenhuma das 3 aulas do curso cobre watershed; Aula08 é só
detecção de ponto/borda). Bom pra separar objetos que se tocam, caso
clássico: `rice.tif`.

Passos:
  1. distance_transform: nº de erosões que cada pixel de objeto
     sobrevive (transformada de distância morfológica).
  2. local_maxima: picos do distance transform = centro de cada objeto,
     viram marcadores.
  3. Rotula marcadores com connected_components.extract_components.
  4. Inundação: por nível de distância decrescente, cada rótulo cresce
     (dilatação condicionada) só sobre pixels de objeto com distância
     >= nível; quando dois rótulos disputam o mesmo pixel na mesma
     iteração, esse pixel vira linha de watershed (rótulo -1) e
     congela.
"""
import numpy as np
from numpy.lib.stride_tricks import sliding_window_view

from .morphology import CROSS3, default_anchor, erode
from .connected_components import extract_components, relabel_consecutive


def distance_transform(binary_img, B=CROSS3):
    """Distância morfológica: dist(p) = nº de erosões que p sobrevive."""
    fg = (binary_img > 0).astype(np.uint8) * 255
    dist = np.zeros(fg.shape, dtype=np.int32)
    current = fg
    level = 0
    while np.any(current):
        dist[current > 0] = level
        current = erode(current, B)
        level += 1
    return dist


def local_maxima(dist, size=3):
    """Máximos locais do distance transform (broadcast, sem loop).

    `size` pequeno (3) sobre-segmenta: pequenas ondulações na "sela"
    entre dois objetos encostados também viram marcador. `size` maior
    suprime essas ondulações comparando contra uma vizinhança maior —
    ajustar por imagem (objetos maiores/mais próximos pedem size maior).
    """
    pad = size // 2
    padded = np.pad(dist, pad, mode="constant", constant_values=-1)
    win = sliding_window_view(padded, (size, size))
    local_max = win.max(axis=(2, 3))
    return (dist == local_max) & (dist > 0)


def threshold_markers(dist, level, min_size=1, B=CROSS3):
    """Marcadores por corte de altura: componentes de `dist >= level`.

    Mais robusto que `local_maxima` em objetos irregulares (ex: grãos de
    arroz) — a cresta do distance transform de uma forma alongada/não-
    circular pode ter várias ondulações locais, cada uma virando um
    marcador espúrio com `local_maxima`. Cortar por altura mantém a
    região central de cada objeto conectada como um único marcador,
    desde que `level` seja alto o bastante. `min_size` descarta
    fragmentos pequenos (ruído de binarização).
    """
    mask = (dist >= level).astype(np.uint8) * 255
    labels, _ = extract_components(mask, B)
    if min_size > 1:
        sizes = np.bincount(labels.ravel())
        drop = sizes < min_size
        drop[0] = False
        labels = np.where(drop[labels], 0, labels)
        labels, _ = relabel_consecutive(labels)
    return labels


def _propagate_step(labels, active_mask, B, anchor):
    kh, kw = B.shape
    top, left = anchor
    bottom, right = kh - 1 - top, kw - 1 - left
    pad_spec = ((top, bottom), (left, right))

    padded_labels = np.pad(labels, pad_spec, mode="constant", constant_values=0)
    padded_active = np.pad(active_mask.astype(np.uint8), pad_spec,
                            mode="constant", constant_values=0)
    win_labels = sliding_window_view(padded_labels, (kh, kw))
    win_active = sliding_window_view(padded_active, (kh, kw))

    valid = B[None, None] & (win_active > 0) & (win_labels > 0)
    big = 10 ** 9
    lo = np.where(valid, win_labels, big).min(axis=(2, 3))
    hi = np.where(valid, win_labels, -big).max(axis=(2, 3))
    has_neighbor = lo != big
    conflict = has_neighbor & (lo != hi)
    single = has_neighbor & (lo == hi)

    unlabeled_active = active_mask & (labels == 0)
    new_labels = labels.copy()
    new_labels = np.where(unlabeled_active & single, lo, new_labels)
    new_labels = np.where(unlabeled_active & conflict, -1, new_labels)
    return new_labels


def flood_from_markers(binary_img, dist, markers, B=CROSS3, max_iter_per_level=1000):
    """Inundação nível-a-nível de `dist`, a partir de `markers` (labels
    int, 0=não rotulado). Retorna labels finais (-1 = linha de watershed)."""
    B = np.asarray(B).astype(bool)
    anchor = default_anchor(B)
    fg = binary_img > 0
    labels = markers.copy()
    max_level = int(dist.max())

    for level in range(max_level, 0, -1):
        active_mask = fg & (dist >= level)
        for _ in range(max_iter_per_level):
            new_labels = _propagate_step(labels, active_mask, B, anchor)
            if np.array_equal(new_labels, labels):
                break
            labels = new_labels
    return labels


def watershed_transform(binary_img, B=CROSS3, dist=None, markers=None,
                         marker_window=7):
    """Pipeline completo: distance transform -> marcadores -> inundação.

    Marcadores por padrão vêm de `local_maxima` (bom para formas
    convexas bem separadas, ex: círculos sintéticos). Para formas
    irregulares (ex: rice.tif), passe `markers` pré-computado com
    `threshold_markers` — veja discussão no notebook.
    """
    if dist is None:
        dist = distance_transform(binary_img, B)
    if markers is None:
        maxima = local_maxima(dist, size=marker_window)
        markers, _ = extract_components((maxima * 255).astype(np.uint8), B)
    n = int(markers.max())
    labels = flood_from_markers(binary_img, dist, markers, B)
    return labels, dist, n


def draw_watershed_lines(rgb_img, labels):
    """Marca linhas de watershed (label==-1) em vermelho sobre uma cópia
    de rgb_img, pra visualização."""
    out = rgb_img.copy()
    out[labels == -1] = [255, 0, 0]
    return out
