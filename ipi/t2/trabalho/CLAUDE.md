# PhotoPy – Trabalho T2 IPI/UFMT

Ferramenta de processamento de imagens (Photoshop simplificado) em Python + PyQt5.
Disciplina: Introdução ao Processamento de Imagens – UFMT.

---

## Como rodar

```bash
# Sempre a partir do diretório trabalho/
cd /home/wesley184/github/UFMT/ipi/t2/trabalho
venv/bin/python3 photoshop/main.py
```

O `main.py` insere `trabalho/` no `sys.path` para que os imports relativos (`..utils`, `..processing`) funcionem corretamente dentro do pacote `photoshop`.

---

## Estrutura do projeto

```
trabalho/
├── venv/                        ← virtualenv (Python 3.12)
├── photoshop/                   ← pacote principal
│   ├── main.py                  ← entrypoint; aplica tema escuro Fusion
│   ├── requirements.txt
│   ├── processing/              ← algoritmos puros (sem GUI)
│   │   ├── color_conversion.py  ← rgb2hsi / hsi2rgb (equações do curso)
│   │   ├── resampling.py        ← nearest_neighbor, bilinear, resize_cv2
│   │   ├── intensity.py         ← transformações pontuais
│   │   ├── histogram_ops.py     ← equalização global/local, casamento
│   │   └── filters.py           ← filtros espaciais
│   ├── ui/                      ← interface PyQt5
│   │   ├── main_window.py       ← janela principal, menus, undo/redo, zoom
│   │   ├── histogram_widget.py  ← histograma matplotlib embutido (FigureCanvasQTAgg)
│   │   └── dialogs.py           ← todos os diálogos de parâmetros
│   └── utils/
│       └── image_utils.py       ← load_image, save_image, image_info
└── exemplos-python/             ← exemplos do professor (referência de implementação)
    ├── brilho/hsi_rgb_conv.py
    ├── constraste/
    ├── equalizacao_hist/
    ├── especificacao_hist/
    └── limiarizacao/
```

---

## Convenções internas

- **Formato de imagem interno:** `numpy.ndarray` RGB `uint8` (ou grayscale 2D `uint8`).
- **OpenCV lê/salva em BGR** – `load_image` converte para RGB na entrada; `save_image` converte de volta para BGR na saída.
- **Processamento em float64:** todas as funções de `processing/` recebem uint8 e retornam uint8; internamente usam `float64` para evitar overflow/clipping prematuro.
- **Operações pesadas rodam em `_Worker(QThread)`** dentro de `main_window.py` para não travar a GUI.
- **Undo/Redo:** pilha `_history` (máx 20) + `_redo`. Cada `_apply()` faz push automático antes de processar.

---

## Módulo `processing/`

### `color_conversion.py`
| Função | Descrição |
|---|---|
| `rgb2hsi(img)` | RGB [0-255] → HSI [0-255]. Equações exatas do curso (arccos, setor B>G). |
| `hsi2rgb(img)` | HSI [0-255] → RGB [0-255]. 3 setores com cos(π/3 − h). |

### `resampling.py`
| Função | Descrição |
|---|---|
| `nearest_neighbor(img, sh, sw)` | Implementação manual vetorizada com `np.ix_`. |
| `bilinear(img, sh, sw)` | Fórmula do curso: J=Ia(1-dr)(1-dc)+Ib·dr(1-dc)+Ic(1-dr)dc+Id·dr·dc. Vetorizado. |
| `resize_cv2(img, sh, sw, method)` | Wrapper cv2.resize. method: 'nearest'\|'linear'\|'cubic'\|'lanczos'. |

### `intensity.py`
| Função | Parâmetros chave |
|---|---|
| `brightness_additive(img, c)` | Soma c em cada canal RGB. |
| `brightness_multiplicative(img, c)` | Multiplica c em cada canal. |
| `brightness_hsi(img, c)` | Ajusta canal I no espaço HSI (preserva cromaticidade). |
| `negative(img)` | s = 255 − r. |
| `log_transform(img, c)` | g = c·log(1+f). c padrão = 255/log(256). |
| `exp_transform(img, c)` | g = (exp(f·c)−1)/(exp(c)−1). |
| `gamma_transform(img, gamma, c)` | g = c·f^γ. c padrão normaliza para [0,255]. |
| `piecewise_linear(img, r1,s1, r2,s2)` | 3 segmentos. Pontos de controle definidos pelo usuário. |
| `threshold_binary(img, a, b)` | [a,b]→255; resto→0. |
| `threshold_preserve(img, a, b)` | [a,b] destaca em amarelo; resto preservado. |
| `threshold_color_cube(img, ref, w)` | Cubo 3D centrado em ref_color, lado w. Fora→cinza 128. |
| `threshold_color_sphere(img, ref, r)` | Esfera 3D raio r. Fora→cinza 128. |

### `histogram_ops.py`
| Função | Descrição |
|---|---|
| `equalize_global(img)` | CDF: Sk=(L−1)·Σpr[0..k]. Cor: apenas canal I no HSI. |
| `histogram_matching(img, ref)` | z=G⁻¹(S(r)). LUT por canal. |
| `equalize_local(img, ksize)` | Janela deslizante ksize×ksize. Lento em imagens grandes (loop Python). |

### `filters.py`
| Função | Parâmetros chave |
|---|---|
| `apply_filter(img, kernel, padding, convolve)` | correlação ou convolução (rot90 180°). |
| `box_filter(img, ksize, padding, separable, convolve)` | separable=True usa `cv2.sepFilter2D` (2× passes 1D). |
| `gaussian_filter(img, sigma, padding, separable, convolve)` | ksize=⌈6σ⌉ (sempre ímpar). Separável por padrão. |
| `median_filter(img, ksize)` | `cv2.medianBlur`. Não-linear. |
| `laplacian_sharpen(img, kernel_type, c, padding)` | kernel_type: '4-conn'\|'8-conn'\|'4-conn+'\|'8-conn+'. g=f+c·∇²f. |
| `sobel_sharpen(img, c, padding)` | g=f+c·√(Gx²+Gy²). |
| `unsharp_mask(img, sigma, c, padding)` | o=f+c·(f−blur(f)). |

**Padding options:** `'zero'`, `'reflect'` (padrão), `'replicate'`, `'wrap'`.

---

## Módulo `ui/`

### `main_window.py` – `MainWindow`
- Menu completo: Arquivo / Editar / Reamostrar / Brilho / Contraste / Limiarização / Histograma / Filtros / Ver
- Atalhos: `Ctrl+O` abrir, `Ctrl+S` salvar, `Ctrl+Z` desfazer, `Ctrl+Y` refazer, `Ctrl+=` zoom+, `Ctrl+-` zoom−, `Ctrl+0` ajustar, `Ctrl+1` 100%
- Zoom: botões no painel direito + `Ctrl+Scroll`
- `_apply(fn, *args, label="Operação", **kwargs)`: método central — push history + roda `fn` em `_Worker` thread + atualiza `_current_label` e reconstrói painel de histórico no `on_done`
- Imagem exibida via `QLabel` dentro de `QScrollArea`

#### Painel de Histórico Visual (sidebar direita)
- `HistoryItemWidget(index, img, label, is_current)`: card com thumbnail 76×57, label da operação, botão "Restaurar" (oculto se `is_current`)
- `_history_labels: list[str]` — paralelo a `_history`, armazena nome do estado salvo
- `_redo_labels: list[str]` — paralelo a `_redo`
- `_current_label: str` — nome do estado atual (ex: "Original", "Gamma γ=0.5")
- `_rebuild_history_panel()` — limpa e reconstrói todos os cards; chamado após cada operação, undo, redo, restore e open
- `_restore_from_history(idx)` — salta para `_history[idx]`; estados posteriores vão para redo (Ctrl+Y funciona após restore)
- `_push_history(state_label)` — salva `(_image, state_label)` antes de cada operação; limpa redo
- Lógica undo: `_redo.append(current)`, `_image = _history.pop()`, `_current_label = _history_labels.pop()`
- Lógica redo: `_history.append(current)`, `_image = _redo.pop()`, `_current_label = _redo_labels.pop()`

### `histogram_widget.py` – `HistogramWidget`
- Matplotlib `FigureCanvasQTAgg` embutido no painel direito
- Grayscale: histograma cinza; Color: 3 canais sobrepostos (R/G/B)

### `dialogs.py`
Cada diálogo herda `_BaseDialog` e expõe `.values()` retornando os parâmetros prontos para passar ao processamento.

| Diálogo | Retorno de `.values()` |
|---|---|
| `ResampleDialog` | `(scale_h, scale_w, mode, cv2_flag)` |
| `BrightnessDialog` | `(mode_str, constant)` |
| `LogTransformDialog` | `c: float` |
| `ExpTransformDialog` | `c: float` |
| `GammaDialog` | `gamma: float` |
| `PiecewiseDialog` | `(r1, s1, r2, s2)` |
| `ThresholdGrayDialog` | `(a, b)` |
| `ThresholdColorDialog` | `(ref_color_tuple, param)` |
| `LocalEqualDialog` | `ksize: int` |
| `HistMatchDialog` | `ref_path: str` |
| `FilterDialog` | `(ksize_or_sigma, padding, separable, convolve)` |
| `MedianDialog` | `ksize: int` |
| `LaplacianDialog` | `(kernel_type, c, padding)` |
| `SobelDialog` | `(c, padding)` |
| `UnsharpDialog` | `(sigma, c, padding)` |

---

## Dependências (venv)

```
numpy>=2.4
opencv-python>=4.13
PyQt5>=5.15
matplotlib>=3.10
scipy>=1.17
```

Instalar: `venv/bin/pip install -r photoshop/requirements.txt`

---

## O que ainda pode ser adicionado

- **Adicionar ruído** (gaussiano, sal-e-pimenta) para testar filtros
- **Visualização do gradiente** (Gx, Gy, magnitude separados)
- **Preview em tempo real** com slider (ex: gamma, brilho) antes de confirmar
- **Converter para grayscale** (menu Editar)
- **Comparação lado a lado** original vs processado
- **Export de histograma** como PNG
- **Barra de progresso** para `equalize_local` (loop puro Python, lento)
- **Testes unitários** em `tests/` cobrindo todas as funções de `processing/`
