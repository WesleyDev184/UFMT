#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define MAX_CHAR 32
#define true 1
#define false 0
#define ERROR -1

// Regras e simbolos da gramatica
#define E 0
#define ER 1
#define T 2
#define TR 3
#define F 4
// Terminais:
#define id 0
#define sum 1
#define mult 2
#define o_par 3
#define c_par 4
#define end 5
#define empty 6

// Definicao de tipos
// String
typedef struct t_arr_int
{
    int ruler[MAX_CHAR];
} typeArrayInt;

// Stack
typedef struct t_stck
{
    int stack[MAX_CHAR];
    int count;
} typeStack;

// Variaveis globais
int pos = 0;
char string[MAX_CHAR];
char lookahead;
typeArrayInt TAS[5][6] = {
    {{T, ER}, {ERROR}, {ERROR}, {T, ER}, {ERROR}, {ERROR}},
    {{ERROR}, {sum, T, ER}, {ERROR}, {ERROR}, {empty}, {empty}},
    {{F, TR}, {ERROR}, {ERROR}, {F, TR}, {ERROR}, {ERROR}},
    {{ERROR}, {empty}, {mult, F, TR}, {ERROR}, {empty}, {empty}},
    {{id}, {ERROR}, {ERROR}, {o_par, E, c_par}, {ERROR}, {ERROR}}};
typeStack stack;

// Prototipos
int push(int);
int pop();
int driver();
int digit();
int match(char c);
void nextToken();
int terminal(int);
int getTerminal(char c);

// Manipulacao da pilha
int push(int value)
{
    if (stack.count < MAX_CHAR)
    {
        stack.stack[stack.count++] = value;
        return true;
    }
    return ERROR;
}

int pop()
{
    if (stack.count > 0)
    {
        return stack.stack[--stack.count];
    }
    return ERROR;
}

int terminal(int c)
{
    if (c == id || c == sum || c == mult || c == o_par || c == c_par || c == end || c == empty)
    {
        return true;
    }
    return false;
}

int getTerminal(char c)
{
    if (c >= '0' && c <= '9')
        return id;
    if (c == '+')
        return sum;
    if (c == '*')
        return mult;
    if (c == '(')
        return o_par;
    if (c == ')')
        return c_par;
    if (c == '\0')
        return end;
    return ERROR;
}

int match(char c)
{
    if (lookahead == c)
    {
        nextToken();
        return true;
    }
    return false;
}

// Funcao que passa ao proximo simbolo da cadeia
void nextToken()
{
    pos++;
    lookahead = string[pos];
}

// Funcao da regra de derivacao 'digit''
int digit()
{
    char ch;
    ch = lookahead;
    if (
        match('0') || match('1') ||
        match('2') || match('3') ||
        match('4') || match('5') ||
        match('6') || match('7') ||
        match('8') || match('9'))
    {
        // Adicao de comando para geracao de codigo:
        //...
        return true;
    }
    return false;
}

int driver()
{
    stack.count = 0;
    push(end);
    push(E);

    lookahead = string[pos];

    while (stack.count > 0)
    {
        printf("lookahead: %c\n", lookahead);
        int X = pop();
        printf("X: %d\n", X);
        int a = getTerminal(lookahead);
        printf("a: %d\n", a);

        if (terminal(X))
        {
            if (X == a)
            {
                match(lookahead);
            }
            else
            {
                printf("Erro sintático: símbolo inesperado '%c'\n", lookahead);
                return 0;
            }
        }
        else
        {
            typeArrayInt rule = TAS[X][a];

            if (rule.ruler[0] != ERROR)
            {
                for (int i = MAX_CHAR - 1; i >= 0; i--)
                {
                    if (rule.ruler[i] != empty)
                    {
                        push(rule.ruler[i]);
                    }
                }
            }
            else
            {
                printf("Erro sintático: símbolo inesperado '%c'\n", lookahead);
                return 0;
            }
        }
    }

    if (lookahead == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Funcao principal
int main()
{
    stack.count = 0; // Inicializacao do contador da pilha
    push(end);
    push(E);

    int acept = false;

    // printf("Informe uma cadeia:\n");
    // scanf("%s", string); //leitura da cadeia
    strcpy(string, "2+3");

    lookahead = string[0]; // inicializacao do lookahead

    acept = driver(); // Chamada da derivacao/funcao inicial da gramatica
    printf("lookahead: %c\n", lookahead);

    if (acept)
    {
        printf("Cadeia PERTENCENTE a linguagem!\n");
    }
    else
    {
        printf("Cadeia NAO pertencente a linguagem.\n");
    }

    return 1;
}