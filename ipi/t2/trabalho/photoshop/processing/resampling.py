import numpy as np
import cv2


def nearest_neighbor(img: np.ndarray, scale_h: float, scale_w: float) -> np.ndarray:
    is_gray = img.ndim == 2
    arr = img[:, :, np.newaxis] if is_gray else img
    h, w, c = arr.shape

    nh = max(1, int(round(h * scale_h)))
    nw = max(1, int(round(w * scale_w)))

    sr = float(h) / float(nh)
    sc = float(w) / float(nw)

    R = np.clip(np.round(np.arange(nh) * sr).astype(int), 0, h - 1)
    C = np.clip(np.round(np.arange(nw) * sc).astype(int), 0, w - 1)

    out = arr[np.ix_(R, C)]
    return out[:, :, 0] if is_gray else out


def bilinear(img: np.ndarray, scale_h: float, scale_w: float) -> np.ndarray:
    is_gray = img.ndim == 2
    arr = img[:, :, np.newaxis].astype(np.float64) if is_gray else img.astype(np.float64)
    h, w, c = arr.shape

    nh = max(1, int(round(h * scale_h)))
    nw = max(1, int(round(w * scale_w)))

    sr = float(h) / float(nh)
    sc = float(w) / float(nw)

    rm = np.clip(np.arange(nh) * sr, 0, h - 1 - 1e-9)
    cm = np.clip(np.arange(nw) * sc, 0, w - 1 - 1e-9)

    r0 = np.floor(rm).astype(int)
    c0 = np.floor(cm).astype(int)
    r1 = np.minimum(r0 + 1, h - 1)
    c1 = np.minimum(c0 + 1, w - 1)

    dr = (rm - r0)[:, np.newaxis]
    dc = (cm - c0)[np.newaxis, :]

    wa = (1 - dr) * (1 - dc)
    wb = dr * (1 - dc)
    wc = (1 - dr) * dc
    wd = dr * dc

    out = np.zeros((nh, nw, c), dtype=np.float64)
    for ch in range(c):
        Ia = arr[np.ix_(r0, c0)][:, :, ch]
        Ib = arr[np.ix_(r1, c0)][:, :, ch]
        Ic = arr[np.ix_(r0, c1)][:, :, ch]
        Id = arr[np.ix_(r1, c1)][:, :, ch]
        out[:, :, ch] = wa * Ia + wb * Ib + wc * Ic + wd * Id

    out = np.clip(out, 0, 255).astype(np.uint8)
    return out[:, :, 0] if is_gray else out


def bicubic(img: np.ndarray, scale_h: float, scale_w: float) -> np.ndarray:
    h, w = img.shape[:2]
    nh = max(1, int(round(h * scale_h)))
    nw = max(1, int(round(w * scale_w)))
    return cv2.resize(img, (nw, nh), interpolation=cv2.INTER_CUBIC)
