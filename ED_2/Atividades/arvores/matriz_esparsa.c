#include <stdio.h>
#include <stdlib.h>

typedef struct tempNo
{
  float valor;
  int coluna;
  struct tempNo *prox;
} NO;

typedef NO *PONT;

typedef struct
{
  PONT *A;
  int linhas;
  int colunas;
} MATRIZ;

MATRIZ *inicializarMatriz(int lin, int col)
{
  int i;

  MATRIZ *novo;

  novo = (MATRIZ *)malloc(sizeof(MATRIZ));

  novo->A = (PONT *)malloc(lin * sizeof(PONT));
  novo->linhas = lin;
  novo->colunas = col;
  for (i = 0; i < lin; i++)
    novo->A[i] = NULL;

  return novo;
}

void imprimeMatriz(MATRIZ *m)
{
  for (int l = 0; l < m->linhas; l++)
  {
    if (m->A[l] != NULL)
    {
      PONT c = m->A[l];
      while (c != NULL)
      {
        printf("  [%f|(%d,%d)]", c->valor, l, c->coluna);
        c = c->prox;
      }
      printf("\n");
    }
  }
}

// função que insere um valor na matriz
int insereMatriz(MATRIZ *m, int lin, int col, float val)
{
  // Verifica se os índices lin e col estão dentro dos limites da matriz
  if (lin < 0 || lin >= m->linhas || col < 0 || col >= m->colunas)
  {
    printf("Erro: Índices fora dos limites da matriz.\n");
    return 0; // Falha na inserção
  }

  // Cria um novo nó para armazenar o valor
  PONT novo = (PONT)malloc(sizeof(NO));
  if (novo == NULL)
  {
    printf("Erro: Falha na alocação de memória.\n");
    return 0; // Falha na inserção
  }

  novo->valor = val;
  novo->coluna = col;

  // Insere o nó na lista encadeada correspondente à linha
  if (m->A[lin] == NULL || col < m->A[lin]->coluna)
  {
    novo->prox = m->A[lin];
    m->A[lin] = novo;
  }
  else
  {
    PONT atual = m->A[lin];
    PONT anterior = NULL;

    while (atual != NULL && col > atual->coluna)
    {
      anterior = atual;
      atual = atual->prox;
    }

    novo->prox = atual;
    anterior->prox = novo;
  }

  return 1; // Inserção bem-sucedida
}

// função que retorna o valor
float ValorMatriz(MATRIZ *m, int lin, int col)
{
  // Verifica se os índices lin e col estão dentro dos limites da matriz
  if (lin < 0 || lin >= m->linhas || col < 0 || col >= m->colunas)
  {
    printf("Erro: Índices fora dos limites da matriz.\n");
    return 0.0; // Valor padrão se a busca falhar
  }

  PONT atual = m->A[lin];

  // Procura o valor na lista encadeada correspondente à linha
  while (atual != NULL)
  {
    if (atual->coluna == col)
      return atual->valor;
    atual = atual->prox;
  }

  return 0.0; // Valor padrão se não encontrar o valor
}

int excluirMatriz(MATRIZ *m, int lin, int col)
{
  // Verifica se os índices lin e col estão dentro dos limites da matriz
  if (lin < 0 || lin >= m->linhas || col < 0 || col >= m->colunas)
  {
    printf("Erro: Índices fora dos limites da matriz.\n");
    return 0; // Falha na exclusão
  }

  PONT atual = m->A[lin];
  PONT anterior = NULL;

  // Procura o valor na lista encadeada correspondente à linha
  while (atual != NULL)
  {
    if (atual->coluna == col)
    {
      // Remove o nó da lista
      if (anterior == NULL)
        m->A[lin] = atual->prox;
      else
        anterior->prox = atual->prox;

      // Libera a memória alocada para o nó
      free(atual);

      return 1; // Exclusão bem-sucedida
    }

    anterior = atual;
    atual = atual->prox;
  }

  printf("Erro: Valor não encontrado na matriz.\n");
  return 0; // Falha na exclusão
}

MATRIZ *soma2Matriz(MATRIZ *m, MATRIZ *n)
{
  if (m == NULL || n == NULL || m->linhas != n->linhas || m->colunas != n->colunas)
  {
    printf("Erro: Matrizes não podem ser somadas.\n");
    return NULL;
  }

  MATRIZ *resultado = inicializarMatriz(m->linhas, m->colunas);

  for (int l = 0; l < m->linhas; l++)
  {
    for (int c = 0; c < m->colunas; c++)
    {
      float valor_m = ValorMatriz(m, l, c);
      float valor_n = ValorMatriz(n, l, c);
      float valor_soma = valor_m + valor_n;
      insereMatriz(resultado, l, c, valor_soma);
    }
  }

  return resultado;
}

int main()
{
  MATRIZ *m, *n, *soma; // Renomeada a variável "sum" para "soma"
  int col, lin, qtvalores;
  int colVal, linVal;
  float val;

  // ler dados para a primeira matriz
  scanf("%d", &qtvalores);
  scanf("%d", &lin);
  scanf("%d", &col);

  m = inicializarMatriz(lin, col);

  for (int i = 0; i < qtvalores; i++)
  {
    scanf("%d", &linVal);
    scanf("%d", &colVal);
    scanf("%f", &val);
    insereMatriz(m, linVal, colVal, val);
  }

  // ler dados para a segunda matriz
  scanf("%d", &qtvalores);
  scanf("%d", &lin);
  scanf("%d", &col);

  n = inicializarMatriz(lin, col);

  for (int i = 0; i < qtvalores; i++)
  {
    scanf("%d", &linVal);
    scanf("%d", &colVal);
    scanf("%f", &val);
    insereMatriz(n, linVal, colVal, val);
  }

  // realiza a soma das duas matrizes
  soma = soma2Matriz(m, n); // Renomeada a variável "sum" para "soma"

  // imprime a matriz resultante
  imprimeMatriz(soma);

  return 0;
}