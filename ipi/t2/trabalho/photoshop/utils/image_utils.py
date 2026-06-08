import numpy as np
import cv2


def load_image(path: str) -> np.ndarray:
    """Load image via OpenCV, return RGB uint8 numpy array."""
    img = cv2.imread(path, cv2.IMREAD_UNCHANGED)
    if img is None:
        raise IOError(f"Cannot load image: {path}")
    if img.ndim == 2:
        return img  # grayscale
    if img.shape[2] == 4:
        img = cv2.cvtColor(img, cv2.COLOR_BGRA2BGR)
    return cv2.cvtColor(img, cv2.COLOR_BGR2RGB)


def save_image(path: str, img: np.ndarray) -> None:
    """Save RGB/gray uint8 numpy array via OpenCV."""
    if img.ndim == 3:
        out = cv2.cvtColor(img.astype(np.uint8), cv2.COLOR_RGB2BGR)
    else:
        out = img.astype(np.uint8)
    cv2.imwrite(path, out)


def to_display(img: np.ndarray) -> np.ndarray:
    """Ensure image is uint8 for display purposes."""
    return np.clip(img, 0, 255).astype(np.uint8)


def is_grayscale(img: np.ndarray) -> bool:
    return img.ndim == 2


def image_info(img: np.ndarray) -> str:
    if img is None:
        return "Nenhuma imagem carregada"
    h = img.shape[0]
    w = img.shape[1]
    ch = 1 if img.ndim == 2 else img.shape[2]
    return f"{w}×{h}  |  {ch} canal{'is' if ch > 1 else ''}  |  uint8"
