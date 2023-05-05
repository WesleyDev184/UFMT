#ifndef TABULEIRO_C
#define TABULEIRO_C

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char id;
    int data;
    struct node *next;
    struct node *prev;
} Node;

typedef struct linked_list
{
    Node *head;
    Node *rear;
} LinkedList;

/**
 * This function creates a circular doubly linked list with nodes containing data and an ID.
 *
 * @param size The size parameter is an integer that represents the number of elements in the linked
 * list that will be created.
 * @param values An array of integers containing the values to be stored in the linked list.
 *
 * @return The function `createList` returns a pointer to a `LinkedList` structure.
 */
LinkedList *createList(int size, int *values)
{
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    l->head = NULL;
    l->rear = NULL;

    Node *new_node = NULL;
    for (int i = 0; i < size; i++)
    {
        new_node = (Node *)malloc(sizeof(Node));
        new_node->data = values[i];
        new_node->id = 'A' + i;
        new_node->next = NULL;
        new_node->prev = NULL;

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
            new_node->prev = NULL;
            l->head->prev = new_node;
            l->head = new_node;
        }
    }
    l->head->prev = l->rear;
    l->rear->next = l->head;
    return l;
}

void printList(LinkedList *list)
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
        Node *current = list->head;
        while (current != list->rear)
        {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("%d ", current->data);
    }
    printf("\n");
}

#endif
