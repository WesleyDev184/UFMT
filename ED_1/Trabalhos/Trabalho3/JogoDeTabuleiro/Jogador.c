#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de nó
struct node
{
    int data;
    struct node *next;
};

// Função para inserir um novo elemento na lista circular
void insert(struct node **head, int data)
{
    // Aloca um novo nó
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;

    // Se a lista estiver vazia, o novo nó se torna o primeiro e único elemento
    if (*head == NULL)
    {
        *head = new_node;
        new_node->next = *head;
    }
    // Caso contrário, insere o novo nó no final da lista
    else
    {
        struct node *temp = *head;
        while (temp->next != *head)
        {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = *head;
    }
}
