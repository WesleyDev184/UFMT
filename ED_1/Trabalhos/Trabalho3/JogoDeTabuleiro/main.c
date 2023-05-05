/*
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1 - Trabalho 6 : lst - estatica x dinamica
 * Prof Ivairton
 * Discentes:  Lucas Barbosa Amaral, Wesley Antonio Junior dos Santos
 */

#include <stdio.h>
#include <stdlib.h>
#include "Tabuleiro.c"

LinkedList *createCircularList(char *filename)
{
    FILE *fp;
    int size, value, values[26];
    LinkedList *list;

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

int main()
{
    LinkedList *list = createCircularList("defineBoard.txt");

    // printList(list);

    return 0;
}
