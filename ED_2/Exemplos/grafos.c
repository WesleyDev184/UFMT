#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;
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

int main()
{
  GRAFO *gr = criaGrafo(5); // Cria um grafo com 5 vértices
  criaAresta(gr, 0, 1, 2);
  criaAresta(gr, 1, 2, 4);
  criaAresta(gr, 2, 0, 12);
  criaAresta(gr, 2, 4, 40);
  criaAresta(gr, 3, 1, 3);
  criaAresta(gr, 4, 3, 8);
  imprime(gr); // Imprime o grafo
  return 0;
}
