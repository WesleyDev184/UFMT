#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOPESO;

typedef struct aresta
{
    int origem, destino;
    TIPOPESO peso;
} ARESTA;

typedef struct grafo
{
    int vertices;
    int arestas;
    ARESTA *aresta;
} GRAFO;

GRAFO *criaGrafo(int v, int a)
{
    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = a;
    g->aresta = (ARESTA *)malloc(a * sizeof(ARESTA));
    return g;
}

int compararArestas(const void *a, const void *b)
{
    return ((ARESTA *)a)->peso - ((ARESTA *)b)->peso;
}

int encontrar(int pai[], int i)
{
    if (pai[i] == i)
        return i;
    return encontrar(pai, pai[i]);
}

void unir(int pai[], int rank[], int x, int y)
{
    int raiz_x = encontrar(pai, x);
    int raiz_y = encontrar(pai, y);

    if (rank[raiz_x] < rank[raiz_y])
        pai[raiz_x] = raiz_y;
    else if (rank[raiz_x] > rank[raiz_y])
        pai[raiz_y] = raiz_x;
    else
    {
        pai[raiz_y] = raiz_x;
        rank[raiz_x]++;
    }
}

int kruskal(GRAFO *g)
{
    int custo_total = 0;
    int *pai = (int *)malloc(g->vertices * sizeof(int));
    int *rank = (int *)malloc(g->vertices * sizeof(int));

    for (int i = 0; i < g->vertices; i++)
    {
        pai[i] = i;
        rank[i] = 0;
    }

    qsort(g->aresta, g->arestas, sizeof(ARESTA), compararArestas);

    for (int i = 0, j = 0; i < g->arestas && j < g->vertices - 1; i++)
    {
        int origem = g->aresta[i].origem;
        int destino = g->aresta[i].destino;
        int peso = g->aresta[i].peso;

        int raiz_origem = encontrar(pai, origem);
        int raiz_destino = encontrar(pai, destino);

        if (raiz_origem != raiz_destino)
        {
            custo_total += peso;
            unir(pai, rank, raiz_origem, raiz_destino);
            j++;
        }
    }

    free(pai);
    free(rank);

    return custo_total;
}

int main()
{
    FILE *entrada = fopen("ex1.txt", "r");
    if (entrada == NULL)
    {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    char linha[100];
    int vertices, arestas;

    while (fgets(linha, sizeof(linha), entrada))
    {
        if (linha[0] == 'p')
        {
            sscanf(linha, "p sp %d %d", &vertices, &arestas);
            break;
        }
    }

    GRAFO *gr = criaGrafo(vertices, arestas);

    for (int i = 0; i < arestas; i++)
    {
        int v, w, peso;
        fgets(linha, sizeof(linha), entrada);
        sscanf(linha, "a %d %d %d", &v, &w, &peso);
        gr->aresta[i].origem = v - 1;
        gr->aresta[i].destino = w - 1;
        gr->aresta[i].peso = peso;
    }

    fclose(entrada);

    clock_t start_time = clock();
    int custo_total = kruskal(gr);
    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Grava o resultado em um arquivo de saída
    FILE *saida = fopen("saida.txt", "w");
    if (saida == NULL)
    {
        perror("Erro ao abrir o arquivo de saída");
        return 1;
    }

    fprintf(saida, "Custo Total da Árvore Geradora Mínima: %d\n", custo_total);
    fprintf(saida, "Tempo Total: %lf segundos\n", execution_time);

    fclose(saida);

    return 0;
}