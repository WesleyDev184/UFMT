import numpy as np
import cv2
def rgb2hsi(image: np.ndarray) -> np.ndarray:
    
    # Normaliza os valores de R, G e B para [0, 1]
    image = image.astype(np.float64) / 255

    # Separa os canais R, G e B
    r = image[:, :, 0]
    g = image[:, :, 1]
    b = image[:, :, 2]

    # Calcula a intensidade
    intensity = (r + g + b) / 3

    # Calcula a saturação
    min_rgb = np.min(image, axis=2)
    saturation = 1 - (3 / (r + g + b + 1e-6)) * min_rgb

    # Calcula a matiz
    num = 0.5 * ((r - g) + (r - b))
    den = np.sqrt((r - g) ** 2 + (r - b) * (g - b))
    hue = np.arccos(num / (den + 1e-6))
    hue[b > g] = 2 * np.pi - hue[b > g]
    hue = hue / (2 * np.pi)  # Normalize hue to [0, 1]

    # Junta os canais H, S e I em uma imagem HSI
    hsi_image = np.stack((hue, saturation, intensity), axis=2)

    return (hsi_image * 255).astype(np.uint8)



def hsi2rgb(image: np.ndarray) -> np.ndarray:
    # Normaliza os valores de H, S e I para [0, 1]
    image = image.astype(np.float64) / 255.0
    h = image[:, :, 0] * 2 * np.pi  # Hue em radianos
    s = image[:, :, 1]             
    i = image[:, :, 2]              

    r = np.zeros(h.shape)
    g = np.zeros(h.shape)
    b = np.zeros(h.shape)

    # Valores H no intervalo [0, 2*pi/3)
    mask = (h >= 0) & (h < 2 * np.pi / 3)
    b[mask] = i[mask] * (1 - s[mask])
    r[mask] = i[mask] * (1 + s[mask] * np.cos(h[mask]) / np.cos(np.pi / 3 - h[mask]))
    g[mask] = 3 * i[mask] - (r[mask] + b[mask])

    # Valores H no intervalo [2*pi/3, 4*pi/3)
    mask = (h >= 2 * np.pi / 3) & (h < 4 * np.pi / 3)
    h_adj = h[mask] - 2 * np.pi / 3
    r[mask] = i[mask] * (1 - s[mask])
    g[mask] = i[mask] * (1 + s[mask] * np.cos(h_adj) / np.cos(np.pi / 3 - h_adj))
    b[mask] = 3 * i[mask] - (r[mask] + g[mask])

    # Valores H no intervalo [4*pi/3, 2*pi)
    mask = (h >= 4 * np.pi / 3) & (h < 2 * np.pi)
    h_adj = h[mask] - 4 * np.pi / 3
    g[mask] = i[mask] * (1 - s[mask])
    b[mask] = i[mask] * (1 + s[mask] * np.cos(h_adj) / np.cos(np.pi / 3 - h_adj))
    r[mask] = 3 * i[mask] - (g[mask] + b[mask])

    # Junta os canais R, G, B em uma imagem RGB e escala para [0, 255]
    rgb_image = np.stack((r, g, b), axis=2) * 255.0
    rgb_image = np.clip(rgb_image, 0, 255).astype(np.uint8)

    return rgb_image
