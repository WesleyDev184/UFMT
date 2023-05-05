/*
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1 - Trabalho 6 : lst - estática x dinamica
 * Prof Ivairton
 * Discentes:  Lucas Barbosa Amaral, Wesley Antonio Junior dos Santos
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Tabuleiro.c"
#include "Jogador.c"

LinkedList *createCircularBoard(char *filename)
{
    FILE *fp;
    int size, value, values[26];
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    // Lê o tamanho da lista na primeira linha do arquivo
    fscanf(fp, "%d", &size);
    printf("Tamanho da lista: %d\n", size);

    // Lê os valores do arquivo e adiciona na lista
    for (int i = 0; i < size; i++)
    {
        fscanf(fp, "%d", &value);
        values[i] = value;
        printf("Valor %d: %d\n", i, value);
    }

    list = createList(size, values);

    fclose(fp);

    return list;
}

ListPlayers *createCircularListPlayers(char *filename)
{
    FILE *fp;
    int size;
    char players[100][100];
    ListPlayers *listOfPlayers = (ListPlayers *)malloc(sizeof(ListPlayers));

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    // Lê o tamanho da lista na primeira linha do arquivo
    fscanf(fp, "%d", &size);
    printf("Tamanho da lista: %d\n", size);

    // Lê os valores do arquivo e adiciona na lista
    for (int i = 0; i < size; i++)
    {
        fscanf(fp, "%s", players[i]);
        printf("Player %d: %s\n", i, players[i]);
    }

    listOfPlayers = createPlayerList(size, (char *)players);

    fclose(fp);

    return listOfPlayers;
}

int main()
{
    /*

    int num;

    srand(time(NULL));

    num = rand() % 6 + 1;
    */
    LinkedList *board = createCircularBoard("defineBoard.txt");

    printList(board);

    ListPlayers *players = createCircularListPlayers("definePlayer.txt");

    // printListPlayer(players);

    return 0;
}
