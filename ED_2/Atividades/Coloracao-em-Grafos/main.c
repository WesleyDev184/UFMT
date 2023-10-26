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

typedef struct
{
  int vertex;
  int degree;
  int saturation;
  int color;
} DSATUR_INFO;

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
  
  ADJACENCIA *novo1 = criaAdj(vf, ps);
  ADJACENCIA *novo2 = criaAdj(vi, ps);

  ADJACENCIA *ant1 = NULL;
  ADJACENCIA *p1 = gr->adj[vi].cab;
  while (p1 && p1->vertice < vf) // Percorre a lista de adjacências do vértice vi até encontrar a posição correta de inserção da nova adjacência
  {
    ant1 = p1;
    p1 = p1->prox;
  }
  if (ant1)
  {
    ant1->prox = novo1; // Insere a nova adjacência na posição correta da lista ordenada
  }
  else
  {
    gr->adj[vi].cab = novo1; // Se ant1 for nulo, a nova adjacência é o primeiro elemento da lista
  }
  novo1->prox = p1;

  ADJACENCIA *ant2 = NULL;
  ADJACENCIA *p2 = gr->adj[vf].cab;
  while (p2 && p2->vertice < vi) // Percorre a lista de adjacências do vértice vf até encontrar a posição correta de inserção da nova adjacência
  {
    ant2 = p2;
    p2 = p2->prox;
  }
  if (ant2)
  {
    ant2->prox = novo2; // Insere a nova adjacência na posição correta da lista ordenada
  }
  else
  {
    gr->adj[vf].cab = novo2; // Se ant2 for nulo, a nova adjacência é o primeiro elemento da lista
  }
  novo2->prox = p2;

  gr->arestas += 2; // Incrementa o número de arestas no grafo (em ambos os vértices)
  return true;
}

void imprimeDSATUR(GRAFO *gr, DSATUR_INFO *dsatur)
{
  printf("Vertices: %d. Arestas: %d.\n", gr->vertices, gr->arestas);
  printf("Vertex  DSATUR  Degree  Color\n");
  for (int i = 0; i < gr->vertices; i++)
  {
    printf("v%d:    %d       %d       %d\n", dsatur[i].vertex, dsatur[i].saturation, dsatur[i].degree, dsatur[i].color);
  }
}

int compareDSATUR(const void *a, const void *b)
{
  DSATUR_INFO *infoA = (DSATUR_INFO *)a;
  DSATUR_INFO *infoB = (DSATUR_INFO *)b;

  if (infoA->saturation != infoB->saturation)
  {
    return infoB->saturation - infoA->saturation;
  }
  else
  {
    return infoB->degree - infoA->degree;
  }
}

int DSATUR(GRAFO *gr)
{
  DSATUR_INFO *dsatur = (DSATUR_INFO *)malloc(gr->vertices * sizeof(DSATUR_INFO));
  for (int i = 0; i < gr->vertices; i++)
  {
    dsatur[i].vertex = i;
    dsatur[i].saturation = 0;
    dsatur[i].degree = 0;
    dsatur[i].color = -1;
    ADJACENCIA *ad = gr->adj[i].cab;
    while (ad)
    {
      dsatur[i].degree++;
      if (dsatur[ad->vertice].color != -1)
      {
        dsatur[i].saturation++;
      }
      ad = ad->prox;
    }
  }

  qsort(dsatur, gr->vertices, sizeof(DSATUR_INFO), compareDSATUR);

  int maxColor = 0;
  for (int i = 0; i < gr->vertices; i++)
  {
    int v = dsatur[i].vertex;
    int color = 1;
    while (1)
    {
      bool available = true;
      ADJACENCIA *ad = gr->adj[v].cab;
      while (ad)
      {
        if (dsatur[ad->vertice].color == color)
        {
          available = false;
          break;
        }
        ad = ad->prox;
      }
      if (available)
      {
        dsatur[v].color = color;
        if (color > maxColor)
        {
          maxColor = color;
        }
        break;
      }
      color++;
    }
  }

  free(dsatur);
  return maxColor;
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

void geraArquivoSaida(char *nomeArquivo, int valorCromatico, int index)
{
  FILE *arquivoSaida = fopen(nomeArquivo, "a");

  if (!arquivoSaida)
  {
    printf("Erro ao abrir o arquivo de saída.\n");
    return;
  }

  // Verifique se o arquivo não está vazio e não termina com uma quebra de linha.
  fseek(arquivoSaida, -1, SEEK_END);
  if (ftell(arquivoSaida) > 0)
  {
    fputc('\n', arquivoSaida); // Adiciona uma quebra de linha
  }

  switch (index)
  {
  case 0:
    fprintf(arquivoSaida, "jean.col\n");
    break;
  case 1:
    fprintf(arquivoSaida, "miles250.col\n");
    break;

  case 2:
    fprintf(arquivoSaida, "miles1000.col\n");
    break;

  case 3:
    fprintf(arquivoSaida, "le450_25a.col\n");
    break;

  case 4:
    fprintf(arquivoSaida, "r1000.1.col\n");
    break;

  case 5:
    fprintf(arquivoSaida, "r250.1c.col\n");
    break;

  default:
    break;
  }

  fprintf(arquivoSaida, "Valor da cromático: %d", valorCromatico);

  fclose(arquivoSaida);
}

int main()
{
  char *nomeArquivo[] = {
      "D:/GitHub/UFMT/ED_2/Atividades/Coloracao-em-Grafos/Trab7 (Coloracao) all-instaces/jean.col",
      "D:/GitHub/UFMT/ED_2/Atividades/Coloracao-em-Grafos/Trab7 (Coloracao) all-instaces/miles250.col",
      "D:/GitHub/UFMT/ED_2/Atividades/Coloracao-em-Grafos/Trab7 (Coloracao) all-instaces/miles1000.col",
      "D:/GitHub/UFMT/ED_2/Atividades/Coloracao-em-Grafos/Trab7 (Coloracao) all-instaces/le450_25a.col",
      "D:/GitHub/UFMT/ED_2/Atividades/Coloracao-em-Grafos/Trab7 (Coloracao) all-instaces/r1000.1.col",
      "D:/GitHub/UFMT/ED_2/Atividades/Coloracao-em-Grafos/Trab7 (Coloracao) all-instaces/r250.1c.col"};

  for (int i = 0; i < 6; i++)
  {
    GRAFO *gr = NULL;
    FILE *arquivoEntrada = fopen(nomeArquivo[i], "r");

    if (!arquivoEntrada)
    {
      printf("Erro ao abrir o arquivo de entrada %s.\n", nomeArquivo[i]);
      continue;
    }

    leGrafoArquivo(&gr, arquivoEntrada);

    int chromaticNumber = DSATUR(gr);

    printf("Numero Cromatico para %s: %d\n", nomeArquivo[i], chromaticNumber);

    geraArquivoSaida("saida.txt", chromaticNumber, i);

    fclose(arquivoEntrada);
    free(gr); // Liberar o grafo após cada instância
  }

  return 0;
}
