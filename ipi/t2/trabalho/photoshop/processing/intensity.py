import numpy as np
from .color_conversion import rgb2hsi, hsi2rgb


def brightness_additive(img: np.ndarray, c: float) -> np.ndarray:
    """Add constant c to each RGB channel."""
    out = img.astype(np.float64) + c
    return np.clip(out, 0, 255).astype(np.uint8)


def brightness_multiplicative(img: np.ndarray, c: float) -> np.ndarray:
    """Multiply each RGB channel by constant c."""
    out = img.astype(np.float64) * c
    return np.clip(out, 0, 255).astype(np.uint8)


def brightness_hsi(img: np.ndarray, c: float) -> np.ndarray:
    """Adjust brightness via I channel in HSI to preserve chromaticity."""
    if img.ndim == 2:
        return np.clip(img.astype(np.float64) + c, 0, 255).astype(np.uint8)
    hsi = rgb2hsi(img)
    hsi[:, :, 2] = np.clip(hsi[:, :, 2] + c, 0, 255)
    return hsi2rgb(hsi).astype(np.uint8)


def negative(img: np.ndarray) -> np.ndarray:
    """s = 255 - r  (complementary colors for RGB)."""
    return (255 - img.astype(np.int16)).clip(0, 255).astype(np.uint8)


def log_transform(img: np.ndarray, c: float = None) -> np.ndarray:
    """g = c * log(1 + f). Expands dark region details."""
    f = img.astype(np.float64)
    if c is None:
        c = 255.0 / np.log(256.0)
    out = c * np.log(1.0 + f)
    return np.clip(out, 0, 255).astype(np.uint8)


def exp_transform(img: np.ndarray, c: float = 1.0) -> np.ndarray:
    """Exponential transform: expands bright region representation."""
    f = img.astype(np.float64) / 255.0
    out = (np.exp(f * c) - 1.0) / (np.exp(c) - 1.0 + 1e-9) * 255.0
    return np.clip(out, 0, 255).astype(np.uint8)


def gamma_transform(img: np.ndarray, gamma: float, c: float = None) -> np.ndarray:
    """Power-law: g = c * f^gamma. gamma<1 lightens, gamma>1 darkens."""
    f = img.astype(np.float64)
    if c is None:
        c = 255.0 / (255.0 ** gamma)
    out = c * (f ** gamma)
    return np.clip(out, 0, 255).astype(np.uint8)


def piecewise_linear(img: np.ndarray, r1: float, s1: float,
                     r2: float, s2: float) -> np.ndarray:
    """3-segment piecewise linear transform defined by (r1,s1) and (r2,s2)."""
    f = img.astype(np.float64)
    out = np.zeros_like(f)

    eps = 1e-9
    # Segment 1: [0, r1] -> [0, s1]
    if r1 > 0:
        mask = f <= r1
        out[mask] = (s1 / (r1 + eps)) * f[mask]

    # Segment 2: (r1, r2] -> [s1, s2]
    if r2 > r1:
        mask = (f > r1) & (f <= r2)
        out[mask] = s1 + ((s2 - s1) / (r2 - r1 + eps)) * (f[mask] - r1)

    # Segment 3: (r2, 255] -> [s2, 255]
    if r2 < 255:
        mask = f > r2
        out[mask] = s2 + ((255 - s2) / (255 - r2 + eps)) * (f[mask] - r2)

    return np.clip(out, 0, 255).astype(np.uint8)


def threshold_binary(img: np.ndarray, a: float, b: float) -> np.ndarray:
    """Pixels in [a,b] -> 255, rest -> 0 (grayscale output)."""
    gray = np.mean(img, axis=2).astype(np.float64) if img.ndim == 3 else img.astype(np.float64)
    out = np.zeros_like(gray, dtype=np.uint8)
    out[(gray > a) & (gray < b)] = 255
    if img.ndim == 3:
        return np.stack([out, out, out], axis=2)
    return out


def threshold_preserve(img: np.ndarray, a: float, b: float) -> np.ndarray:
    """Pixels in [a,b] highlighted in yellow; rest keeps original tones."""
    gray = np.mean(img, axis=2).astype(np.float64) if img.ndim == 3 else img.astype(np.float64)
    out = img.copy()
    mask = (gray > a) & (gray < b)
    if img.ndim == 3:
        out[mask] = [255, 255, 0]
    else:
        out[mask] = 255
    return out


def threshold_color_cube(img: np.ndarray, ref_color: tuple, w: float) -> np.ndarray:
    """Keep pixels within cube of side w centered on ref_color; rest -> gray 128."""
    if img.ndim != 3:
        return img
    f = img.astype(np.float64)
    cr, cg, cb = ref_color
    mask = (
        (np.abs(f[:, :, 0] - cr) <= w / 2) &
        (np.abs(f[:, :, 1] - cg) <= w / 2) &
        (np.abs(f[:, :, 2] - cb) <= w / 2)
    )
    out = np.full_like(img, 128)
    out[mask] = img[mask]
    return out


def threshold_color_sphere(img: np.ndarray, ref_color: tuple, radius: float) -> np.ndarray:
    """Keep pixels within Euclidean sphere of radius around ref_color; rest -> gray 128."""
    if img.ndim != 3:
        return img
    f = img.astype(np.float64)
    cr, cg, cb = ref_color
    dist = np.sqrt(
        (f[:, :, 0] - cr) ** 2 +
        (f[:, :, 1] - cg) ** 2 +
        (f[:, :, 2] - cb) ** 2
    )
    out = np.full_like(img, 128)
    out[dist <= radius] = img[dist <= radius]
    return out
