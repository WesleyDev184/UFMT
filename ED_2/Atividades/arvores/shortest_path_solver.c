#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>

#define INFINITY INT_MAX / 2 // Alterado para evitar estouro

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

GRAFO *criaGrafo(int v)
{
  GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
  if (!g)
  {
    fprintf(stderr, "Erro ao alocar memória para o grafo.\n");
    exit(EXIT_FAILURE);
  }
  g->vertices = v;
  g->arestas = 0;
  g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));
  if (!g->adj)
  {
    free(g);
    fprintf(stderr, "Erro ao alocar memória para o vetor de vértices.\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < v; i++)
  {
    g->adj[i].cab = NULL;
  }
  return g;
}

ADJACENCIA *criaAdj(int v, int peso)
{
  ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
  if (!temp)
  {
    fprintf(stderr, "Erro ao alocar memória para a adjacência.\n");
    exit(EXIT_FAILURE);
  }
  temp->vertice = v;
  temp->peso = peso;
  temp->prox = NULL;
  return temp;
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO ps)
{
  if (!gr || vf < 0 || vf >= gr->vertices || vi < 0 || vi >= gr->vertices)
  {
    return false;
  }
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
  return true;
}

void imprime(GRAFO *gr)
{
  printf("Vertices: %d. Arestas: %d.\n", gr->vertices, gr->arestas);
  for (int i = 0; i < gr->vertices; i++)
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
  if (!visitados)
  {
    fprintf(stderr, "Erro ao alocar memória para o vetor de visitados.\n");
    exit(EXIT_FAILURE);
  }
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

bool leGrafoArquivo(GRAFO **gr, FILE *arquivo)
{
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

void geraArquivoSaida(char *nomeArquivo, int custoTotal, double tempoTotal, char *cidade, char *destino)
{
  FILE *arquivoSaida = fopen(nomeArquivo, "a");

  if (!arquivoSaida)
  {
    fprintf(stderr, "Erro ao abrir o arquivo de saída.\n");
    return;
  }

  // Adiciona uma quebra de linha se o arquivo já contiver dados
  if (ftell(arquivoSaida) > 0)
    fprintf(arquivoSaida, "\n\n");

  fprintf(arquivoSaida, "Cidade: %s\n", cidade);
  fprintf(arquivoSaida, "Destino: %s\n", destino);
  fprintf(arquivoSaida, "Custo total da árvore geradora mínima: %d\n", custoTotal);
  fprintf(arquivoSaida, "Tempo total de execução: %f segundos\n", tempoTotal);

  fclose(arquivoSaida);
}

int main()
{
  char *nomeArquivo[] = {
      "D:/GitHub/UFMT/ED_2/Atividades/arvores/inputs/exemploAula.txt",
      "D:/GitHub/UFMT/ED_2/Atividades/arvores/inputs/exemploAula.txt",
  };

  for (int i = 0; i < 2; i++)
  {
    FILE *arquivo = fopen(nomeArquivo[i], "r");

    if (!arquivo)
    {
      fprintf(stderr, "Erro ao abrir o arquivo.\n");
      return 1;
    }

    GRAFO *gr = NULL;
    if (!leGrafoArquivo(&gr, arquivo))
    {
      fclose(arquivo);
      return 1;
    }
    fclose(arquivo);

    int *distancias = (int *)malloc(gr->vertices * sizeof(int));

    if (!distancias)
    {
      fprintf(stderr, "Erro ao alocar memória para o vetor de distâncias.\n");
      return 1;
    }

    clock_t inicio, fim;
    double tempoTotal;

    // Calcular a distância do vértice 1 ao vértice 2 usando Dijkstra
    inicio = clock();
    dijkstra(gr, 0, distancias);
    fim = clock();
    tempoTotal = (double)(fim - inicio) / CLOCKS_PER_SEC;
    geraArquivoSaida("dijkstra.txt", distancias[1], tempoTotal, i ? "CAL" : "NY", "v1 -> v2");

    // Calcular a distância do vértice 1 ao vértice 5 usando Dijkstra
    inicio = clock();
    dijkstra(gr, 0, distancias);
    fim = clock();
    tempoTotal = (double)(fim - inicio) / CLOCKS_PER_SEC;
    geraArquivoSaida("dijkstra.txt", distancias[4], tempoTotal, i ? "CAL" : "NY", "v1 -> v5");

    // Calcular a distância do vértice 1 ao vértice 9 usando Dijkstra
    inicio = clock();
    dijkstra(gr, 0, distancias);
    fim = clock();
    tempoTotal = (double)(fim - inicio) / CLOCKS_PER_SEC;
    geraArquivoSaida("dijkstra.txt", distancias[8], tempoTotal, i ? "CAL" : "NY", "v1 -> v9");

    // Calcular a distância do vértice 1 ao vértice 2 usando Bellman-Ford
    inicio = clock();
    bellmanFord(gr, 0, distancias);
    fim = clock();
    tempoTotal = (double)(fim - inicio) / CLOCKS_PER_SEC;
    geraArquivoSaida("bellmanFord.txt", distancias[1], tempoTotal, i ? "CAL" : "NY", "v1 -> v2");

    // Calcular a distância do vértice 1 ao vértice 5 usando Bellman-Ford
    inicio = clock();
    bellmanFord(gr, 0, distancias);
    fim = clock();
    tempoTotal = (double)(fim - inicio) / CLOCKS_PER_SEC;
    geraArquivoSaida("bellmanFord.txt", distancias[4], tempoTotal, i ? "CAL" : "NY", "v1 -> v5");

    // Calcular a distância do vértice 1 ao vértice 9 usando Bellman-Ford
    inicio = clock();
    bellmanFord(gr, 0, distancias);
    fim = clock();
    tempoTotal = (double)(fim - inicio) / CLOCKS_PER_SEC;
    geraArquivoSaida("bellmanFord.txt", distancias[8], tempoTotal, i ? "CAL" : "NY", "v1 -> v9");

    free(distancias);
    free(gr->adj);
    free(gr);
  }

  return 0;
}
