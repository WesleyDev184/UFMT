#include <stdio.h>
#include <stdlib.h>

typedef struct node
{                      // Definição da estrutura do nó da fila
    int data;          // Dado armazenado no nó
    struct node *next; // Ponteiro para o próximo nó da fila
} Node;

typedef struct queue
{                // Definição da estrutura da fila
    Node *front; // Ponteiro para o primeiro nó da fila
    Node *rear;  // Ponteiro para o último nó da fila
} Queue;

Queue *create_queue()
{                                                  // Função para criar uma nova fila vazia
    Queue *queue = (Queue *)malloc(sizeof(Queue)); // Aloca espaço para a fila
    queue->front = NULL;                           // Define o ponteiro de início como NULL
    queue->rear = NULL;                            // Define o ponteiro de fim como NULL
    return queue;                                  // Retorna a fila criada
}

void enqueue(Queue *queue, int data)
{                                                  // Função para adicionar um elemento à fila
    Node *new_node = (Node *)malloc(sizeof(Node)); // Aloca espaço para o novo nó
    new_node->data = data;                         // Define o dado do novo nó
    new_node->next = NULL;                         // Define o próximo nó como NULL

    if (queue->rear == NULL)
    {                            // Se a fila está vazia
        queue->front = new_node; // Define o ponteiro de início e fim como o novo nó
        queue->rear = new_node;
    }
    else
    {                                 // Se a fila não está vazia
        queue->rear->next = new_node; // Define o próximo nó do último nó como o novo nó
        queue->rear = new_node;       // Define o ponteiro de fim como o novo nó
    }
}

int dequeue(Queue *queue)
{ // Função para remover o elemento mais antigo da fila
    if (queue->front == NULL)
    {                                // Se a fila está vazia
        printf("Queue is empty.\n"); // Imprime uma mensagem de erro
        return -1;                   // Retorna um valor inválido
    }
    else
    {                                      // Se a fila não está vazia
        int data = queue->front->data;     // Armazena o dado do primeiro nó
        Node *temp = queue->front;         // Armazena o ponteiro para o primeiro nó
        queue->front = queue->front->next; // Define o ponteiro de início como o próximo nó
        free(temp);                        // Libera o espaço alocado para o primeiro nó
        if (queue->front == NULL)
        {                       // Se a fila ficar vazia
            queue->rear = NULL; // Define o ponteiro de fim como NULL
        }
        return data; // Retorna o dado do primeiro nó
    }
}

void print_queue(Queue *queue)
{ // Função para imprimir todos os elementos da fila
    if (queue->front == NULL)
    {                                // Se a fila está vazia
        printf("Queue is empty.\n"); // Imprime uma mensagem de erro
    }
    else
    {                                 // Se a fila não está vazia
        Node *current = queue->front; // Ponteiro para percorrer a fila
        while (current != NULL)
        {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

int main()
{
    Queue *queue = create_queue();

    int option;
    do
    {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Print Queue\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            int data;
            printf("Enter data to enqueue: ");
            scanf("%d", &data);
            enqueue(queue, data);
            break;
        }
        case 2:
        {
            int data = dequeue(queue);
            if (data != -1)
            {
                printf("Dequeued element: %d\n", data);
            }
            break;
        }
        case 3:
        {
            printf("Queue: ");
            print_queue(queue);
            break;
        }
        case 4:
        {
            printf("Exiting program...\n");
            break;
        }
        default:
        {
            printf("Invalid choice. Try again.\n");
            break;
        }
        }
    } while (option != 4);

    return 0;
}