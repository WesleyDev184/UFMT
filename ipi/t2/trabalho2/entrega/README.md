# Trabalho 2 — Processamento de Imagens

## Como rodar

```bash
python3 -m venv venv
venv/bin/pip install -r requirements.txt
venv/bin/jupyter notebook main.ipynb
```

Ou, pra reexecutar tudo direto do terminal (sem abrir a interface):

```bash
venv/bin/jupyter nbconvert --to notebook --execute --inplace main.ipynb
```

O notebook já vem com as saídas (imagens/gráficos) salvas — não precisa rodar
de novo pra ver os resultados, só pra conferir/alterar.

## Estrutura

```
entrega/
├── main.ipynb        # roda os 4 itens do enunciado e mostra os resultados
├── imgproc/           # funções de processamento (numpy puro, sem cv2)
├── Archive/            # imagens de teste usadas pelo notebook
└── requirements.txt
```

`imgproc/io_utils.py` usa `cv2` **apenas** pra ler/salvar arquivo de imagem
— todo o processamento (filtragem em frequência, morfologia, componentes
conectados, convex hull, detecção de bordas) é numpy puro com broadcast
(`sliding_window_view`), sem `cv2` e sem `scipy.ndimage`.

## Itens implementados

1. **Filtragem em frequência** (`imgproc/freq_filters.py`): Gaussiano e
   Butterworth passa-baixas/passa-altas, variando D0 (e n no Butterworth),
   mais aguçamento via passa-altas gaussiano.
2. **Componentes conectados** (`imgproc/connected_components.py`): extração
   via dilatação morfológica, versão otimizada (todos os rótulos propagam
   simultaneamente num único passe vetorizado por iteração).
3. **Convex hull** (`imgproc/convex_hull.py`): via Hit-or-Miss, 4 elementos
   estruturantes rotacionados (detector de canto côncavo), aplicado por
   componente conectado.
4. **Detecção de bordas — Canny** (`imgproc/edges.py`): suavização
   gaussiana + gradiente Sobel + supressão de não-máximos + histerese
   8-conectada. Substitui o watershed morfológico do enunciado original
   porque nenhuma aula do curso cobre watershed — Aula08 ensina segmentação
   por descontinuidade via Canny (ver discussão no início do notebook).
