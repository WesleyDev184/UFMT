#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
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

int prim(GRAFO *gr, int raiz)
{
  int *chave = (int *)malloc(gr->vertices * sizeof(int));
  int *pai = (int *)malloc(gr->vertices * sizeof(int));
  bool *incluirNoMST = (bool *)malloc(gr->vertices * sizeof(bool));

  for (int i = 0; i < gr->vertices; i++)
  {
    chave[i] = INT_MAX;
    pai[i] = -1;
    incluirNoMST[i] = false;
  }

  chave[raiz] = 0;

  for (int count = 0; count < gr->vertices - 1; count++)
  {
    int u = -1;

    for (int v = 0; v < gr->vertices; v++)
    {
      if (!incluirNoMST[v] && (u == -1 || chave[v] < chave[u]))
      {
        u = v;
      }
    }

    incluirNoMST[u] = true;

    ADJACENCIA *p = gr->adj[u].cab;
    while (p != NULL)
    {
      int v = p->vertice;
      if (!incluirNoMST[v] && p->peso < chave[v])
      {
        pai[v] = u;
        chave[v] = p->peso;
      }
      p = p->prox;
    }
  }

  int custoTotal = 0;
  for (int i = 0; i < gr->vertices; i++)
  {
    if (pai[i] != -1)
    {
      custoTotal += chave[i];
    }
  }

  printf("Custo total da arvore geradora minima: %d\n", custoTotal);

  free(chave);
  free(pai);
  free(incluirNoMST);

  return custoTotal;
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

void geraArquivoSaida(char *nomeArquivo, int custoTotal, double tempoTotal, char *cidade)
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

  fprintf(arquivoSaida, "Cidade: %s\n", cidade);
  fprintf(arquivoSaida, "Custo total da árvore geradora mínima: %d\n", custoTotal);
  fprintf(arquivoSaida, "Tempo total de execução: %f segundos\n", tempoTotal);

  fclose(arquivoSaida);
}
int main()
{
  // Substitua o caminho do arquivo pelo caminho correto
  FILE *arquivoNY = fopen("D:/GitHub/UFMT/ED_2/Atividades/inputs/exemploAula.txt", "r");
  FILE *arquivoCAL = fopen("D:/GitHub/UFMT/ED_2/Atividades/inputs/exemploAula.txt", "r");

  if (!arquivoNY)
  {
    printf("Erro ao abrir o arquivo NY.\n");
    return 1;
  }

  if (!arquivoCAL)
  {
    printf("Erro ao abrir o arquivo CAL.\n");
    return 1;
  }

  GRAFO *grNY = NULL;
  GRAFO *grCAL = NULL;

  if (leGrafoArquivo(&grNY, arquivoNY))
  {
    fclose(arquivoNY);

    // Imprime o grafo lido do arquivo
    // imprime(grNY);

    // Mede o tempo de execução do algoritmo de Prim
    clock_t inicio = clock();
    int custoTotal = prim(grNY, 0);
    clock_t fim = clock();

    // Calcula o tempo total em segundos
    double tempoTotal = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Tempo total: %f segundos\n", tempoTotal);

    char cidade1[128] = "NY";

    geraArquivoSaida("saida.txt", custoTotal, tempoTotal, cidade1);

    // Libera a memória alocada para o grafo
    // (você pode querer modificar a função para liberar memória de maneira mais genérica)
    free(grNY->adj);
    free(grNY);
  }
  else
  {
    fclose(arquivoNY);
    printf("Erro ao ler o grafo do arquivo.\n");
    return 1;
  }

  if (leGrafoArquivo(&grCAL, arquivoCAL))
  {
    fclose(arquivoCAL);

    // Imprime o grafo lido do arquivo
    // imprime(grCAL);

    // Mede o tempo de execução do algoritmo de Prim
    clock_t inicio = clock();
    int custoTotal = prim(grCAL, 0);
    clock_t fim = clock();

    // Calcula o tempo total em segundos
    double tempoTotal = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Tempo total: %f segundos\n", tempoTotal);

    char cidade2[128] = "CAL";

    geraArquivoSaida("saida.txt", custoTotal, tempoTotal, cidade2);

    // Libera a memória alocada para o grafo
    // (você pode querer modificar a função para liberar memória de maneira mais genérica)
    free(grCAL->adj);
    free(grCAL);
  }
  else
  {
    fclose(arquivoCAL);
    printf("Erro ao ler o grafo do arquivo.\n");
    return 1;
  }

  return 0;
}
