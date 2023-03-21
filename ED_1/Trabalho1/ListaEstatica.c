/**
 * UFMT - Ciencia da Computacao
 * Disciplina de ED 1
 *
 * Prof. Ivairton
 * Wesley Antonio Junior Dos santos
 * RGA: 202011722024
 * Felipe Rodrigues Dantas
 * RGA: 202111722010
 * Implementação de LISTA com alocacao Estatica
 * 2023-03-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DATA 10000

/**
 * A List is a structure that contains an array of integers and an integer.
 * @property {int} items - an array of integers
 * @property {int} cont - The number of items in the list.
 */
typedef struct list
{
    int items[MAX_DATA];
    int cont;
} List;

/* A function prototype. */
int IsFull(List *);
int IsEmpty(List *);
void insertAtStart(List *, int);
void insertAtEnd(List *, int);
void insertAtPosition(List *, int, int);
void printList(List *);
void insertAtStartTest(List *);
void insertAtPositionTest(List *);
void insertAtEndTest(List *);

/**
 * It checks if the list is full.
 *
 * @param list The list to check.
 *
 * @return the value of the variable list->cont.
 */
int IsFull(List *list)
{
    if (list->cont == MAX_DATA)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * If the list is empty, return 1, else return 0
 *
 * @param list The list to check.
 *
 * @return the value of the variable list->cont.
 */
int IsEmpty(List *list)
{
    if (list->cont == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * It inserts an item at the start of the list
 *
 * @param list pointer to the list
 * @param data the data to be inserted
 */
void insertAtStart(List *list, int data)
{
    if (IsFull(list))
    {
        printf("\nLista Cheia\n");
    }
    else
    {
        for (int i = list->cont; i > 0; i--)
        {
            list->items[i] = list->items[i - 1];
        }
        list->items[0] = data;
        list->cont++;
    }
}

/**
 * It inserts an item at the end of the list
 *
 * @param list pointer to the list
 * @param data the data to be inserted
 */
void insertAtEnd(List *list, int data)
{
    if (IsFull(list))
    {
        printf("\nLista Cheia\n");
    }
    else
    {
        list->items[list->cont] = data;
        list->cont++;
    }
}

/**
 * It inserts an element at a given position
 *
 * @param list pointer to the list
 * @param data the data to be inserted
 * @param pos position to insert the data
 */
void insertAtPosition(List *list, int data, int pos)
{
    if (IsFull(list))
    {
        printf("\nLista Cheia\n");
    }
    else
    {
        for (int i = list->cont; i > pos; i--)
        {
            list->items[i] = list->items[i - 1];
        }
        list->items[pos] = data;
        list->cont++;
    }
}

/**
 * It prints the list
 *
 * @param list pointer to the list
 */
void printList(List *list)
{
    if (IsEmpty(list))
    {
        printf("\nLista Vazia\n");
    }
    else
    {
        printf("Lista: \n");
        for (int i = 0; i < list->cont; i++)
        {
            printf("%d ", list->items[i]);
            if ((i + 1) % 10 == 0)
            {
                printf("\n");
            }
        }
        printf("\n");
    }
}

void insertAtStartTest(List *list)
{
    clock_t start_time, end_time;
    double total_time;
    srand(time(NULL));

    start_time = clock();

    // gera 1/3 das entradas no inicio
    for (int i = 1; i <= 10000 / 3; i++)
    {
        int random = rand() % 1000;
        insertAtStart(list, random);
    }

    end_time = clock();
    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("start -Tempo total de execucao: %f segundos.\n", total_time);
}

void insertAtPositionTest(List *list)
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
        insertAtPosition(list, random, randomPos);
    }

    end_time = clock();
    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("pos - Tempo total de execucao: %f segundos.\n", total_time);
}

void insertAtEndTest(List *list)
{
    clock_t start_time, end_time;
    double total_time;
    srand(time(NULL));

    start_time = clock(); // inicia a contagem do tempo

    // gera 1/3 das entradas no final
    for (int i = 1; i <= 10000 / 3; i++)
    {
        int random = rand() % 1000;
        insertAtEnd(list, random);
    }

    end_time = clock(); // finaliza a contagem do tempo
    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("End - Tempo total de execucao: %f segundos.\n", total_time);
}

int main()
{
    List list;
    list.cont = 0;

    insertAtStartTest(&list);
    insertAtEndTest(&list);
    insertAtPositionTest(&list);
}