#include <stdio.h>
#include <stdlib.h>

// Constantes
#define MAX_CHAR 32
#define true 1
#define false 0

// Variáveis globais
int pos = 0;
char string[MAX_CHAR];
char lookahead;
int reg = 0; // Registrador atual

// Protótipos
int list();
int listR();
int digit();
int match(char c);
void nextToken();
void emit(char *op, int reg1, int reg2);

// Verifica se o próximo caractere na cadeia é o esperado
int match(char c) {
    if (lookahead == c) {
        nextToken();
        return true;
    }
    return false;
}

// Função que passa ao próximo símbolo da cadeia
void nextToken() {
    pos++;
    lookahead = string[pos];
}

// Emite uma instrução de operação
void emit(char *op, int reg1, int reg2) {
    printf("%s R%d, R%d\n", op, reg1, reg2);
}

// Função da regra de derivação 'list'
int list() {
    if (digit() != -1) {
        return listR();
    }
    return false;
}

// Função da regra de derivação 'listR'
int listR() {
    if (lookahead == '+') {
        match('+');
        int reg1 = reg - 1;
        int reg2 = digit();
        if (reg2 != -1) {
            emit("ADD", reg1, reg2);
            reg--;
            return listR();
        }
        return false;
    } else if (lookahead == '-') {
        match('-');
        int reg1 = reg - 1;
        int reg2 = digit();
        if (reg2 != -1) {
            emit("SUB", reg1, reg2);
            reg--;
            return listR();
        }
        return false;
    }
    return true;
}

// Função da regra de derivação 'digit'
int digit() {
    if (lookahead >= '0' && lookahead <= '9') {
        printf("MOV R%d, %c\n", reg, lookahead);
        int currentReg = reg;
        reg++;
        nextToken();
        return currentReg;
    }
    return -1;
}

int main() {
    // Exemplo de uso
    printf("Digite uma expressão: ");
    scanf("%s", string);
    lookahead = string[0];
    if (list() && lookahead == '\0') {
        printf("Expressão válida\n");
    } else {
        printf("Erro de sintaxe\n");
    }
    return 0;
}