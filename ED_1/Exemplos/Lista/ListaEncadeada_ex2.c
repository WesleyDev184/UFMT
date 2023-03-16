#include <stdio.h>;
#include <stdlib.h>;

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct linkedList
{
    Node *head;
    Node *rear;
} LinkedList;

LinkedList *CreateList()
{
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    l->head = NULL;
    l->rear = NULL;
    return l;
}

void InsertAtStart(LinkedList *list, int data)
{
    // Aloca dinamicamente um novo nó
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

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
        list->head = new_node;
    }
}

void InsertAtEnd(LinkedList *list, int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    if (list->head == NULL)
    {
        list->head = new_node;
        list->rear = new_node;
    }
    else
    {
        // Adiciona o novo nó ao final da lista
        list->rear->next = new_node;
        list->rear = new_node;
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

    LinkedList *list = CreateList();

    InsertAtEnd(list, 2);
    InsertAtEnd(list, 2);
    InsertAtEnd(list, 2);
    InsertAtEnd(list, 2);
    InsertAtStart(list, 1);
    InsertAtStart(list, 1);
    InsertAtStart(list, 1);
    InsertAtStart(list, 1);

    printList(list);
}