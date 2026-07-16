import numpy as np
from .color_conversion import rgb2hsi, hsi2rgb


def _hist(ch: np.ndarray) -> np.ndarray:
    return np.bincount(ch.ravel().astype(np.int32), minlength=256).astype(np.float64)


def _equalize_channel(ch: np.ndarray) -> np.ndarray:
    h, w = ch.shape
    pr = _hist(ch) / (h * w)
    cdf = np.cumsum(pr)
    sk = np.round(255 * cdf).astype(np.uint8)
    return sk[ch]


def equalize_global(img: np.ndarray) -> np.ndarray:
    if img.ndim == 2:
        return _equalize_channel(img.astype(np.uint8))

    hsi = rgb2hsi(img)
    I_eq = _equalize_channel(hsi[:, :, 2].astype(np.uint8))
    hsi[:, :, 2] = I_eq.astype(np.float64)
    return hsi2rgb(hsi).astype(np.uint8)


def histogram_matching(img: np.ndarray, ref: np.ndarray) -> np.ndarray:
    def match_ch(src: np.ndarray, ref_ch: np.ndarray) -> np.ndarray:
        cdf_src = np.cumsum(_hist(src))
        cdf_ref = np.cumsum(_hist(ref_ch))
        lut = np.zeros(256, dtype=np.uint8)
        for i in range(256):
            diff = np.abs(cdf_ref - cdf_src[i])
            lut[i] = diff.argmin()
        return lut[src]

    if img.ndim == 2:
        ref_g = ref if ref.ndim == 2 else np.mean(ref, axis=2).astype(np.uint8)
        return match_ch(img.astype(np.uint8), ref_g.astype(np.uint8))

    ref_3 = ref if ref.ndim == 3 else np.stack([ref, ref, ref], axis=2)
    result = np.zeros_like(img)
    for c in range(3):
        result[:, :, c] = match_ch(img[:, :, c].astype(np.uint8),
                                   ref_3[:, :, c].astype(np.uint8))
    return result


def _local_eq_channel(ch: np.ndarray, ksize: int) -> np.ndarray:
    h, w = ch.shape
    pad = ksize // 2
    padded = np.pad(ch, pad, mode='reflect')
    out = np.zeros_like(ch)
    for r in range(h):
        for col in range(w):
            region = padded[r: r + ksize, col: col + ksize].ravel()
            hist = np.bincount(region.astype(np.int32), minlength=256).astype(np.float64)
            cdf = np.cumsum(hist / region.size)
            out[r, col] = int(round(255 * cdf[ch[r, col]]))
    return out.astype(np.uint8)


def equalize_local(img: np.ndarray, ksize: int = 11) -> np.ndarray:
    if img.ndim == 2:
        return _local_eq_channel(img.astype(np.uint8), ksize)
    result = np.zeros_like(img)
    for c in range(3):
        result[:, :, c] = _local_eq_channel(img[:, :, c].astype(np.uint8), ksize)
    return result
