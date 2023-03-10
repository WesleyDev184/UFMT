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
void add_node(LinkedList *list, int data)
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

// Função que imprime todos os elementos da lista encadeada
void print_list(LinkedList *list)
{
    Node *current = list->head;
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
    add_node(&list, 1);
    add_node(&list, 2);
    add_node(&list, 3);

    // Imprime todos os nós da lista
    print_list(&list);

    return 0;
}