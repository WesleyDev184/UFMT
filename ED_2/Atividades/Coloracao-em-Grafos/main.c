#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
  GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO)); // Aloca memória para o grafo
  g->vertices = v;
  g->arestas = 0;
  g->adj = (VERTICE *)malloc(v * sizeof(VERTICE)); // Aloca memória para os vértices do grafo
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
      sscanf(linha, "p edge %d %d", &vertices, &arestas);
      break;
    }
  }

  // Criar o grafo com base no número de vértices
  *gr = criaGrafo(vertices);

  // Adicionar arestas ao grafo
  while (fgets(linha, sizeof(linha), arquivo) != NULL)
  {
    if (linha[0] == 'e')
    {
      int u, v, peso;
      sscanf(linha, "e %d %d %d", &u, &v, &peso);
      criaAresta(*gr, u - 1, v - 1, peso);
    }
  }

  fclose(arquivo);
  return true;
}

void geraArquivoSaida(char *nomeArquivo, int valorCromatico)
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

  fprintf(arquivoSaida, "Valor da cromático: %d", valorCromatico);

  fclose(arquivoSaida);
}

int main()
{
  GRAFO *gr = NULL;
  FILE *arquivoEntrada = fopen("D:/GitHub/UFMT/ED_2/Atividades/Coloracao-em-Grafos/Trab7 (Coloracao) all-instaces/jean.col", "r");

  if (!arquivoEntrada)
  {
    printf("Erro ao abrir o arquivo de entrada.\n");
    return 0;
  }

  leGrafoArquivo(&gr, arquivoEntrada);
 
  imprime(gr);
  return 0;
}
