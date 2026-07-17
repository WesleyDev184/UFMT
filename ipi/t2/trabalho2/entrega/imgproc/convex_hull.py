"""Envoltório convexo (convex hull) via Hit-or-Miss (Aula07, slides 48-50).

B1 detecta um canto côncavo: vizinhos Norte+Oeste exigidos objeto,
Leste+Sul exigidos fundo (cantos e centro = don't care). B2,B3,B4 =
B1 rotacionado 90°, 180°, 270° — cobre as 4 orientações de canto,
gerado com np.rot90 em vez de transcrito pixel a pixel da figura do
slide (o algoritmo é o mesmo: cada Bi é o anterior girado 90°;
transcrição visual exata da figura não pôde ser confirmada com
certeza, então a versão aqui foi derivada e validada testando que
preenche corretamente um canto côncavo real).

X_k^i = (X_{k-1}^i ⊛ B^i) ∪ X_{k-1}^i,  i=1..4,  até convergência.
C(A) = ∪ D^i.

Slide 49 aponta que o hull pode crescer além dos limites do objeto;
a correção sugerida (slide 51) é aplicar o algoritmo por componente,
restrito à bounding box de cada um — é o que `convex_hull_per_component`
faz, reaproveitando `component_bboxes` do módulo de componentes
conectados.
"""
import numpy as np

from .morphology import hit_or_miss
from .connected_components import component_bboxes

_B1_FG = np.array([[0, 1, 0],
                   [1, 0, 0],
                   [0, 0, 0]], dtype=np.uint8)  # Norte + Oeste = objeto
_B1_BG = np.array([[0, 0, 0],
                   [0, 0, 1],
                   [0, 1, 0]], dtype=np.uint8)  # Leste + Sul = fundo


def convex_hull_binary(binary_img, max_iter=1000):
    """Convex hull de uma imagem binária (255=objeto), sem restrição de bbox."""
    results = []
    for k in range(4):
        B_fg = np.rot90(_B1_FG, k)
        B_bg = np.rot90(_B1_BG, k)
        X = binary_img.copy()
        for _ in range(max_iter):
            hm = hit_or_miss(X, B_fg, B_bg)
            new_X = np.maximum(X, hm)
            if np.array_equal(new_X, X):
                break
            X = new_X
        results.append(X)
    return np.maximum.reduce(results)


def convex_hull_per_component(binary_img, labels, n, max_iter=1000):
    """Aplica convex_hull_binary por componente, restrito à sua bounding
    box, evitando o crescimento excessivo apontado no slide 49."""
    out = np.zeros_like(binary_img)
    for lbl, (r0, r1, c0, c1) in component_bboxes(labels, n).items():
        sub = (labels[r0:r1, c0:c1] == lbl).astype(np.uint8) * 255
        hull_sub = convex_hull_binary(sub, max_iter=max_iter)
        out[r0:r1, c0:c1] = np.maximum(out[r0:r1, c0:c1], hull_sub)
    return out
