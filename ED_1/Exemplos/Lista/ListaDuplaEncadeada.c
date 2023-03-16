#include <stdio.h>
#include <stdlib.h>

// Define uma estrutura para os nós da lista encadeada dupla
typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
} Node;

// Define uma estrutura para a lista encadeada dupla, que contém apenas o nó cabeça
typedef struct linked_list
{
    Node *head;
    Node *rear;
} LinkedList;

LinkedList *createList()
{
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    l->head = NULL;
    l->rear = NULL;
    return l;
} 

// Função que adiciona um novo nó ao final da lista encadeada dupla
void insertAtEnd(LinkedList *list, int data)
{
    // Aloca dinamicamente um novo nó
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    // Verifica se a lista encadeada dupla está vazia
    if (list->head == NULL)
    {
        // Se estiver vazia, o novo nó é o nó cabeça
        list->head = new_node;
        list->rear = new_node;
    }
    else
    {
        // Se não estiver vazia, percorre a lista até encontrar o último nó
        Node *current = list->rear;
        // Adiciona o novo nó ao final da lista
        current->next = new_node;
        new_node->prev = current;
        list->rear = new_node;
    }
}

// Função que adiciona um novo nó ao início da lista encadeada dupla
void insertAtStart(LinkedList *list, int data)
{
    // Aloca dinamicamente um novo nó
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    // Verifica se a lista encadeada dupla está vazia
    if (list->head == NULL)
    {
        // Se estiver vazia, o novo nó é o nó cabeça
        list->head = new_node;
        list->rear = new_node;
    }
    else
    {
        // Se não estiver vazia, o novo nó aponta para o nó cabeça atual
        new_node->next = list->head;
        new_node->prev = NULL;
        list->head->prev = new_node;
        list->head = new_node;
    }
}

// Função que adiciona um novo nó por posição da lista encadeada dupla
void insertAtPosition(LinkedList *list, int data, int position)
{
    // Aloca dinamicamente um novo nó
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    // Verifica se a lista encadeada dupla está vazia
    if (list->head == NULL)
    {
        // Se estiver vazia, o novo nó é o nó cabeça
        list->head = new_node;
        list->rear = new_node;
    }
    else
    {
        // Se não estiver vazia, percorre a lista até encontrar o último nó
        Node *current = list->head;
        int i = 0;
        while (i < position && current != NULL)
        {
            current = current->next;
            i++;
        }
        if (current == list->rear)
        {
            insertAtEnd(list, data);
        }
        else
        {
            // Adiciona o novo nó a lista
            new_node->next = current->next;
            new_node->prev = current;
            current->next = new_node;
        }
    }
}

// Função que remove um nó da lista encadeada dupla
void removeNodeAtPosition(LinkedList *list, int pos)
{
    // Verifica se a lista encadeada dupla está vazia
    if (list->head == NULL)
    {
        printf("Lista vazia :(");
    }
    else
    {
        // Se não estiver vazia, percorre a lista até encontrar o último nó
        Node *current = list->head;
        int i = 0;
        while (i < pos && current->next != NULL)
        {
            current = current->next;
            i++;
        }
        // Remove o nó da lista
        current->next = current->next->next;
        current->next->prev = current;
        free(current->next->prev);
    }
}

// Função que remove um nó no inicio da lista da lista encadeada dupla
void removeNodeAtStart(LinkedList *list)
{
    // Verifica se a lista encadeada dupla está vazia
    if (list->head == NULL)
    {
        printf("Lista vazia :(");
    }
    else
    {
        // Se não estiver vazia, percorre a lista até encontrar o último nó
        Node *current = list->head;
        // Remove o nó da lista
        list->head = current->next;
        list->head->prev = NULL;
        free(current);
    }
}

// Função que remove um nó no final da lista da lista encadeada dupla
void removeNodeAtEnd(LinkedList *list)
{
    // Verifica se a lista encadeada dupla está vazia
    if (list->head == NULL)
    {
        printf("Lista vazia :(");
    }
    else
    {
        // Se não estiver vazia, percorre a lista até encontrar o último nó
        Node *current = list->rear;
        // Remove o nó da lista
        list->rear = current->prev;
        list->rear->next = NULL;
        free(current);
    }
}

// Função que imprime a lista encadeada dupla
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
        while (current != NULL)
        {
            printf("%d ", current->data);
            current = current->next;
        }
    }
    printf("\n");
}

int main()
{
    LinkedList *list = createList();

    insertAtEnd(list, 1);
    insertAtEnd(list, 2);
    insertAtEnd(list, 3);
    insertAtEnd(list, 4);
    insertAtEnd(list, 5);
    insertAtStart(list, 6);
    insertAtStart(list, 7);
    insertAtStart(list, 8);
    insertAtStart(list, 9);
    insertAtStart(list, 10);
    insertAtPosition(list, 11, 3);
    insertAtPosition(list, 12, 10);

    printList(list);

    removeNodeAtStart(list);
    removeNodeAtStart(list);

    printList(list);

    removeNodeAtEnd(list);
    removeNodeAtEnd(list);

    printList(list);

    removeNodeAtPosition(list, 3);

    printList(list);
}