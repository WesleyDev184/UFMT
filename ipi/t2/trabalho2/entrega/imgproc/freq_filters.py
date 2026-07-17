"""Filtragem no domínio da frequência (Aula06): Gaussiano e Butterworth,
passa-baixas e passa-altas, mais aguçamento via passa-altas gaussiano.

Pipeline exatamente como no slide 30-31:
  1. zero-padding de MxN para P=2M, Q=2N
  2. multiplica por (-1)^(x+y) e faz DFT -> F(u,v) já centralizado em (P/2,Q/2)
  3. H(u,v) real, simétrico, tamanho PxQ, centrado em (P/2,Q/2)
  4. G = H*F
  5. g_p = real(IDFT(G)) * (-1)^(x+y)   <- remultiplica pra desfazer a centralização
  6. resultado = quadrante superior-esquerdo MxN de g_p
"""
import numpy as np


def _centering_signs(P, Q):
    x = np.arange(P).reshape(-1, 1)
    y = np.arange(Q).reshape(1, -1)
    return (-1.0) ** (x + y)  # broadcast (P,1)+(1,Q) -> (P,Q)


def distance_grid(P, Q):
    """D(u,v) = distância euclidiana ao centro (P/2, Q/2), via broadcast."""
    u = np.arange(P).reshape(-1, 1) - P / 2
    v = np.arange(Q).reshape(1, -1) - Q / 2
    return np.sqrt(u ** 2 + v ** 2)


def glpf(P, Q, D0):
    """Gaussiano passa-baixas: H = exp(-D²/(2 D0²))."""
    D = distance_grid(P, Q)
    return np.exp(-(D ** 2) / (2 * D0 ** 2))


def ghpf(P, Q, D0):
    """Gaussiano passa-altas: H = 1 - GLPF."""
    return 1.0 - glpf(P, Q, D0)


def blpf(P, Q, D0, n):
    """Butterworth passa-baixas: H = 1 / (1 + (D/D0)^(2n))."""
    D = distance_grid(P, Q)
    return 1.0 / (1.0 + (D / D0) ** (2 * n))


def bhpf(P, Q, D0, n):
    """Butterworth passa-altas: H = 1 / (1 + (D0/D)^(2n)); H(centro)=0."""
    D = distance_grid(P, Q).copy()
    center = D == 0
    D[center] = np.inf  # evita divisão por zero: D0/inf -> 0 -> H=0 no centro
    return 1.0 / (1.0 + (D0 / D) ** (2 * n))


def apply_freq_filter(img, H):
    """Aplica H(u,v) (shape 2M,2N) sobre img (MxN) e retorna g(x,y) MxN float64."""
    M, N = img.shape
    P, Q = 2 * M, 2 * N
    f_padded = np.zeros((P, Q), dtype=np.float64)
    f_padded[:M, :N] = img.astype(np.float64)

    signs = _centering_signs(P, Q)
    F = np.fft.fft2(f_padded * signs)
    G = H * F
    g_p = np.real(np.fft.ifft2(G)) * signs
    return g_p[:M, :N]


def _to_uint8(img):
    lo, hi = img.min(), img.max()
    if hi - lo < 1e-12:
        return np.zeros_like(img, dtype=np.uint8)
    return ((img - lo) / (hi - lo) * 255).astype(np.uint8)


def gaussian_filter(img, D0, highpass=False, as_uint8=True):
    M, N = img.shape
    H = ghpf(2 * M, 2 * N, D0) if highpass else glpf(2 * M, 2 * N, D0)
    out = apply_freq_filter(img, H)
    return _to_uint8(out) if as_uint8 else out


def butterworth_filter(img, D0, n, highpass=False, as_uint8=True):
    M, N = img.shape
    H = bhpf(2 * M, 2 * N, D0, n) if highpass else blpf(2 * M, 2 * N, D0, n)
    out = apply_freq_filter(img, H)
    return _to_uint8(out) if as_uint8 else out


def gaussian_sharpen(img, D0, k=1.0, as_uint8=True):
    """g = f + k * GHPF(f, D0). Extensão padrão (Gonzalez) do H_HP do slide 52,
    já que o material do curso define apenas o filtro, não a fórmula de
    aguçamento em si (slide 48 só anuncia o tópico)."""
    M, N = img.shape
    H = ghpf(2 * M, 2 * N, D0)
    hp = apply_freq_filter(img, H)
    out = img.astype(np.float64) + k * hp
    return np.clip(out, 0, 255).astype(np.uint8) if as_uint8 else out
