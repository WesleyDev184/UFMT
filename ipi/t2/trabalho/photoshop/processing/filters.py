import numpy as np
import cv2


_BORDER = {
    'zero':      cv2.BORDER_CONSTANT,
    'reflect':   cv2.BORDER_REFLECT,
    'replicate': cv2.BORDER_REPLICATE,
    'wrap':      cv2.BORDER_WRAP,
}


def _border(padding: str) -> int:
    return _BORDER.get(padding, cv2.BORDER_REFLECT)


def apply_filter(img: np.ndarray, kernel: np.ndarray,
                 padding: str = 'reflect', convolve: bool = False) -> np.ndarray:
    k = np.rot90(kernel, 2) if convolve else kernel
    out = cv2.filter2D(img.astype(np.float64), cv2.CV_64F, k,
                       borderType=_border(padding))
    return np.clip(out, 0, 255).astype(np.uint8)


def box_filter(img: np.ndarray, ksize: int = 3,
               padding: str = 'reflect', separable: bool = True,
               convolve: bool = False) -> np.ndarray:
    if separable:
        k1d = np.ones((ksize, 1), dtype=np.float64) / ksize
        out = cv2.sepFilter2D(img, cv2.CV_64F, k1d, k1d.T,
                              borderType=_border(padding))
        return np.clip(out, 0, 255).astype(np.uint8)
    kernel = np.ones((ksize, ksize), dtype=np.float64) / (ksize * ksize)
    return apply_filter(img, kernel, padding, convolve)


def gaussian_filter(img: np.ndarray, sigma: float = 1.0,
                    padding: str = 'reflect', separable: bool = True,
                    convolve: bool = False) -> np.ndarray:
    ksize = max(3, int(np.ceil(6 * sigma)))
    if ksize % 2 == 0:
        ksize += 1
    if separable:
        k1d = cv2.getGaussianKernel(ksize, sigma)
        out = cv2.sepFilter2D(img, cv2.CV_64F, k1d, k1d.T,
                              borderType=_border(padding))
        return np.clip(out, 0, 255).astype(np.uint8)
    k1d = cv2.getGaussianKernel(ksize, sigma)
    kernel = k1d @ k1d.T
    return apply_filter(img, kernel, padding, convolve)


def median_filter(img: np.ndarray, ksize: int = 3) -> np.ndarray:
    if ksize % 2 == 0:
        ksize += 1
    return cv2.medianBlur(img.astype(np.uint8), ksize)


def laplacian_sharpen(img: np.ndarray, kernel_type: str = '8-conn',
                      c: float = -1.0, padding: str = 'reflect') -> np.ndarray:
    kernels = {
        '4-conn':  np.array([[0,  1, 0], [1, -4, 1], [0,  1, 0]], dtype=np.float64),
        '8-conn':  np.array([[1,  1, 1], [1, -8, 1], [1,  1, 1]], dtype=np.float64),
        '4-conn+': np.array([[0, -1, 0], [-1, 4, -1], [0, -1, 0]], dtype=np.float64),
        '8-conn+': np.array([[-1, -1, -1], [-1, 8, -1], [-1, -1, -1]], dtype=np.float64),
    }
    kernel = kernels.get(kernel_type, kernels['8-conn'])
    f = img.astype(np.float64)
    lap = cv2.filter2D(f, cv2.CV_64F, kernel, borderType=_border(padding))
    out = f + c * lap
    return np.clip(out, 0, 255).astype(np.uint8)


def sobel_sharpen(img: np.ndarray, c: float = 0.5,
                  padding: str = 'reflect') -> np.ndarray:
    sob_x = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]], dtype=np.float64)
    sob_y = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]], dtype=np.float64)
    border = _border(padding)
    f = img.astype(np.float64)
    gx = cv2.filter2D(f, cv2.CV_64F, sob_x, borderType=border)
    gy = cv2.filter2D(f, cv2.CV_64F, sob_y, borderType=border)
    mag = np.sqrt(gx ** 2 + gy ** 2)
    out = f + c * mag
    return np.clip(out, 0, 255).astype(np.uint8)


def unsharp_mask(img: np.ndarray, sigma: float = 2.0,
                 c: float = 1.0, padding: str = 'reflect') -> np.ndarray:
    smoothed = gaussian_filter(img, sigma=sigma, padding=padding)
    f = img.astype(np.float64)
    s = smoothed.astype(np.float64)
    mask = f - s
    out = f + c * mask
    return np.clip(out, 0, 255).astype(np.uint8)
