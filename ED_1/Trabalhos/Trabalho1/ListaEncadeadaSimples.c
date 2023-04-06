/**
 * UFMT - Ciencia da Computacao
 * Disciplina de ED 1
 *
 * Prof. Ivairton
 * Wesley Antonio Junior Dos santos
 * RGA: 202011722024
 * Felipe Rodrigues Dantas
 * RGA: 202111722010
 * Implementação de LISTA com alocação Dinâmica
 * 2023-03-15
 */

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

    printf("start -Tempo total de execucao: %f segundos.\n", total_time);
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

    start_time = clock(); // inicia a contagem do tempo

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