#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó da lista
struct Node
{
    int data;
    struct Node *next;
};

typedef struct Node Node;

// Função que cria um novo nó com o valor especificado
Node *create_node(int data)
{
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Função que insere um novo nó no final da lista e retorna um ponteiro para a cabeça da lista
Node *insert_node_at_end(Node *head, int data)
{
    Node *node = create_node(data);
    if (head == NULL)
    {
        head = node;
    }
    else
    {
        Node *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;
    }
    return head;
}

// Função que insere um novo nó no início da lista e retorna um ponteiro para a cabeça da lista
Node *insert_node_at_beginning(Node *head, int data)
{
    Node *node = create_node(data);
    if (head == NULL)
    {
        head = node;
    }
    else
    {
        node->next = head;
        head = node;
    }
    return head;
}

// Função que insere um novo nó em uma posição especificada da lista e retorna um ponteiro para a cabeça da lista
Node *insert_node_at_position(Node *head, int data, int position)
{
    Node *node = create_node(data);
    if (head == NULL || position == 0)
    {
        node->next = head;
        head = node;
    }
    else
    {
        Node *current = head;
        int i = 1;
        while (i < position && current->next != NULL)
        {
            current = current->next;
            i++;
        }
        node->next = current->next;
        current->next = node;
    }
    return head;
}

// Função que remove o nó no início da lista e retorna um ponteiro para a cabeça da lista
Node *remove_node_at_beginning(Node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    Node *new_head = head->next;
    free(head);
    return new_head;
}

// Função que remove o nó no final da lista e retorna um ponteiro para a cabeça da lista
Node *remove_node_at_end(Node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (head->next == NULL)
    {
        free(head);
        return NULL;
    }
    Node *current = head;
    while (current->next->next != NULL)
    {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    return head;
}

// Função que remove o nó em uma posição especificada da lista e retorna um ponteiro para a cabeça da lista
Node *remove_node_at_position(Node *head, int position)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (position == 0)
    {
        Node *new_head = head->next;
        free(head);
        return new_head;
    }
    Node *current = head;
    // Localiza o nó anterior ao que será removido
    int i = 1;
    while (i < position && current->next != NULL)
    {
        current = current->next;
        i++;
    }
    if (current->next == NULL)
    {
        return head;
    }
    Node *node_to_remove = current->next;
    current->next = node_to_remove->next;
    free(node_to_remove);
    return head;
}

// Função que remove o primeiro nó com o valor especificado e retorna um ponteiro para a cabeça da lista
Node *remove_node_by_value(Node *head, int value)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (head->data == value)
    {
        Node *new_head = head->next;
        free(head);
        return new_head;
    }
    Node *current = head;
    while (current->next != NULL && current->next->data != value)
    {
        current = current->next;
    }
    if (current->next != NULL)
    {
        Node *node_to_remove = current->next;
        current->next = node_to_remove->next;
        free(node_to_remove);
    }
    return head;
}

// Função que busca um valor na lista e retorna um ponteiro para o nó correspondente, ou NULL se o valor não for encontrado
Node *find_node_by_value(Node *head, int value)
{
    Node *current = head;
    while (current != NULL)
    {
        if (current->data == value)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Função que imprime os valores de todos os nós da lista
void print_list(Node *head)
{
    Node *current = head;
    printf("Lista: ");
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void getPosition(Node *head, int value)
{
    Node *current = head;
    int i = 0;
    while (current != NULL)
    {
        if (current->data == value)
        {
            printf("Posicao: %d ", i);
        }
        current = current->next;
        i++;
    }
    printf("\n");
}

// Função principal do programa, que cria uma lista vazia e permite ao usuário adicionar e remover nós da lista
int main()
{
    Node *head = NULL;
    int opcao, data, position, value;
    do
    {
        printf("Escolha uma opcao:\n");
        printf("1 - Inserir no final\n");
        printf("2 - Inserir no inicio\n");
        printf("3 - Inserir por posicao\n");
        printf("4 - Remover no final\n");
        printf("5 - Remover no inicio\n");
        printf("6 - Remover por posicao\n");
        printf("7 - Remover por valor\n");
        printf("8 - Buscar valor\n");
        printf("9 - Imprimir lista\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Digite o valor a ser inserido: ");
            scanf("%d", &data);
            head = insert_node_at_end(head, data);
            break;
        case 2:
            printf("Digite o valor a ser inserido: ");
            scanf("%d", &data);
            head = insert_node_at_beginning(head, data);
            break;
        case 3:
            printf("Digite o valor a ser inserido: ");
            scanf("%d", &data);
            printf("Digite a posicao: ");
            scanf("%d", &position);
            head = insert_node_at_position(head, data, position);
            break;
        case 4:
            head = remove_node_at_end(head);
            break;
        case 5:
            head = remove_node_at_beginning(head);
            break;
        case 6:
            printf("Digite a posicao: ");
            scanf("%d", &position);
            head = remove_node_at_position(head, position);
            break;
        case 7:
            printf("Digite o valor a ser removido: ");
            scanf("%d", &value);
            head = remove_node_by_value(head, value);
            break;
        case 8:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &value);
            Node *node = find_node_by_value(head, value);
            if (node == NULL)
            {
                printf("Valor nao encontrado na lista\n");
            }
            else
            {
                printf("Valor encontrado na lista\n");
                getPosition(head, value);
            }
            break;
        case 9:
            print_list(head);
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida\n");
        }
    } while (opcao != 0);
    // Libera a memória alocada para a lista
    while (head != NULL)
    {
        Node *node_to_remove = head;
        head = head->next;
        free(node_to_remove);
    }
    return 0;
}
