/**
 * UFMT - Ciencia da Computacao
 * Disciplina de ED 1
 *
 * Prof. Ivairton
 * Wesley Antonio Junior Dos santos
 * RGA: 202011722024
 * Felipe Rodrigues Dantas
 * RGA: 202111722010
 * Implementação de LISTA com alocação Dinâmica (Dupla)
 * 2023-03-15
 */

#include <stdio.h>;
#include <stdlib.h>;
#include <time.h>;

/**
 * A Node is a structure that contains an integer, a pointer to a Node, and a pointer to a Node.
 * @property {int} data - The data that the node holds.
 * @property next - This is a pointer to the next node in the list.
 * @property prev - The previous node in the list.
 */
typedef struct node
{
    int data;
    struct node *next;
    struct node *prev
} Node;

/**
 * A linked list is a structure that contains a pointer to the first node in the list and a pointer to
 * the last node in the list.
 * @property {Node} head - The head of the linked list.
 * @property {Node} rear - The last node in the linked list.
 */
typedef struct linkedList
{
    Node *head;
    Node *rear;
} LinkedList;

/* A function prototype */
LinkedList *CreateList();
void InsertAtStart(LinkedList *, int);
void InsertAtEnd(LinkedList *, int data);
void InsertAtPosition(LinkedList *, int, int);
void PrintLinkedList(LinkedList *list);
void InsertAtStartTest(LinkedList *list);
void InsertAtPositionTest(LinkedList *);
void InsertAtEndTest(LinkedList *);

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
 * It inserts a node at the start of the list.
 *
 * @param list A pointer to the LinkedList structure.
 * @param data The data to be inserted into the list.
 */
void InsertAtStart(LinkedList *list, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;

    if (list->head == NULL)
    {
        list->head = node;
        list->rear = node;
    }
    else
    {
        node->next = list->head;
        list->head = node;
    }
}

/**
 * It creates a new node, sets its next and prev pointers to NULL, and then inserts it at the end of
 * the list
 *
 * @param list A pointer to the list.
 * @param data The data to be inserted.
 */
void InsertAtEnd(LinkedList *list, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;

    // Caso a lista esteja vazia, o novo nó será a cabeça e a cauda da lista.
    if (list->head == NULL)
    {
        list->head = node;
        list->rear = node;
    }
    else
    {
        // Caso a lista não esteja vazia, o novo nó será inserido após o último nó da lista.
        list->rear->next = node;
        node->prev = list->rear;
        list->rear = node;
    }
}

/**
 * Inserts a node at the specified position in the list
 *
 * @param list The list to insert the node into.
 * @param data the data to be inserted
 * @param position the position where you want to insert the new node
 */
void InsertAtPosition(LinkedList *list, int data, int position)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;

    if (list->head == NULL)
    {
        list->head = node;
        list->rear = node;
    }
    else
    {
        Node *aux = list->head;
        int i = 0;
        while (i < position && aux->next != NULL)
        {
            aux = aux->next;
            i++;
        }
        if (aux == list->rear)
        {
            InsertAtEnd(list, data);
        }
        else
        {
            node->next = aux->next;
            node->prev = aux;
            aux->next = node;
        }
    }
}

/**
 * It prints the linked list by traversing the list and printing each node's data
 *
 * @param list The linked list to print.
 */
void PrintLinkedList(LinkedList *list)
{
    Node *current = list->head;

    printf("Linked List: ");

    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }

    printf("\n");
}

void InsertAtStartTest(LinkedList *list)
{
    clock_t start_time, end_time;
    double total_time;
    srand(time(NULL));

    start_time = clock();

    // gera 1/3 das entradas no inicio
    for (int i = 1; i <= 10000 / 3; i++)
    {
        int random = rand() % 1000;
        InsertAtStart(list, random);
    }

    end_time = clock();
    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("start - Tempo total de execucao: %f segundos.\n", total_time);
}

void InsertAtPositionTest(LinkedList *list)
{
    clock_t start_time, end_time;
    double total_time;
    srand(time(NULL));

    start_time = clock();

    // gera 1/3 das entradas inserindo em alguma posição
    for (int i = 1; i <= 10000 / 3; i++)
    {
        int randomPos = rand() % 10000;
        int random = rand() % 1000;
        InsertAtPosition(list, random, randomPos);
    }
    end_time = clock();
    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("pos - Tempo total de execucao: %f segundos.\n", total_time);
}

void InsertAtEndTest(LinkedList *list)
{
    clock_t start_time, end_time;
    double total_time;
    srand(time(NULL));

    start_time = clock(); // inicia a contagem do tempo2

    // gera 1/3 das entradas no final
    for (int i = 1; i <= 10000 / 3; i++)
    {
        int random = rand() % 1000;
        InsertAtEnd(list, random);
    }

    end_time = clock(); // finaliza a contagem do tempo
    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("End - Tempo total de execucao: %f segundos.\n", total_time);
}

int main()
{
    LinkedList *list = CreateList();

    InsertAtStartTest(list);
    InsertAtEndTest(list);
    InsertAtPositionTest(list);
}