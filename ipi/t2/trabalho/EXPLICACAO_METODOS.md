# Explicação dos Métodos – PhotoPy (T2 IPI/UFMT)

Documento de referência explicando a lógica matemática e de implementação de cada função do módulo `processing/`.

---

## 1. `color_conversion.py` — Conversão RGB ↔ HSI

O espaço de cor **HSI** (Hue, Saturation, Intensity) separa a informação de luminosidade (I) das cores (H e S), o que permite manipular brilho sem distorcer as cores.

---

### `rgb2hsi(image)`

Converte uma imagem RGB [0–255] para HSI [0–255].

**Passo a passo:**

1. **Normaliza** os canais R, G, B para o intervalo [0, 1] dividindo por 255.

2. **Intensidade (I):**
   ```
   I = (R + G + B) / 3
   ```
   Média aritmética dos três canais.

3. **Saturação (S):**
   ```
   S = 1 - (3 / (R+G+B+ε)) * min(R, G, B)
   ```
   Quanto maior a diferença entre o canal mínimo e a média, maior a saturação. O `ε = 1e-6` evita divisão por zero em pixels pretos.

4. **Matiz (H):**
   ```
   θ = arccos( 0.5*((R-G)+(R-B)) / sqrt((R-G)²+(R-B)(G-B)) + ε )
   ```
   - Se `B > G`: `H = 2π − θ` (cobre o segundo hemisfério do círculo de cores)
   - Normaliza para [0, 1] dividindo por `2π`

5. Empilha (H, S, I) e multiplica por 255 para retornar no mesmo intervalo da entrada.

---

### `hsi2rgb(image)`

Conversão inversa: HSI [0–255] → RGB [0–255].

A matiz é dividida em **3 setores** de 120° cada (2π/3 radianos):

| Setor | Intervalo de H | Canal fixo |
|---|---|---|
| 1 | [0°, 120°) | B fixo |
| 2 | [120°, 240°) | R fixo |
| 3 | [240°, 360°) | G fixo |

**Fórmula do Setor 1** (exemplo):
```
B = I * (1 - S)
R = I * (1 + S * cos(H) / cos(π/3 - H))
G = 3I - (R + B)
```
Os setores 2 e 3 usam a mesma fórmula com H deslocado de 120° e 240° respectivamente, trocando qual canal é o "fixo".

Ao final, multiplica por 255 e aplica `clip(0, 255)` para garantir valores válidos de uint8.

---

## 2. `resampling.py` — Reamostramento (Redimensionamento)

Todas as funções recebem `scale_h` e `scale_w` (fatores de escala) e calculam o novo tamanho como `round(H * scale_h)` e `round(W * scale_w)`.

---

### `nearest_neighbor(img, scale_h, scale_w)`

Interpolação por **vizinho mais próximo**: para cada pixel de destino, mapeia de volta para a coordenada de origem e arredonda para o pixel inteiro mais próximo.

**Mapeamento inverso:**
```
sr = H_original / H_novo       sc = W_original / W_novo
R[i] = round(i * sr)           C[j] = round(j * sc)
```

Usa `np.ix_(R, C)` para indexação vetorizada eficiente (sem loop Python), evitando iteração pixel a pixel.

**Característica:** rápido, mas gera efeito "degrau" (pixelado) em ampliações.

---

### `bilinear(img, scale_h, scale_w)`

Interpolação **bilinear**: estima o valor do pixel de destino como média ponderada dos 4 vizinhos mais próximos na imagem original.

**Mapeamento inverso (coordenada contínua):**
```
rm[i] = i * sr        cm[j] = j * sc
r0 = floor(rm)        c0 = floor(cm)
dr = rm - r0          dc = cm - c0
```

**Fórmula de interpolação:**
```
J = Ia*(1-dr)*(1-dc) + Ib*dr*(1-dc) + Ic*(1-dr)*dc + Id*dr*dc
```
Onde:
- `Ia = img[r0, c0]` — canto superior esquerdo
- `Ib = img[r0+1, c0]` — canto inferior esquerdo
- `Ic = img[r0, c0+1]` — canto superior direito
- `Id = img[r0+1, c0+1]` — canto inferior direito

Os pesos `dr` e `dc` são as distâncias fracionárias até o vizinho seguinte. A implementação usa broadcasting numpy para calcular todos os pixels simultaneamente.

**Característica:** resultado suave, sem artefatos de degrau. Mais lento que nearest neighbor, mas muito mais rápido que bicúbico.

---

### `bicubic(img, scale_h, scale_w)`

Wrapper direto para `cv2.INTER_CUBIC`. Usa polinômios cúbicos considerando uma vizinhança 4×4. Não há implementação manual aqui.

---

## 3. `intensity.py` — Transformações de Intensidade

Todas operam pixel a pixel (transformações pontuais). A imagem é convertida para `float64` antes das operações e clampada de volta para `uint8` [0, 255] no final.

---

### `brightness_additive(img, c)`

```
s = r + c
```
Soma a constante `c` em todos os canais RGB. `c > 0` clareia, `c < 0` escurece.

---

### `brightness_multiplicative(img, c)`

```
s = r * c
```
Multiplica todos os canais por `c`. `c > 1` clareia, `0 < c < 1` escurece.

---

### `brightness_hsi(img, c)`

Ajusta o brilho operando **apenas no canal I** do espaço HSI:
```
I_novo = clip(I + c, 0, 255)
```
Vantagem: preserva a cromaticidade (H e S inalterados), então as cores não se distorcem ao clarear/escurecer. Para imagens grayscale, age como `brightness_additive`.

---

### `negative(img)`

```
s = 255 - r
```
Inverte cada canal: pixels claros ficam escuros e vice-versa. Gera o negativo fotográfico da imagem.

---

### `log_transform(img, c)`

```
s = c * log(1 + r)
```
O padrão usa `c = 255 / log(256)` para normalizar o resultado ao intervalo [0, 255].

**Efeito:** comprime a faixa dos tons altos e expande os tons escuros — realça detalhes em regiões escuras da imagem.

---

### `exp_transform(img, c)`

```
f = r / 255          (normaliza para [0,1])
s = (exp(f*c) - 1) / (exp(c) - 1) * 255
```

**Efeito:** oposto ao logarítmico — expande tons altos (realça regiões claras) e comprime tons escuros. Útil para imagens com detalhes na parte clara do histograma.

---

### `gamma_transform(img, gamma, c)`

```
s = c * r^gamma
```
O padrão usa `c = 255 / 255^gamma` para normalizar a saída.

- `gamma < 1`: clareia a imagem (curva côncava para cima)
- `gamma > 1`: escurece a imagem (curva côncava para baixo)
- `gamma = 1`: identidade

É a transformação de **lei de potência** (Power-Law). Muito usada em correção de gamma de monitores.

---

### `piecewise_linear(img, r1, s1, r2, s2)`

Define uma transformação linear por partes com 3 segmentos, controlados pelos pontos `(r1, s1)` e `(r2, s2)`:

| Segmento | Entrada | Saída | Inclinação |
|---|---|---|---|
| 1 | [0, r1] | [0, s1] | s1/r1 |
| 2 | [r1, r2] | [s1, s2] | (s2-s1)/(r2-r1) |
| 3 | [r2, 255] | [s2, 255] | (255-s2)/(255-r2) |

Permite criar contrastes seletivos: pode-se esticar uma faixa de tons e comprimir as demais.

---

### `threshold_binary(img, a, b)`

```
s = 255  se  a < media_rgb < b
s = 0    caso contrário
```
Converte a imagem para grayscale internamente (média dos canais), depois binariza: pixels dentro do intervalo `(a, b)` viram branco, o resto vira preto.

---

### `threshold_preserve(img, a, b)`

Igual ao binário, mas **preserva a imagem original** fora da faixa e destaca os pixels dentro do intervalo `(a, b)` em **amarelo** (255, 255, 0).

---

### `threshold_color_cube(img, ref_color, w)`

Segmentação de cor no espaço RGB usando um **cubo** de lado `w` centrado em `ref_color = (R, G, B)`.

Condição de pertencimento:
```
|r - Rref| ≤ w/2  AND  |g - Gref| ≤ w/2  AND  |b - Bref| ≤ w/2
```
Pixels **dentro** do cubo são preservados; pixels **fora** viram cinza (128).

---

### `threshold_color_sphere(img, ref_color, radius)`

Igual ao cubo, mas usa distância **Euclidiana** no espaço 3D RGB:

```
dist = sqrt((r-Rref)² + (g-Gref)² + (b-Bref)²)
```
Pixels com `dist ≤ radius` são preservados; o resto vira cinza (128).

**Diferença cubo vs esfera:** o cubo pode incluir cores diagonalmente distantes da referência (cantos do cubo). A esfera é geometricamente mais precisa e simétrica na seleção de cores similares.

---

## 4. `histogram_ops.py` — Operações de Histograma

---

### `_equalize_channel(ch)` *(privada)*

Equalização de um único canal via **CDF (Função de Distribuição Acumulada)**:

```
pr[k] = histograma[k] / (H * W)     (probabilidade de cada nível)
CDF[k] = Σ pr[0..k]                 (acumulado)
Sk = round(255 * CDF[k])            (mapeamento)
```
O resultado é uma LUT (Lookup Table) de 256 entradas que redistribui os níveis de intensidade para preencher uniformemente o histograma de saída.

---

### `equalize_global(img)`

**Equalização global do histograma:**

- **Grayscale:** aplica `_equalize_channel` diretamente.
- **Colorida:** converte para HSI, equaliza **somente o canal I** (intensidade), e converte de volta para RGB.

Equalizar em RGB diretamente distorceria as cores. Usando HSI, mantemos a tonalidade e saturação intactas.

---

### `histogram_matching(img, ref)` — Especificação de Histograma

Transforma o histograma de `img` para que se assemelhe ao histograma da imagem de referência `ref`.

**Algoritmo (por canal):**
1. Calcula `S(r)` = CDF acumulada da imagem fonte.
2. Calcula `G(z)` = CDF acumulada da imagem referência.
3. Para cada nível `i` de entrada, encontra o nível `z` tal que `G(z) ≈ S(i)`:
   ```
   lut[i] = argmin_z |G(z) - S(i)|
   ```
4. Aplica a LUT: `saida = lut[entrada]`.

Para imagens coloridas, o processo é feito canal a canal (R, G, B independentemente).

---

### `equalize_local(img, ksize)` — Equalização Local

Em vez de usar o histograma global, aplica a equalização dentro de uma **janela deslizante** `ksize × ksize` centrada em cada pixel.

**Para cada pixel (r, c):**
1. Extrai a região `[r-pad:r+pad, c-pad:c+pad]` da imagem com padding `reflect`.
2. Calcula o histograma e CDF locais dessa janela.
3. Mapeia o valor do pixel central usando essa CDF local.

**Efeito:** realça detalhes locais que seriam perdidos na equalização global, pois cada região tem sua própria redistribuição de contraste.

**Limitação:** implementado com loop Python duplo — muito lento para imagens grandes (O(H×W×ksize²)). Por isso é executado em `QThread` na UI.

---

## 5. `filters.py` — Filtros Espaciais

---

### `apply_filter(img, kernel, padding, convolve)`

Função base que aplica um kernel arbitrário usando `cv2.filter2D`.

- **Correlação** (padrão, `convolve=False`): desliza o kernel sobre a imagem sem rotacioná-lo.
- **Convolução** (`convolve=True`): rotaciona o kernel 180° antes (`np.rot90(k, 2)`) e então aplica.

Para kernels simétricos (como gaussiano, box), correlação e convolução produzem o mesmo resultado.

O mapa de borda `padding` define o tratamento das bordas:
- `'zero'`: preenche com zeros (escurece bordas)
- `'reflect'`: espelha pixels nas bordas (padrão, sem artefatos)
- `'replicate'`: repete o pixel da borda
- `'wrap'`: envolve (como tileamento)

---

### `box_filter(img, ksize, padding, separable, convolve)`

Filtro da média: substitui cada pixel pela média dos vizinhos em uma janela `ksize × ksize`.

**Kernel:**
```
K = [[1/k², 1/k², ...],
     [1/k², 1/k², ...], ...]     (ksize×ksize com soma = 1)
```

**Modo separável** (`separable=True`): o kernel 2D é decomposto em dois passes 1D:
```
K_2D = K_col × K_lin
```
Usa `cv2.sepFilter2D` que aplica um vetor horizontal e depois vertical. Complexidade: `O(k)` por pixel em vez de `O(k²)` — muito mais rápido para kernels grandes.

---

### `gaussian_filter(img, sigma, padding, separable, convolve)`

Filtro passa-baixa com pesos gaussianos:
```
G(x, y) = exp(-(x²+y²) / (2σ²))
```

O tamanho do kernel é calculado automaticamente como `ceil(6σ)` arredondado para ímpar (cobre 3σ de cada lado, o que captura ~99.7% da gaussiana).

**Modo separável:** o kernel gaussiano 2D é separável (`G(x,y) = G(x)·G(y)`), então dois passes 1D via `cv2.sepFilter2D` são matematicamente equivalentes e muito mais eficientes.

**Efeito:** suavização/desfoque. Quanto maior o `σ`, mais borrada fica a imagem.

---

### `median_filter(img, ksize)`

Filtro **não-linear**: substitui cada pixel pela **mediana** dos valores na vizinhança `ksize × ksize`.

Usa `cv2.medianBlur` diretamente. O `ksize` é forçado a ser ímpar.

**Vantagem sobre o box/gaussiano:** muito eficaz contra ruído **sal-e-pimenta** (pixels isolados com valor mínimo ou máximo), pois a mediana é resistente a outliers extremos.

---

### `laplacian_sharpen(img, kernel_type, c, padding)`

Realce por **Laplaciano** (segunda derivada discreta):
```
g = f + c * ∇²f
```

Disponibiliza 4 kernels:

| Tipo | Kernel | Conectividade |
|---|---|---|
| `'4-conn'` | `[0,1,0; 1,-4,1; 0,1,0]` | 4 vizinhos (N,S,L,O) |
| `'8-conn'` | `[1,1,1; 1,-8,1; 1,1,1]` | 8 vizinhos (inclui diagonais) |
| `'4-conn+'` | negado do 4-conn | mesmo, centro positivo |
| `'8-conn+'` | negado do 8-conn | mesmo, centro positivo |

- Kernels com **centro negativo** (padrão): usar `c < 0` (subtrai o laplaciano).
- Kernels com **centro positivo** (`+`): usar `c > 0` (soma o laplaciano).
- O laplaciano detecta bordas; somá-lo à imagem original realça os contornos.

---

### `sobel_sharpen(img, c, padding)`

Realce por gradiente de **Sobel** (primeira derivada):
```
M(x,y) = sqrt(Gx² + Gy²)
g = f + c * M
```

Os kernels Sobel calculam derivadas em X e Y:
```
Gx = [[-1,-2,-1],[0,0,0],[1,2,1]]
Gy = [[-1,0,1],[-2,0,2],[-1,0,1]]
```

A magnitude `M` é o mapa de bordas. Somar à imagem original com fator `c` enfatiza os contornos sem eliminar o conteúdo interno da imagem.

**Diferença do Laplaciano:** o Sobel usa derivada de 1ª ordem (detecta onde o gradiente é alto), enquanto o Laplaciano usa 2ª ordem (detecta onde o gradiente muda rapidamente). O Sobel é menos sensível a ruído.

---

### `unsharp_mask(img, sigma, c, padding)`

Máscara de nitidez não afiada (*Unsharp Masking*):
```
1. smooth = gaussian_filter(f, sigma)
2. mask   = f - smooth          (camada de detalhes)
3. output = f + c * mask
```

**Intuição:** `smooth` é uma versão borrada de `f`. A diferença `f - smooth` captura os detalhes de alta frequência (bordas, texturas finas). Somar esses detalhes amplificados por `c` de volta à imagem original aumenta a nitidez percebida.

É equivalente ao **filtro passa-alta implícito**: `output = (1+c)*f - c*smooth`.

---

## 6. UI — Visão Geral Rápida

| Arquivo | Responsabilidade |
|---|---|
| `main_window.py` | Janela principal: menus, undo/redo (pilha `_history`), zoom, painel de histórico visual, execução de operações em `QThread` via `_apply()` |
| `histogram_widget.py` | Exibe histograma matplotlib embutido no painel direito (grayscale ou RGB sobrepostos) |
| `dialogs.py` | Diálogos de parâmetros para cada operação; cada um herda `_BaseDialog` e expõe `.values()` |
| `utils/image_utils.py` | `load_image` (BGR→RGB), `save_image` (RGB→BGR), `image_info` |

O método central `_apply(fn, *args)` em `main_window.py` salva o estado atual no histórico, executa `fn` em uma `QThread` separada para não travar a interface, e atualiza a exibição ao concluir.

---

*Gerado para fins de estudo — T2 IPI/UFMT.*
