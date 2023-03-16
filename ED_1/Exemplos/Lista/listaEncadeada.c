// Inclui as bibliotecas de entrada e saída e de alocação dinâmica de memória
#include <stdio.h>
#include <stdlib.h>

// Define uma estrutura para os nós da lista encadeada
typedef struct node
{
    int data;
    struct node *next;
} Node;

// Define uma estrutura para a lista encadeada, que contém apenas o nó cabeça
typedef struct linked_list
{
    Node *head;
} LinkedList;

// Função que adiciona um novo nó ao final da lista encadeada
void insertAtEnd(LinkedList *list, int data)
{
    // Aloca dinamicamente um novo nó
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    // Verifica se a lista encadeada está vazia
    if (list->head == NULL)
    {
        // Se estiver vazia, o novo nó é o nó cabeça
        list->head = new_node;
    }
    else
    {
        // Se não estiver vazia, percorre a lista até encontrar o último nó
        Node *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        // Adiciona o novo nó ao final da lista
        current->next = new_node;
    }
}

// Função que adiciona um novo nó ao início da lista encadeada
void insertAtStart(LinkedList *list, int data)
{
    // Aloca dinamicamente um novo nó
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;

    // Verifica se a lista encadeada está vazia
    if (list->head == NULL)
    {
        // Se estiver vazia, o novo nó é o nó cabeça
        new_node->next = NULL;
        list->head = new_node;
    }
    else
    {
        // Se não estiver vazia, o novo nó aponta para o nó cabeça atual
        new_node->next = list->head;
        // O nó cabeça da lista passa a ser o novo nó
        list->head = new_node;
    }
}

void insertAtPosition(LinkedList *list, int data, int position)
{
    // Aloca dinamicamente um novo nó
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;

    // Verifica se a lista encadeada está vazia
    if (list->head == NULL)
    {
        // Se estiver vazia, o novo nó é o nó cabeça
        new_node->next = NULL;
        list->head = new_node;
    }
    else
    {
        // Se não estiver vazia, o novo nó aponta para o nó cabeça atual
        Node *current = list->head;
        Node *previous = NULL;
        int i = 0;
        while (current->next != NULL && i < position)
        {
            previous = current;
            current = current->next;
            i++;
        }
        previous->next = new_node;
        new_node->next = current;
    }
}

void remeveAtStart(LinkedList *list)
{
    // Verifica se a lista encadeada está vazia
    if (list->head == NULL)
    {
        printf("Lista vazia");
    }
    else
    {
        // Se não estiver vazia, o novo nó aponta para o nó cabeça atual
        Node *current = list->head;
        list->head = current->next;
        free(current);
    }
}

void removeAtEnd(LinkedList *list)
{
    // Verifica se a lista encadeada está vazia
    if (list->head == NULL)
    {
        printf("Lista vazia");
    }
    else
    {
        // Se não estiver vazia, o novo nó aponta para o nó cabeça atual
        Node *current = list->head;
        Node *previous = NULL;
        while (current->next != NULL)
        {
            previous = current;
            current = current->next;
        }
        previous->next = NULL;
        free(current);
    }
}

void removeAtPosition(LinkedList *list, int position)
{
    // Verifica se a lista encadeada está vazia
    if (list->head == NULL)
    {
        printf("Lista vazia");
    }
    else
    {
        // Se não estiver vazia, o novo nó aponta para o nó cabeça atual
        Node *current = list->head;
        Node *previous = NULL;
        int i = 0;
        while (current->next != NULL && i < position)
        {
            previous = current;
            current = current->next;
            i++;
        }
        previous->next = current->next;
        free(current);
    }
}

// Função que imprime todos os elementos da lista encadeada
void print_list(LinkedList *list)
{
    Node *current = list->head;
    printf("Lista: ");
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Função principal
int main()
{
    // Cria uma lista encadeada vazia
    LinkedList list;
    list.head = NULL;

    // Adiciona três nós à lista
    insertAtEnd(&list, 1);
    insertAtEnd(&list, 2);
    insertAtEnd(&list, 3);
    insertAtStart(&list, 0);
    insertAtStart(&list, 4);
    insertAtStart(&list, 5);
    insertAtPosition(&list, 6, 2);

    // Imprime todos os nós da lista
    print_list(&list);

    remeveAtStart(&list);
    removeAtEnd(&list);
    removeAtPosition(&list, 3);

    print_list(&list);

    return 0;
}