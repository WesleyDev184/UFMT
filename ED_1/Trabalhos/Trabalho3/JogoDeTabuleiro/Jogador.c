#ifndef JOGADORES_C
#define JOGADORES_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodePlayer
{
    char id;
    int data;
    struct nodePlayer *next;
    // struct node *prev;
} NodePlayer;

typedef struct listPlayers
{
    NodePlayer *head;
    NodePlayer *rear;
} ListPlayers;

/**
 * This function creates a circular doubly linked list with nodes containing data and an ID.
 *
 * @param size The size parameter is an integer that represents the number of elements in the linked
 * list that will be created.
 * @param values An array of integers containing the values to be stored in the linked list.
 *
 * @return The function `createList` returns a pointer to a `LinkedList` structure.
 */
ListPlayers *createPlayerList(int size, char **values)
{
    ListPlayers *l = (ListPlayers *)malloc(sizeof(ListPlayers));
    l->head = NULL;
    l->rear = NULL;

    NodePlayer *new_node = NULL;
    for (int i = 0; i < size; i++)
    {
        new_node = (NodePlayer *)malloc(sizeof(NodePlayer));
        new_node->id = (char *)malloc(strlen(values[i]) + 1); // Aloca espaço para a string, incluindo o caractere terminador
        new_node->data = NULL;                                // Define o campo 'data' como um ponteiro e atribui o valor NULL
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
            new_node->next = l->head;

            l->head = new_node;
        }
    }

    l->rear->next = l->head;
    return l;
}

void destroyPlayerList(ListPlayers *list)
{
    // Percorre a lista e libera a memória alocada para cada nó e para cada string no campo 'id'
    NodePlayer *current = list->head;
    while (current != NULL)
    {
        NodePlayer *next = current->next;
        free(current->id);
        free(current);
        current = next;
    }

    // Libera a memória alocada para a estrutura da lista
    free(list);
}

void printListPlayer(ListPlayers *list)
{
    // Verifica se a lista encadeada dupla está vazia
    if (list->head == NULL)
    {
        printf("Lista vazia :(");
    }
    else
    {
        // Se não estiver vazia, percorre a lista até encontrar o último nó
        printf("Lista: ");
        NodePlayer *current = list->head;
        while (current != list->rear)
        {
            printf("%s ", current->id);
            current = current->next;
        }
        printf("%s ", current->id);
    }
    printf("\n");
}

#endif
