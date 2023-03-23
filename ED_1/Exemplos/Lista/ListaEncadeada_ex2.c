#include <stdio.h>;
#include <stdlib.h>;
#include <time.h>;

/**
 * A Node is a structure that contains an integer and a pointer to a Node.
 * @property {int} data - This is the data that the node will hold.
 * @property next - This is a pointer to the next node in the list.
 */
typedef struct node
{
    int data;
    struct node *next;
} Node;

/**
 * A linked list is a pointer to a node.
 * @property {Node} head - The head of the linked list.
 * @property {Node} rear - The last node in the linked list.
 */
typedef struct linkedList
{
    Node *head;
    Node *rear;
} LinkedList;

/* A function prototype. */
LinkedList *CreateList();
void InsertAtStart(LinkedList *, int);
void InsertAtEnd(LinkedList *, int);
void InsertAtPosition(LinkedList *, int, int);
void printLinkedList(LinkedList *);
void InsertAtStartTest(LinkedList *);
void InsertAtPositionTest(LinkedList *);
void InsertAtEndTest(LinkedList *);
void removeAtStart(LinkedList *);
void removeAtEnd(LinkedList *);
void removeAtPosition(LinkedList *, int);

/**
 * Create a new LinkedList, and return a pointer to it.
 *
 * @return A pointer to a LinkedList.
 */
LinkedList *CreateList()
{
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    l->head = NULL;
    l->rear = NULL;
    return l;
}

/**
 * If the list is empty, the new node is the head node, otherwise the new node points to the current
 * head node and becomes the new head node.
 *
 * @param list A pointer to the LinkedList structure.
 * @param data The data to be inserted into the list.
 */
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

/**
 * It creates a new node, sets its data to the value passed in, sets its next pointer to NULL, and then
 * adds it to the end of the list
 *
 * @param list The list to insert the node into.
 * @param data The data to be inserted into the list.
 */
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

/**
 * It inserts a new node at a given position in a linked list
 *
 * @param list The list where you want to insert the new node.
 * @param data the data to be inserted
 * @param position The position where you want to insert the new node.
 */
void InsertAtPosition(LinkedList *list, int data, int position)
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
        Node *aux = list->head;
        int i = 1;
        while (i < position && aux->next != NULL)
        {
            aux = aux->next;
            i++;
        }
        new_node->next = aux->next;
        aux->next = new_node;
    }
}

/**
 * It removes the first node of the list
 *
 * @param list pointer to the list
 */
void removeAtStart(LinkedList *list)
{
    if (list->head == NULL)
    {
        printf("Lista vazia :(");
    }
    else
    {
        Node *aux = list->head;
        list->head = list->head->next;
        free(aux);
    }
}

/**
 * If the list is not empty, then if the list has only one element, then set the head and rear to NULL,
 * otherwise, set the rear to the second to last element and set the next pointer of the rear to NULL.
 *
 * @param list pointer to the list
 */
void removeAtEnd(LinkedList *list)
{
    if (list->head == NULL)
    {
        printf("Lista vazia :(");
    }
    else
    {
        Node *aux = list->head;
        if (aux->next == NULL) // lista possui apenas um elemento
        {
            list->head = list->rear = NULL;
            free(aux);
        }
        else
        {
            while (aux->next != list->rear)
            {
                aux = aux->next;
            }
            free(list->rear);
            list->rear = aux;
            list->rear->next = NULL;
        }
    }
}

/**
 * It removes the node at the given position
 *
 * @param list the list
 * @param position the position of the node to be removed
 */
void removeAtPosition(LinkedList *list, int position)
{
    if (list->head == NULL)
    {
        printf("Lista vazia :(");
    }
    else
    {
        Node *aux = list->head;
        int i = 1;
        while (i < position && aux->next != NULL)
        {
            aux = aux->next;
            i++;
        }
        Node *aux2 = aux->next;
        aux->next = aux->next->next;
        free(aux2);
    }
}

/**
 * It prints the list
 *
 * @param list The list to be printed
 */
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

    InsertAtStart(list, 1);
    InsertAtStart(list, 2);
    InsertAtStart(list, 3);

    printList(list);

    InsertAtEnd(list, 4);
    InsertAtEnd(list, 5);
    InsertAtEnd(list, 6);

    printList(list);

    InsertAtPosition(list, 7, 3);
    InsertAtPosition(list, 8, 4);
    InsertAtPosition(list, 9, 5);

    printList(list);

    removeAtStart(list);
    removeAtStart(list);

    printList(list);

    removeAtEnd(list);
    removeAtEnd(list);

    printList(list);

    removeAtPosition(list, 2);
    removeAtPosition(list, 2);

    printList(list);

    return 0;
}