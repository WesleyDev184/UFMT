#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define INFINITY INT_MAX
#define TRUE 1
#define FALSE 0

typedef int TIPOPESO;
typedef int bool;

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

GRAFO *criaGrafo(int v)
{
  GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
  g->vertices = v;
  g->arestas = 0;
  g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));
  int i;
  for (i = 0; i < v; i++)
  {
    g->adj[i].cab = NULL;
  }
  return g;
}

ADJACENCIA *criaAdj(int v, int peso)
{
  ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
  temp->vertice = v;
  temp->peso = peso;
  temp->prox = NULL;
  return temp;
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO ps)
{
  if (!gr)
    return FALSE;
  if ((vf < 0) || (vf >= gr->vertices))
    return FALSE;
  if ((vi < 0) || (vi >= gr->vertices))
    return FALSE;
  ADJACENCIA *novo = criaAdj(vf, ps);
  ADJACENCIA *ant = NULL;
  ADJACENCIA *p = gr->adj[vi].cab;
  while (p && p->vertice < vf)
  {
    ant = p;
    p = p->prox;
  }
  if (ant)
  {
    ant->prox = novo;
  }
  else
  {
    gr->adj[vi].cab = novo;
  }
  novo->prox = p;
  gr->arestas++;
  return TRUE;
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
      printf("v%d(%d) ", ad->vertice, ad->peso);
      ad = ad->prox;
    }
    printf("\n");
  }
}

void dijkstra(GRAFO *gr, int origem, int *distancias)
{
  int *visitados = (int *)malloc(gr->vertices * sizeof(int));
  int i, v, cont;

  for (i = 0; i < gr->vertices; i++)
  {
    distancias[i] = INFINITY;
    visitados[i] = 0;
  }

  distancias[origem] = 0;

  for (cont = 0; cont < gr->vertices - 1; cont++)
  {
    int u = -1;
    for (i = 0; i < gr->vertices; i++)
    {
      if (!visitados[i] && (u == -1 || distancias[i] < distancias[u]))
      {
        u = i;
      }
    }

    visitados[u] = 1;

    ADJACENCIA *p = gr->adj[u].cab;
    while (p)
    {
      v = p->vertice;
      if (!visitados[v] && distancias[u] + p->peso < distancias[v])
      {
        distancias[v] = distancias[u] + p->peso;
      }
      p = p->prox;
    }
  }

  free(visitados);
}

void bellmanFord(GRAFO *gr, int origem, int *distancias)
{
  int i, j;

  for (i = 0; i < gr->vertices; i++)
  {
    distancias[i] = INFINITY;
  }

  distancias[origem] = 0;

  for (i = 1; i <= gr->vertices - 1; i++)
  {
    for (j = 0; j < gr->vertices; j++)
    {
      ADJACENCIA *p = gr->adj[j].cab;
      while (p)
      {
        int v = p->vertice;
        int peso = p->peso;
        if (distancias[j] != INFINITY && distancias[j] + peso < distancias[v])
        {
          distancias[v] = distancias[j] + peso;
        }
        p = p->prox;
      }
    }
  }
}

void carregarInstancia(GRAFO *gr, const char *nomeArquivo)
{
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (!arquivo)
  {
    perror("Erro ao abrir o arquivo");
    exit(EXIT_FAILURE);
  }

  int vertices, arestas;
  char linha[128];

  // Encontrar o número de vértices e arestas
  while (fgets(linha, sizeof(linha), arquivo) != NULL)
  {
    if (linha[0] == 'p')
    {
      sscanf(linha, "p sp %d %d", &vertices, &arestas);
      break;
    }
  }

  printf("Número de vértices: %d\n", vertices);
  printf("Número de arestas: %d\n", arestas);

  // Criar o grafo com base no número de vértices
  gr = criaGrafo(vertices);

  // Adicionar arestas ao grafo
  while (fgets(linha, sizeof(linha), arquivo) != NULL)
  {
    if (linha[0] == 'a')
    {
      int u, v, peso;
      sscanf(linha, "a %d %d %d", &u, &v, &peso);
      criaAresta(gr, u - 1, v - 1, peso);
    }
  }

  fclose(arquivo);
}

void salvarResultado(const char *nomeArquivo, int *distancias, clock_t tempo)
{
  FILE *arquivo = fopen(nomeArquivo, "w");
  if (!arquivo)
  {
    perror("Erro ao criar o arquivo de saída");
    exit(EXIT_FAILURE);
  }

  fprintf(arquivo, "Distancias encontradas:\n");
  for (int i = 0; i < 3; i++)
  {
    fprintf(arquivo, "Vertice %d: %d\n", i + 1, distancias[i]);
  }

  fprintf(arquivo, "\nTempo total de processamento: %f segundos\n", ((double)tempo) / CLOCKS_PER_SEC);

  fclose(arquivo);
}

int main()
{
  GRAFO *gr = NULL;
  carregarInstancia(&gr, "USA-road-d.CAL.gr");

  int origem = 0;
  int *distanciasDijkstra = (int *)malloc(gr->vertices * sizeof(int));
  int *distanciasBellmanFord = (int *)malloc(gr->vertices * sizeof(int));

  // Carregar instâncias
  printf("Instância CAL carregada.\n");

  // Executar Dijkstra
  clock_t inicioDijkstra = clock();
  dijkstra(gr, origem, distanciasDijkstra);
  clock_t fimDijkstra = clock();
  double tempoDijkstra = ((double)(fimDijkstra - inicioDijkstra)) / CLOCKS_PER_SEC;
  printf("Dijkstra concluído em %f segundos.\n", tempoDijkstra);

  // Salvar resultados do Dijkstra
  salvarResultado("output_dijkstra.txt", distanciasDijkstra, fimDijkstra - inicioDijkstra);

  // Limpar resultados do Dijkstra para reutilização
  free(distanciasDijkstra);
  distanciasDijkstra = (int *)malloc(gr->vertices * sizeof(int));

  // Executar Bellman-Ford
  clock_t inicioBellmanFord = clock();
  bellmanFord(gr, origem, distanciasBellmanFord);
  clock_t fimBellmanFord = clock();
  double tempoBellmanFord = ((double)(fimBellmanFord - inicioBellmanFord)) / CLOCKS_PER_SEC;
  printf("Bellman-Ford concluído em %f segundos.\n", tempoBellmanFord);

  // Salvar resultados do Bellman-Ford
  salvarResultado("output_bellman_ford.txt", distanciasBellmanFord, fimBellmanFord - inicioBellmanFord);

  // Limpar resultados do Bellman-Ford
  free(distanciasBellmanFord);

  // Liberar memória do grafo
  // ...

  return 0;
}
