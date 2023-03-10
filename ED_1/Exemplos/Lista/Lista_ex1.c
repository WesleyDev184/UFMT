#include <stdio.h>

#define MAX 10

typedef struct list
{
    int items[MAX];
    int cont;
} List;

List *createList()
{
    List *l = (List *)malloc(sizeof(List));
    l->cont = 0;
    return l;
}

int isFull(List *l)
{
    if (l->cont == MAX)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isEmpty(List *l)
{
    if (l->cont == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void insertAtStart(List *l, int item)
{
    if (isFull(l))
    {
        printf("\nLista cheia\n");
    }
    else
    {
        for (int i = l->cont; i > 0; i--)
        {
            l->items[i] = l->items[i - 1];
        }
        l->items[0] = item;
        l->cont++;
    }
}

void insertAtEnd(List *l, int item)
{
    if (isFull(l))
    {
        printf("\nLista cheia\n");
    }
    else
    {
        l->items[l->cont] = item;
        l->cont++;
    }
}

void insertAtPosition(List *l, int item, int pos)
{
    if (isFull(l))
    {
        printf("\nLista cheia\n");
    }
    else
    {
        for (int i = l->cont; i > pos; i--)
        {
            l->items[i] = l->items[i - 1];
        }
        l->items[pos] = item;
        l->cont++;
    }
}

void removeAtStart(List *l)
{
    if (isEmpty(l))
    {
        printf("\nLista vazia\n");
    }
    else
    {
        for (int i = 0; i < l->cont; i++)
        {
            l->items[i] = l->items[i + 1];
        }
        l->cont--;
    }
}

void removeAtEnd(List *l)
{
    if (isEmpty(l))
    {
        printf("\nLista vazia\n");
    }
    else
    {
        l->cont--;
    }
}

void removeAtPosition(List *l, int pos)
{
    if (isEmpty(l))
    {
        printf("\nLista vazia\n");
    }
    else
    {
        for (int i = pos; i < l->cont; i++)
        {
            l->items[i] = l->items[i + 1];
        }
        l->cont--;
    }
}

void removeAtValue(List *l, int item)
{
    if (isEmpty(l))
    {
        printf("\nLista vazia\n");
    }
    else
    {
        for (int i = 0; i < l->cont; i++)
        {
            if (l->items[i] == item)
            {
                for (int j = i; j < l->cont; j++)
                {
                    l->items[j] = l->items[j + 1];
                }
                l->cont--;
            }
        }
    }
}

void seekValue(List *l, int item)
{
    if (isEmpty(l))
    {
        printf("\nLista vazia\n");
    }
    else
    {
        for (int i = 0; i < l->cont; i++)
        {
            if (l->items[i] == item)
            {
                printf("\nO valor %d esta na posicao %d\n", item, i);
            }
        }
    }
}

void seekGraterValue(List *l)
{
    if (isEmpty(l))
    {
        printf("\nLista vazia\n");
    }
    else
    {
        int aux = l->items[0];
        for (int i = 0; i < l->cont; i++)
        {
            if (l->items[i] > aux)
            {
                aux = l->items[i];
            }
        }
        printf("\nO maior valor da lista eh %d\n", aux);
    }
}

void seekSmallerValue(List *l)
{
    if (isEmpty(l))
    {
        printf("\nLista vazia\n");
    }
    else
    {
        int aux = l->items[0];
        for (int i = 0; i < l->cont; i++)
        {
            if (l->items[i] < aux)
            {
                aux = l->items[i];
            }
        }
        printf("\nO menor valor da lista eh %d\n", aux);
    }
}

void printList(List *l)
{
    if (isEmpty(l))
    {
        printf("\nLista vazia\n");
    }
    else
    {
        for (int i = 0; i < l->cont; i++)
        {
            printf("%d ", l->items[i]);
        }
        printf("\n");
    }
}

int main()
{
    List *l = createList();

    int op, item, pos;

    do
    {
        printf("\n------LISTA------\n");
        printf("\n1 - Inserir no inicio");
        printf("\n2 - Inserir no final");
        printf("\n3 - Inserir em uma posicao");
        printf("\n4 - Remover no inicio");
        printf("\n5 - Remover no final");
        printf("\n6 - Remover em uma posicao");
        printf("\n7 - Remover por valor");
        printf("\n8 - Buscar um valor");
        printf("\n9 - Buscar o maior valor");
        printf("\n10 - Buscar o menor valor");
        printf("\n11 - Imprimir lista");
        printf("\n12 - Sair");
        printf("\n\nOpcao: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\nDigite o valor: ");
            scanf("%d", &item);
            insertAtStart(l, item);
            break;
        case 2:
            printf("\nDigite o valor: ");
            scanf("%d", &item);
            insertAtEnd(l, item);
            break;
        case 3:
            printf("\nDigite o valor: ");
            scanf("%d", &item);
            printf("\nDigite a posicao: ");
            scanf("%d", &pos);
            insertAtPosition(l, item, pos);
            break;
        case 4:
            removeAtStart(l);
            break;
        case 5:
            removeAtEnd(l);
            break;
        case 6:
            printf("\nDigite a posicao: ");
            scanf("%d", &pos);
            removeAtPosition(l, pos);
            break;
        case 7:
            printf("\nDigite o valor: ");
            scanf("%d", &item);
            removeAtValue(l, item);
            break;
        case 8:
            printf("\nDigite o valor: ");
            scanf("%d", &item);
            seekValue(l, item);
            break;
        case 9:
            seekGraterValue(l);
            break;
        case 10:
            seekSmallerValue(l);
            break;
        case 11:
            printList(l);
            break;
        case 12:
            printf("\nSaindo...\n");
            break;
        default:
            printf("\nOpcao invalida\n");
            break;
        }

    } while (op != 12);

    return 0;
}