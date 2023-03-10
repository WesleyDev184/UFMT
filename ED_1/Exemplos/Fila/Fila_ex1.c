#include <stdio.h>

#define MAX 10

typedef struct queue
{
    int items[MAX];
    int rear;
} Queue;

Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->rear = 0;
    return q;
}

int isFull(Queue *q)
{
    if (q->rear == MAX)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isEmpty(Queue *q)
{
    if (q->rear == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enqueue(Queue *q, int item)
{
    if (isFull(q))
    {
        printf("Fila cheia");
    }
    else
    {
        q->items[q->rear] = item;
        q->rear++;
    }
}

void dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Fila vazia");
    }
    else
    {
        for (int i = 0; i < q->rear; i++)
        {
            q->items[i] = q->items[i + 1];
        }
        q->rear--;
    }
}

void printQueue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Fila vazia");
    }
    else
    {
        printf("Fila: \n");
        for (int i = 0; i < q->rear; i++)
        {
            printf("%d ", q->items[i]);
        }
        printf("\n");
    }
}

int main()
{
    Queue *q = createQueue();

    int opcao, item;

    do
    {
        printf("\n --- Fila --- \n");
        printf("1 - Inserir na fila \n");
        printf("2 - Remover da fila \n");
        printf("3 - Imprimir fila \n");
        printf("4 - Sair \n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            printf("Digite o item: ");
            scanf("%d", &item);
            enqueue(q, item);
            break;
        case 2:
            dequeue(q);
            break;
        case 3:
            printQueue(q);
            break;
        case 4:
            printf("Saindo...");
            break;
        default:
            printf("Opcao invalida");
            break;
        }
    } while (opcao != 4);
}
