#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#define INF INT_MAX

typedef int TIPOPESO;

typedef struct adjacencia
{
  int vertice;
  TIPOPESO peso;
  struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice
{
  ADJACENCIA *cab;
} VERTICE;

typedef struct grafo
{
  int vertices;
  int arestas;
  VERTICE *adj;
} GRAFO;

// Protótipos das funções
GRAFO *criaGrafo(int v);
ADJACENCIA *criaAdj(int v, int peso);
bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO ps);
void imprime(GRAFO *gr);
bool leGrafoArquivo(GRAFO **gr, FILE *arquivo);
void geraArquivoSaida(char *nomeArquivo, int custoTotal, double tempoTotal, GRAFO *gr);
int min(int a, int b);
ADJACENCIA *buscaAresta(GRAFO *gr, int u, int v); // Movido para cá
int fordFulkerson(GRAFO *gr, int origem, int destino);
void liberaGrafo(GRAFO *gr);

GRAFO *criaGrafo(int v)
{
  GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO)); // Aloca memória para o grafo
  if (!g)
  {
    perror("Erro ao alocar memória para o grafo.\n");
    exit(EXIT_FAILURE);
  }

  g->vertices = v;
  g->arestas = 0;
  g->adj = (VERTICE *)malloc(v * sizeof(VERTICE)); // Aloca memória para os vértices do grafo
  if (!g->adj)
  {
    free(g);
    perror("Erro ao alocar memória para os vértices do grafo.\n");
    exit(EXIT_FAILURE);
  }

  int i;
  for (i = 0; i < v; i++)
  {
    g->adj[i].cab = NULL; // Inicializa a lista de adjacências de cada vértice como nula
  }
  return g;
}

ADJACENCIA *criaAdj(int v, int peso)
{
  ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA)); // Cria uma nova adjacência
  if (!temp)
  {
    perror("Erro ao alocar memória para a adjacência.\n");
    exit(EXIT_FAILURE);
  }

  temp->vertice = v;
  temp->peso = peso;
  temp->prox = NULL;
  return temp;
}

// insere ordenado
bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO ps)
{
  if (!gr)
    return false;
  if ((vf < 0) || (vf >= gr->vertices))
    return false;
  if ((vi < 0) || (vi >= gr->vertices))
    return false;
  ADJACENCIA *novo = criaAdj(vf, ps);
  ADJACENCIA *ant = NULL;
  ADJACENCIA *p = gr->adj[vi].cab;
  while (p && p->vertice < vf) // Percorre a lista de adjacências do vértice vi até encontrar a posição correta de inserção da nova adjacência
  {
    ant = p;
    p = p->prox;
  }
  if (ant)
  {
    ant->prox = novo; // Insere a nova adjacência na posição correta da lista ordenada
  }
  else
  {
    gr->adj[vi].cab = novo; // Se ant for nulo, a nova adjacência é o primeiro elemento da lista
  }
  novo->prox = p;
  gr->arestas++; // Incrementa o número de arestas no grafo
  return true;
}

void imprime(GRAFO *gr)
{
  printf("Vertices: %d. Arestas: %d.\n", gr->vertices, gr->arestas);
  int i;
  for (i = 0; i < gr->vertices; i++)
  {
    printf("v%d: ", i);
    ADJACENCIA *ad = gr->adj[i].cab;
    while (ad)
    {
      printf("v%d(%d) ", ad->vertice, ad->peso); // Imprime as adjacências de cada vértice
      ad = ad->prox;
    }
    printf("\n");
  }
}

bool leGrafoArquivo(GRAFO **gr, FILE *arquivo)
{
  int vertices, arestas;
  char linha[128];

  // Encontrar o número de vértices e arestas
  while (fgets(linha, sizeof(linha), arquivo) != NULL)
  {
    if (linha[0] == 'p')
    {
      sscanf(linha, "p max %d %d", &vertices, &arestas);
      break;
    }
  }

  // Criar o grafo com base no número de vértices
  *gr = criaGrafo(vertices);

  // Adicionar arestas ao grafo
  while (fgets(linha, sizeof(linha), arquivo) != NULL)
  {
    if (linha[0] == 'a')
    {
      int u, v, peso;
      sscanf(linha, "a %d %d %d", &u, &v, &peso);
      criaAresta(*gr, u - 1, v - 1, peso);
    }
  }

  return true;
}

void geraArquivoSaida(char *nomeArquivo, int fluxoMaximo, double tempoTotal, GRAFO *gr)
{
  FILE *arquivoSaida = fopen(nomeArquivo, "a");

  if (!arquivoSaida)
  {
    printf("Erro ao abrir o arquivo de saída.\n");
    return;
  }

  // Adiciona uma quebra de linha se o arquivo já contiver dados
  if (ftell(arquivoSaida) > 0)
    fprintf(arquivoSaida, "\n\n");

  fprintf(arquivoSaida, "Fluxo máximo: %d\n", fluxoMaximo);
  fprintf(arquivoSaida, "Tempo total de execução: %f segundos\n\n", tempoTotal);

  // Imprime a configuração do grafo com o uso das folgas
  fprintf(arquivoSaida, "Configuração do grafo com o uso das folgas:\n");
  for (int i = 0; i < gr->vertices; i++)
  {
    fprintf(arquivoSaida, "v%d: ", i);
    ADJACENCIA *ad = gr->adj[i].cab;
    while (ad)
    {
      // Use the fluxoMaximo as slack (folga) value
      fprintf(arquivoSaida, "v%d(%d, F=%d) ", ad->vertice, ad->peso, fluxoMaximo);
      ad = ad->prox;
    }
    fprintf(arquivoSaida, "\n");
  }

  fclose(arquivoSaida);
}

// Função auxiliar para encontrar o mínimo entre dois valores
int min(int a, int b)
{
  return (a < b) ? a : b;
}

// Algoritmo Ford-Fulkerson
int fordFulkerson(GRAFO *gr, int origem, int destino)
{
  int u, v;

  // Criar uma cópia residual do grafo
  GRAFO *residual = criaGrafo(gr->vertices);

  // Inicializar o grafo residual com as mesmas arestas do grafo original
  for (u = 0; u < gr->vertices; u++)
  {
    ADJACENCIA *ad = gr->adj[u].cab;
    while (ad)
    {
      criaAresta(residual, u, ad->vertice, ad->peso);
      ad = ad->prox;
    }
  }

  int fluxoMaximo = 0; // Inicializar o fluxo máximo como 0

  // Enquanto houver um caminho de aumento no grafo residual
  while (1)
  {
    // Executar uma busca em largura para encontrar um caminho de aumento
    int visitados[gr->vertices];
    memset(visitados, 0, sizeof(visitados));
    int pais[gr->vertices];
    memset(pais, -1, sizeof(pais));
    int fila[gr->vertices];
    int frente = -1, tras = -1;
    fila[++tras] = origem;
    visitados[origem] = 1;

    while (frente < tras)
    {
      u = fila[++frente];
      ADJACENCIA *ad = residual->adj[u].cab;
      while (ad)
      {
        v = ad->vertice;
        if (!visitados[v] && ad->peso > 0)
        {
          fila[++tras] = v;
          pais[v] = u;
          visitados[v] = 1;
        }
        ad = ad->prox;
      }
    }

    // Se não houver mais caminhos de aumento, sair do loop
    if (!visitados[destino])
    {
      break;
    }

    // Encontrar a capacidade mínima ao longo do caminho de aumento
    int caminhoMinimo = INF;
    for (v = destino; v != origem; v = pais[v])
    {
      u = pais[v];
      ADJACENCIA *adUV = buscaAresta(residual, u, v);
      caminhoMinimo = min(caminhoMinimo, adUV->peso);
    }

    for (v = destino; v != origem; v = pais[v])
    {
      u = pais[v];
      ADJACENCIA *adUV = buscaAresta(residual, u, v);
      ADJACENCIA *adVU = buscaAresta(residual, v, u);

      if (adUV)
        adUV->peso -= caminhoMinimo;

      if (adVU)
        adVU->peso += caminhoMinimo;
    }

    // Incrementar o fluxo máximo
    fluxoMaximo += caminhoMinimo;
  }

  // Liberar a memória alocada para o grafo residual
  liberaGrafo(residual);

  return fluxoMaximo;
}

// Função para buscar uma aresta no grafo pelo par de vértices (u, v)
ADJACENCIA *buscaAresta(GRAFO *gr, int u, int v)
{
  ADJACENCIA *ad = gr->adj[u].cab;
  while (ad)
  {
    if (ad->vertice == v)
    {
      return ad;
    }
    ad = ad->prox;
  }
  return NULL;
}

void liberaGrafo(GRAFO *gr)
{
  if (gr)
  {
    for (int i = 0; i < gr->vertices; i++)
    {
      ADJACENCIA *atual = gr->adj[i].cab;
      while (atual)
      {
        ADJACENCIA *prox = atual->prox;
        free(atual);
        atual = prox;
      }
    }

    free(gr->adj);
    free(gr);
  }
}

int main()
{
  clock_t inicio = clock(); // Inicia a contagem do tempo de execução
  GRAFO *gr = NULL;         // Ponteiro para o grafo
  FILE *arquivo = fopen("D:/GitHub/UFMT/ED_2/Atividades/Ford-Fulkerson/input.gr", "r");
  // FILE *arquivo = fopen("Path/para/o/arquivo", "r");

  if (!arquivo)
  {
    perror("Erro ao abrir o arquivo.\n");
    return 1;
  }

  if (!leGrafoArquivo(&gr, arquivo))
  {
    fclose(arquivo);
    liberaGrafo(gr);
    perror("Erro ao ler o grafo do arquivo.\n");
    return 1;
  }

  fclose(arquivo);

  int origem = 0;  // Vértice de origem
  int destino = 1; // Vértice de destino

  // Calcular o fluxo máximo
  int fluxoMaximo = fordFulkerson(gr, origem, destino);
  clock_t fim = clock(); // Finaliza a contagem do tempo de execução

  double tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC; // Calcula o tempo de execução em segundos

  // Gere um arquivo de saída com o valor do fluxo máximo
  geraArquivoSaida("saida.txt", fluxoMaximo, tempoExecucao, gr);

  imprime(gr); // Imprime o grafo

  liberaGrafo(gr); // Libera a memória alocada para o grafo

  return 0;
}