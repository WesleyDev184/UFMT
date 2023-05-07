/*
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1 - Trabalho 6 : lst - estática x dinamica
 * Prof Ivairton
 * Discentes:  Lucas Barbosa Amaral, Wesley Antonio Junior dos Santos
 */
#ifndef JOGADOR_C
#define JOGADOR_C

#include <stdio.h>
#include <stdlib.h>

typedef struct nodePlayer
{
    char id;
    int data;
    char position;
    struct NodePLayer *next;
} NodePLayer;

typedef struct listPlayer
{
    NodePLayer *head;
    NodePLayer *rear;
} ListPlayer;

/**
 * This function creates a circular doubly linked list with nodes containing data and an ID.
 *
 * @param size The size parameter is an integer that represents the number of elements in the linked
 * list that will be created.
 * @param values An array of integers containing the values to be stored in the linked list.
 *
 * @return The function `createList` returns a pointer to a `ListPlayer` structure.
 */
ListPlayer *createPlayerList(int size)
{
    ListPlayer *l = (ListPlayer *)malloc(sizeof(ListPlayer));
    l->head = NULL;
    l->rear = NULL;

    NodePLayer *new_node = NULL;
    for (int i = 0; i < size; i++)
    {
        new_node = (NodePLayer *)malloc(sizeof(NodePLayer));
        new_node->data = 0;
        new_node->id = 'Z' - i;
        new_node->position = NULL;
        new_node->next = NULL;

        if (l->head == NULL)
        {
            // Se estiver vazia, o novo nó é o nó cabeça
            l->head = new_node;
            l->rear = new_node;
        }
        else
        {
            // Se não estiver vazia, o novo nó aponta para o nó cabeça atual
            l->rear->next = new_node;
            l->rear = new_node;
        }
    }
    l->rear->next = l->head;

    return l;
}

void setPosition(ListPlayer *list, char id, char position)
{
    NodePLayer *current = list->head;

    // Percorre a lista até encontrar o nó com o ID informado
    while (current->id != id)
    {
        current = current->next;
    }

    current->position = position;
}

void printPlayerList(ListPlayer *list)
{
    // Verifica se a lista encadeada dupla está vazia
    if (list->head == NULL)
    {
        printf("Lista vazia :(");
    }
    else
    {
        // Se não estiver vazia, percorre a lista até encontrar o último nó
        printf("Players: \n");
        NodePLayer *current = list->head;
        while (current != list->rear)
        {
            printf("%c: ", current->id);
            printf("%d ", current->data);
            current = current->next;
            printf("\n");
        }
        printf("%c: ", current->id);
        printf("%d ", current->data);
    }
    printf("\n");
}

void destroyPlayer(ListPlayer *list, char id)
{
    NodePLayer *current = list->head;
    NodePLayer *previous = NULL;

    // Percorre a lista até encontrar o nó com o ID informado
    while (current->id != id)
    {
        previous = current;
        current = current->next;
    }

    // Se o nó for o nó cabeça, o nó cabeça aponta para o próximo nó
    if (current == list->head)
    {
        list->head = current->next;
    }
    else
    {
        // Se não for o nó cabeça, o nó anterior aponta para o próximo nó
        previous->next = current->next;
    }

    // Se o nó for o nó cauda, o nó cauda aponta para o nó anterior
    if (current == list->rear)
    {
        list->rear = previous;
    }

    // Libera o nó da memória
    free(current);
}

#endif
