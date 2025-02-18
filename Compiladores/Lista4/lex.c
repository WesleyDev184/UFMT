/**
 * @file lex.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador lexico
 * @version 0.1
 * @date 2021-11-24
 * 
 */

// Inclusao do cabecalho
#include "lex.h"

/**
 * @brief Processo de inicializacao do lexico. Tem funcao de receber o codigo
 *        de entrada.
 * 
 */
void initLex() {
    FILE *fp = fopen("in.txt", "r");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir o arquivo in.txt.\n");
        exit(EXIT_FAILURE);
    }

    size_t n = fread(string, sizeof(char), MAX_SIZE - 1, fp);
    string[n] = '\0'; // Garante terminação nula

    fclose(fp);
}

/**
 * @brief Analisa o proximo comando no código de entrada e retorna estrutura de
 * dados com Token correspondente (ponteiro).
 * 
 * @return type_token* 
 */
 type_token *getToken() {
    char buffer[MAX_CHAR];
    int pos_buffer = 0;
    type_token *token;

    token = (type_token*) malloc(sizeof(type_token));

    // Consome espaços
    while (isspace(string[pos])) {
        pos++;
    }

    // Verifica se NUMERO
    if (isdigit(string[pos])) {
        // Constrói buffer com os dígitos
        while (isdigit(string[pos])) {
            buffer[pos_buffer++] = string[pos++];
        }
        buffer[pos_buffer] = '\0';
        token->tag = NUM;
        strcpy(token->lexema, buffer); // Copia buffer para lexema
    } 
    else {
        // Para os demais tokens, use switch
        switch (string[pos]) {
            case PLUS:
                token->tag = PLUS;
                strcpy(token->lexema, "+");
                pos++;
                break;
            case MINUS:
                token->tag = MINUS;
                strcpy(token->lexema, "-");
                pos++;
                break;
            case MULT:
                token->tag = MULT;
                strcpy(token->lexema, "*");
                pos++;
                break;
            case DIV:
                token->tag = DIV;
                strcpy(token->lexema, "/");
                pos++;
                break;
            case ENDTOKEN:
                token->tag = ENDTOKEN;
                strcpy(token->lexema, "");
                break;
            default:
                token->tag = ERROR;
                strcpy(token->lexema, "");
                break;
        }
    }

    return token;
}