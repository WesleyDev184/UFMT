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

float somatorioMatriz(MATRIZ *m)
{
  if (m == NULL)
  {
    printf("Erro: Matriz não inicializada.\n");
    return 0.0;
  }

  float somatorio = 0.0;

  for (int l = 0; l < m->linhas; l++)
  {
    if (m->A[l] != NULL)
    {
      PONT c = m->A[l];

      while (c != NULL)
      {
        somatorio += c->valor;
        c = c->prox;
      }
    }
  }

  return somatorio;
}

MATRIZ *multEscalarMatriz(MATRIZ *m, int x)
{
  if (m == NULL)
  {
    printf("Erro: Matriz não inicializada.\n");
    return NULL;
  }

  MATRIZ *n = inicializarMatriz(m->linhas, m->colunas);

  for (int l = 0; l < m->linhas; l++)
  {
    if (m->A[l] != NULL)
    {
      PONT c = m->A[l];
      while (c != NULL)
      {
        insereMatriz(n, l, c->coluna, c->valor * x);
        c = c->prox;
      }
    }
  }

  return n;
}

// A função main não deve ser alterada quando for enviar
int main()
{
  MATRIZ *m;
  int col, lin, qtvalores;
  int linVal, colVal;
  float val;

  qtvalores = 9;
  lin = 3;
  col = 3;

  m = inicializarMatriz(lin, col);

  insereMatriz(m, 0, 0, 3);
  insereMatriz(m, 0, 1, 5);
  insereMatriz(m, 0, 2, 6);
  insereMatriz(m, 1, 0, 2);
  insereMatriz(m, 1, 1, 7);
  insereMatriz(m, 1, 2, 8);
  insereMatriz(m, 2, 0, 1);
  insereMatriz(m, 2, 1, 4);
  insereMatriz(m, 2, 2, 9);

  printf("Matriz após a inserção:\n");
  imprimeMatriz(m);

  printf("Digite a linha e coluna para buscar um valor: ");
  scanf("%d %d", &linVal, &colVal);
  float valor = ValorMatriz(m, linVal, colVal);
  printf("Valor encontrado: %f\n", valor);

  printf("Digite a linha e coluna para excluir um valor: ");
  scanf("%d %d", &linVal, &colVal);
  excluirMatriz(m, linVal, colVal);

  printf("Matriz após a exclusão:\n");
  imprimeMatriz(m);

  return 0;
}