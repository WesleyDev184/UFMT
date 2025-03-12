/**
 * @file tst_lex.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Modulo exclusivo para teste do analisador lexico (isolado)
 * @version 0.2
 * @date 2021-12-10
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct_compiler.h"
#include "lex.h"

// Variaveis globais no modulo de teste
type_token *lookahead;
int pos;

// Funcao principal, para teste do lexico
int main(int argc, char *argv[])
{

    // Verifica a passagem de parametro
    if (argc != 2)
    {
        printf("[ERRO]\n\tÉ necessário informar um arquivo de entrada (código) como parâmetro.\n\n");
        exit(EXIT_FAILURE);
    }

    int acept;
    acept = false;

    initLex(argv[1]);
    lookahead = getToken();

    // Processa todos os tokens a partir da entrada
    while (lookahead->tag != ENDTOKEN)
    {
        printf("Tag:   %d\n", lookahead->tag);
        printf("Token: %s\n", lookahead->lexema);
        printf("Value: %i\n\n", lookahead->value);

        // Verifica se ocorreu erro
        if (lookahead->tag == ERROR)
            printf("--> [ERRO Lexico]\n\n");

        lookahead = getToken();
    }
    // Imprimindo o ultimo token obtido
    printf("Tag:   %d\n", lookahead->tag);
    printf("Token: %s\n", lookahead->lexema);

    return 1;
}