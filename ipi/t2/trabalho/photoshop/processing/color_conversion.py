import numpy as np


def rgb2hsi(image: np.ndarray) -> np.ndarray:
    img = image.astype(np.float64) / 255.0
    r = img[:, :, 0]
    g = img[:, :, 1]
    b = img[:, :, 2]

    intensity = (r + g + b) / 3.0

    min_rgb = np.min(img, axis=2)
    saturation = 1.0 - (3.0 / (r + g + b + 1e-6)) * min_rgb

    num = 0.5 * ((r - g) + (r - b))
    den = np.sqrt((r - g) ** 2 + (r - b) * (g - b))
    hue = np.arccos(np.clip(num / (den + 1e-6), -1.0, 1.0))
    hue[b > g] = 2 * np.pi - hue[b > g]
    hue = hue / (2 * np.pi)

    hsi = np.stack((hue, saturation, intensity), axis=2)
    return hsi * 255.0


def hsi2rgb(image: np.ndarray) -> np.ndarray:
    img = image.astype(np.float64) / 255.0
    h = img[:, :, 0] * 2 * np.pi
    s = img[:, :, 1]
    i = img[:, :, 2]

    r = np.zeros_like(h)
    g = np.zeros_like(h)
    b = np.zeros_like(h)

    m1 = (h >= 0) & (h < 2 * np.pi / 3)
    b[m1] = i[m1] * (1 - s[m1])
    cos_h = np.cos(h[m1])
    cos_60_h = np.cos(np.pi / 3 - h[m1])
    r[m1] = i[m1] * (1 + s[m1] * cos_h / (cos_60_h + 1e-6))
    g[m1] = 3 * i[m1] - (r[m1] + b[m1])

    m2 = (h >= 2 * np.pi / 3) & (h < 4 * np.pi / 3)
    h2 = h[m2] - 2 * np.pi / 3
    r[m2] = i[m2] * (1 - s[m2])
    g[m2] = i[m2] * (1 + s[m2] * np.cos(h2) / (np.cos(np.pi / 3 - h2) + 1e-6))
    b[m2] = 3 * i[m2] - (r[m2] + g[m2])

    m3 = (h >= 4 * np.pi / 3) & (h < 2 * np.pi)
    h3 = h[m3] - 4 * np.pi / 3
    g[m3] = i[m3] * (1 - s[m3])
    b[m3] = i[m3] * (1 + s[m3] * np.cos(h3) / (np.cos(np.pi / 3 - h3) + 1e-6))
    r[m3] = 3 * i[m3] - (g[m3] + b[m3])

    rgb = np.stack((r, g, b), axis=2) * 255.0
    return np.clip(rgb, 0, 255)
