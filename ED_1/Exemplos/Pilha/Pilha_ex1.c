#include <stdio.h>

#define MAX 10

typedef struct stack
{
    int items[MAX];
    int top;
} Stack;

Stack *createStack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = 0;
    return s;
}

int isFull(Stack *s)
{
    if (s->top == MAX)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isEmpty(Stack *s)
{
    if (s->top == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(Stack *s, int item)
{
    if (isFull(s))
    {
        printf("\nPilha cheia\n");
    }
    else
    {
        s->items[s->top] = item;
        s->top++;
    }
}

void pop(Stack *s)
{
    if (isEmpty(s))
    {
        printf("\nPilha vazia");
    }
    else
    {
        s->top--;
    }
}

void printStack(Stack *s)
{
    if (isEmpty(s))
    {
        printf("\nPilha vazia");
    }
    else
    {
        for (int i = s->top - 1; i >= 0; i--)
        {
            printf("%d ", s->items[i]);
        }
        printf("\n");
    }
}

int main()
{
    Stack *s = createStack();
    int opcao, valor;

    do
    {
        printf("\n--- Pilha ---\n");
        printf(" 1 - Empilhar (push)\n");
        printf(" 2 - Desempilhar (pop)\n");
        printf(" 3 - Imprimir pilha\n");
        printf(" 4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            printf("Valor: ");
            scanf("%d", &valor);
            push(s, valor);
            break;
        case 2:
            pop(s);
            break;
        case 3:
            printStack(s);
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }

    } while (opcao != 4);

    return 0;
}