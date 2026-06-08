# Roteiro de Revisão — Apresentação PhotoPy

---

## 1. Fluxo geral para demonstrar

**Ordem sugerida na demo:**
1. Abrir uma imagem (ex: `cat_puppy.jpg`)
2. Mostrar histograma atualizado na sidebar
3. Aplicar Gamma (γ=0.4) → ver mudança visual + histograma
4. Aplicar Gaussiano σ=2 → suavização
5. Aplicar Laplaciano → aguçamento
6. Mostrar painel de histórico → clicar Restaurar
7. Salvar (Ctrl+S) → explicar que salva como `_editada`

---

## 2. Módulos — o que saber de cada um

### 2.1 `color_conversion.py` — RGB ↔ HSI

**H (Matiz):**
```
θ = arccos( 0.5·[(R−G)+(R−B)] / sqrt((R−G)²+(R−B)(G−B)) )
H = θ        se B ≤ G
H = 360°−θ   se B > G
```

**S (Saturação):**
```
S = 1 − (3 / (R+G+B)) · min(R,G,B)
```

**I (Intensidade):**
```
I = (R + G + B) / 3
```

**Por que HSI importa no projeto:**
- Brilho HSI ajusta só canal I → cromaticidade (cor) preservada
- Equalização de histograma em cor → aplica só no canal I → evita distorção de cor
- Se equalizasse RGB independentemente, as proporções entre canais mudariam → cor errada

**Implementação:** normaliza para [0,1] antes de calcular, retorna [0,255]. Usa `1e-6` no denominador para evitar divisão por zero. `np.clip` no arccos para evitar NaN.

---

### 2.2 `resampling.py` — Reamostrar

#### Vizinho Mais Próximo
Mapeamento **inverso**: para cada pixel `(r,c)` da saída, calcula a coordenada correspondente na entrada e arredonda.

```
r_orig = round(r × (H_orig / H_nova))
c_orig = round(c × (W_orig / W_nova))
J(r,c) = I(r_orig, c_orig)
```

**Por que mapeamento inverso (não direto)?**
Mapeamento direto deixa buracos na saída (pixels sem valor). Inverso garante que todo pixel de saída recebe um valor.

#### Bilinear
Usa os **4 vizinhos** do ponto mapeado:

```
J(r,c) = I(r0,c0)·(1-Δr)·(1-Δc)
       + I(r0+1,c0)·Δr·(1-Δc)
       + I(r0,c0+1)·(1-Δr)·Δc
       + I(r0+1,c0+1)·Δr·Δc
```

Onde `Δr = r_mapeado − r0` e `Δc = c_mapeado − c0` (partes fracionárias).

**Diferença visual:** bilinear é mais suave; vizinho mais próximo tem efeito de "blocos" (pixelado) ao ampliar.

**Por que float64 na bilinear e não no vizinho?**
Bilinear faz médias ponderadas (valores intermediários). Vizinho mais próximo só copia pixels inteiros — não há cálculo fracionário.

---

### 2.3 `intensity.py` — Transformações Pontuais

Toda função recebe `uint8`, converte para `float64`, processa, clipa `[0,255]`, retorna `uint8`.

#### Brilho aditivo
```
g = clip(f + c, 0, 255)
```
c > 0 clareia, c < 0 escurece. Muda o ponto de preto.

#### Brilho multiplicativo
```
g = clip(f × c, 0, 255)
```
c > 1 clareia, 0 < c < 1 escurece. Preserva proporção entre canais (não muda a cor, só o ganho).

#### Negativo
```
g = 255 − f
```
Para RGB: cada canal vira seu complementar (vermelho → ciano, verde → magenta, azul → amarelo).

#### Transformação Logarítmica
```
g = c · log(1 + f)       c = 255 / log(256)
```
**Efeito:** comprime altas intensidades, expande baixas → revela detalhes em regiões escuras.
**Uso típico:** visualizar resultado de DFT (espectro de Fourier tem valores muito discrepantes).

#### Transformação Exponencial
```
g = (exp(f·c) − 1) / (exp(c) − 1)   (normalizada para [0,255])
```
**Efeito:** inverso do log → expande regiões claras, comprime escuras.

#### Correção Gamma (Power-Law)
```
g = c · f^γ       c = 255 / 255^γ   (normaliza saída)
```
- **γ < 1** → comportamento logarítmico (clareia, expande escuros)
- **γ > 1** → comportamento exponencial (escurece, expande claros)
- **γ = 1** → identidade
- **Uso real:** correção de monitor (display gamma), imagens médicas

#### Linear por Partes
3 segmentos definidos por pontos `(r1,s1)` e `(r2,s2)`:
```
Segmento 1: [0, r1]    → [0, s1]       inclina = s1/r1
Segmento 2: [r1, r2]   → [s1, s2]      inclina = (s2-s1)/(r2-r1)
Segmento 3: [r2, 255]  → [s2, 255]     inclina = (255-s2)/(255-r2)
```
**Uso:** ampliar faixa dinâmica específica (ex: destacar tons médios), comprimir ruído em sombras.

#### Limiarização Binária
```
g = 255  se A ≤ f ≤ B
g = 0    caso contrário
```

#### Limiarização com Preservação
```
g = amarelo(255,255,0)  se A ≤ f ≤ B    (destaque)
g = f                   caso contrário   (preserva)
```

#### Limiarização por Cubo (RGB 3D)
```
|R − R_ref| ≤ W/2  AND  |G − G_ref| ≤ W/2  AND  |B − B_ref| ≤ W/2
→ mantém; fora → cinza 128
```

#### Limiarização por Esfera (RGB 3D)
```
sqrt((R−Rr)² + (G−Gr)² + (B−Br)²) ≤ R₀
→ mantém; fora → cinza 128
```
**Diferença cubo vs esfera:** cubo testa cada canal separado (mais rápido, menos preciso geometricamente); esfera usa distância euclidiana no espaço RGB (mais fiel à percepção de "cor similar").

---

### 2.4 `histogram_ops.py` — Processamento de Histograma

#### Equalização Global
```
S_k = (L−1) · Σ_{j=0}^{k} p_r(j)     L = 256
```
`p_r(j)` = frequência relativa do nível j = hist[j] / (H×W).
`S_k` = LUT de mapeamento (cada nível k vai para S_k).

**Para imagens coloridas:** aplica equalização **apenas no canal I** do espaço HSI. Se aplicasse em R, G, B separadamente, mudaria as proporções entre canais → distorção de cor.

#### Casamento de Histograma (Especificação)
Dado: imagem `img` e referência `ref`.
```
1. Calcula CDF_src de img
2. Calcula CDF_ref de ref
3. Para cada nível i: z = argmin_j |CDF_ref[j] − CDF_src[i]|
4. LUT[i] = z
```
**Intuição:** encontra qual nível `z` na referência tem a mesma probabilidade acumulada que o nível `i` na fonte. Isso "força" o histograma da saída a ter o mesmo perfil da referência.

#### Equalização Local
Janela deslizante `ksize×ksize`. Para cada pixel `(r,c)`:
- Extrai vizinhança de ksize×ksize ao redor de `(r,c)`
- Calcula CDF local dessa vizinhança
- Mapeia `f(r,c)` usando essa CDF local

**Vantagem:** realça detalhes locais e texturas que a equalização global apaga.
**Desvantagem:** muito lento (loop Python pixel a pixel) — implementação didática, não otimizada.

---

### 2.5 `filters.py` — Filtragem Espacial

#### Conceito fundamental: correlação vs convolução
- **Correlação:** aplica kernel diretamente na vizinhança
- **Convolução:** rotaciona kernel 180° antes de aplicar
- Para kernels simétricos (Box, Gaussiano): resultado idêntico
- Para kernels assimétricos (Sobel): resulta diferente
- Implementado via flag `convolve=True` → `np.rot90(kernel, 2)`

#### Padding (bordas)
| Tipo | Comportamento |
|---|---|
| `zero` | Preenche com 0 (cria borda escura) |
| `reflect` | Espelha pixels da borda (padrão, mais natural) |
| `replicate` | Repete o pixel da extremidade |
| `wrap` | Envolve (trata como periódica) |

#### Filtro Box (Média)
```
kernel = [[1/9, 1/9, 1/9],
          [1/9, 1/9, 1/9],    (para 3×3)
          [1/9, 1/9, 1/9]]
```
**Kernels separáveis:** Box 3×3 = vetor coluna [1/3,1/3,1/3] × vetor linha [1/3,1/3,1/3]. Aplica-se em 2 passes 1D em vez de 1 passe 2D → complexidade O(m) + O(n) em vez de O(m×n) por pixel.

#### Filtro Gaussiano
```
G(x,y) = (1/2πσ²) · exp(−(x²+y²)/2σ²)
```
- Tamanho do kernel: `⌈6σ⌉` (captura ±3σ de cada lado)
- Também separável: G(x,y) = G(x) × G(y)
- Parâmetro σ controla grau de suavização
- Preserva bordas melhor que Box (pesos maiores no centro)

#### Filtro Mediana
- **Não-linear:** ordena os pixels da vizinhança, pega o do meio
- Não usa kernel, não é convolução
- **Excelente para ruído sal-e-pimenta** (impulsos isolados)
- Preserva bordas melhor que filtros lineares
- `cv2.medianBlur` — implementado em C (rápido)

#### Laplaciano (segunda derivada)
Máscaras 4-conectado e 8-conectado:
```
4-conn:  [ 0  1  0]      8-conn:  [1  1  1]
         [ 1 -4  1]               [1 -8  1]
         [ 0  1  0]               [1  1  1]
```
Aguçamento: `g = f + c·∇²f`
- Centro negativo (−4, −8): c deve ser negativo (ex: c=−1)
- Centro positivo (+4, +8): c positivo
- Realça transições abruptas (bordas, detalhes finos)

#### Gradiente Sobel (primeira derivada)
```
Gx = [−1 −2 −1]    Gy = [−1  0  1]
     [ 0  0  0]         [−2  0  2]
     [ 1  2  1]         [−1  0  1]
```
Magnitude: `M = sqrt(Gx² + Gy²)`
Aguçamento: `g = f + c·M`

**Diferença Laplaciano vs Sobel:**
- Laplaciano: segunda derivada, isotrópico, detecta bordas em todas direções igualmente
- Sobel: primeira derivada, detecta direção do gradiente (Gx = bordas verticais, Gy = horizontais)

#### Unsharp Masking
```
1. f_blur = Gaussiano(f, σ)
2. mask   = f − f_blur       (camada de detalhes)
3. saída  = f + c · mask
```
**Intuição:** a parte suavizada é o "sinal baixo". Subtraindo, sobra só os detalhes (altas frequências). Soma de volta amplificados.

---

## 3. Arquitetura do código — perguntas prováveis

**"Por que separar em processing/, ui/, utils/?"**
Separação de responsabilidades: algoritmos de processamento não dependem de PyQt5. É possível usar os algoritmos em scripts sem GUI, testar isoladamente, ou trocar a interface sem reescrever os filtros.

**"Por que usar QThread para as operações?"**
PyQt5 é single-threaded por padrão. Operações pesadas (equalização local, bilinear em imagens grandes) travariam a interface. `_Worker(QThread)` roda o processamento em thread separada; `finished` signal comunica o resultado de volta à thread principal de forma thread-safe.

**"Por que float64 internamente e uint8 para salvar/exibir?"**
`uint8` tem range [0,255]. Operações intermediárias (soma, multiplicação, potência) podem extrapolar esse range. Em float64 os valores ficam no range correto; só no final o `np.clip + astype(uint8)` aplica saturação. Se fizesse tudo em uint8, haveria overflow silencioso (255+1=0 em uint8).

**"O que é o painel de histórico? Como funciona o Restaurar?"**
- `_history: list[ndarray]` armazena cópias da imagem antes de cada operação
- `_history_labels: list[str]` armazena o nome de cada estado
- Restaurar para `history[i]`: define `_image = history[i]`, trunca histórico em `[:i]`, move estados posteriores + estado atual para `_redo` (Ctrl+Y ainda funciona)

**"Como funciona o Salvar?"**
- Ctrl+S: na primeira vez, gera `arquivo_editada.ext` no mesmo diretório do original (nunca sobrescreve o original). Nas vezes seguintes, salva no caminho gerado.
- Ctrl+Shift+S: "Salvar Como" normal com diálogo.
- OpenCV salva em BGR → `save_image` converte RGB→BGR antes de `cv2.imwrite`.

---

## 4. Perguntas mais prováveis do professor

### Sobre reamostragem
- **"Qual a diferença entre interpolação bilinear e vizinho mais próximo?"** → bilinear usa média ponderada de 4 vizinhos, produz resultado mais suave; vizinho copia o pixel mais próximo, mais rápido mas produz artefatos ao ampliar.
- **"O que é mapeamento inverso?"** → mapeia coordenadas da saída para a entrada (não o contrário), garantindo que todo pixel de saída receba um valor.
- **"Por que a bicúbica (cv2) é melhor que a bilinear manual?"** → bicúbica usa 16 vizinhos e polinômio cúbico, preserva melhor bordas e gradientes suaves.

### Sobre espaço HSI
- **"Por que converter para HSI para ajustar brilho?"** → no RGB, aumentar todos os canais muda a cor. No HSI, ajustar só I mantém H (matiz) e S (saturação) intocados → cor percebida não muda.
- **"Dê a fórmula de I."** → `I = (R+G+B)/3`
- **"Por que equalizar histograma colorido no canal I?"** → Se equalizasse R, G, B separados, mudaria a relação entre canais → tom/saturação se distorcem. Equalizar só I muda contraste sem alterar a cromaticidade.

### Sobre filtros
- **"Por que o filtro mediana é melhor para ruído sal-e-pimenta do que o filtro gaussiano?"** → Sal-e-pimenta são impulsos isolados (0 ou 255). A mediana, sendo estatística de ordem, descarta os outliers. A média (gaussiano) os inclui no cálculo → borrado mas ruído persiste.
- **"O que é um kernel separável?"** → kernel 2D que pode ser decomposto em produto externo de dois vetores 1D. Permite aplicar 2 filtragens 1D sequenciais. Ganho de O(m·n) para O(m+n) por pixel.
- **"Qual a diferença entre convolução e correlação?"** → convolução rotaciona o kernel 180° antes de aplicar. Para kernels simétricos (Box, Gaussiano) o resultado é idêntico. Matematicamente, convolução é comutativa.
- **"Por que o laplaciano usa segunda derivada?"** → primeira derivada detecta rampa (transição gradual); segunda derivada detecta a mudança na rampa (pico/vale) → posiciona a borda com mais precisão. Zero-crossing da segunda derivada = localização da borda.

### Sobre histograma
- **"Explique a fórmula de equalização."** → `Sk = (L−1)·CDF(k)`. A CDF é monotonicamente crescente de 0 a 1. Multiplicada por 255 e arredondada, mapeia cada nível de intensidade para o novo nível que "uniformiza" a distribuição.
- **"O que o histograma equalizado garante teoricamente?"** → histograma uniforme (todas intensidades com mesma frequência). Na prática, com 256 níveis discretos, apenas aproximado.
- **"O que é casamento de histograma?"** → encontra mapeamento `LUT[i] = z` tal que `CDF_ref[z] ≈ CDF_src[i]`. Força a distribuição de intensidades da saída a imitar a da referência.
- **"Por que a equalização local revela mais detalhes?"** → usa o contexto local de cada pixel. Regiões com baixo contraste localmente recebem maior "esticamento" de histograma, revelando textura que a equalização global (que usa estatísticas globais) não conseguiria.

### Sobre implementação
- **"Por que usar `np.ix_` no vizinho mais próximo?"** → cria índices de broadcasting para indexação fancy 2D sem loops. `arr[np.ix_(R, C)]` seleciona as linhas R e colunas C gerando matriz (nh × nw) de uma vez.
- **"O que é o `1e-6` e `1e-9` no código?"** → epsilon para evitar divisão por zero (denominadores que podem ser 0 matematicamente, como no cálculo do ângulo H quando todos R=G=B).
- **"Como o histórico de desfazer funciona?"** → pilha de cópias do array numpy. `_push_history` antes de cada operação. `undo` troca `_image` com o topo da pilha. Máximo 20 entradas para limitar memória RAM.

---

## 5. Pontos fracos — saiba responder

| Ponto | Resposta honesta |
|---|---|
| Equalização local lenta | "Implementação didática com loop Python puro — equivalente ao algoritmo do curso. Poderia usar `cv2.createCLAHE` em produção." |
| Bilinear manual mais lenta que cv2 | "Vetorizado com numpy mas ainda Python. cv2 é C compilado. A implementação manual está aqui para fins didáticos, por isso o menu oferece ambas." |
| Sem desfazer ilimitado | "Limitado a 20 estados por RAM. Cópia completa do numpy array a cada operação." |
| Sem preview em tempo real | "Não implementado — operações são aplicadas ao confirmar o diálogo." |

---

## 6. Checklist antes da apresentação

- [ ] Abrir uma imagem e mostrar histograma atualizando
- [ ] Demonstrar Gamma γ=0.3 vs γ=3.0 (efeitos opostos)
- [ ] Demonstrar Log em imagem escura (ex: `fractured_spine.tif`)
- [ ] Demonstrar Bilinear manual vs cv2 cúbico na ampliação (×2)
- [ ] Equalização global em imagem de baixo contraste (ex: `low_contrast_pollen.tif`)
- [ ] Casamento de histograma com imagem de referência
- [ ] Box vs Gaussiano vs Mediana com ruído
- [ ] Laplaciano e Unsharp Masking para aguçamento
- [ ] Mostrar painel histórico + Restaurar
- [ ] Salvar como `_editada`
- [ ] Saber explicar cada fórmula sem olhar o código
