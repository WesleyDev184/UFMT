#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

struct queue {
    int items[MAX_SIZE];
    int front;
    int rear;
};

// Função para criar uma nova fila
struct queue* create_queue() {
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

// Função para verificar se a fila está vazia
int is_empty(struct queue* q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

// Função para verificar se a fila está cheia
int is_full(struct queue* q) {
    if (q->rear == MAX_SIZE - 1)
        return 1;
    else
        return 0;
}

// Função para adicionar um elemento no final da fila
void enqueue(struct queue* q, int value) {
    if (is_full(q)) {
        printf("\nQueue is full\n");
    } else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

// Função para remover um elemento do início da fila
int dequeue(struct queue* q) {
    int item;
    if (is_empty(q)) {
        printf("\nQueue is empty\n");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = -1;
            q->rear = -1;
        }
    }
    return item;
}

// Função para exibir os elementos da fila
void display(struct queue* q) {
    int i;
    if (is_empty(q))
        printf("\nQueue is empty\n");
    else {
        printf("\nQueue contains:\n\n");
        for (i = q->front; i <= q->rear; i++)
            printf("%d ", q->items[i]);
        printf("\n");
    }
}

int main() {
    struct queue* q = create_queue();

    int choice, value;

    while (1) {
        printf("\nSelect an option:\n");
        printf("1. Add to queue\n");
        printf("2. Remove from queue\n");
        printf("3. Display queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter a value to add to the queue: ");
                scanf("%d", &value);
                enqueue(q, value);
                break;
            case 2:
                dequeue(q);
                break;
            case 3:
                display(q);
                break;
            case 4:
                printf("Exiting program\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}