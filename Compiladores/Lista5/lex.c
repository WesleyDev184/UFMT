/**
 * @file lex.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador lexico
 * @version 0.3
 * @date 2021-12-09
 *
 */

// Inclusao do cabecalho
#include "lex.h"

// Definicao de variaveis globais
int pos;
FILE *input_file;

// Definicao e inicializacao de estrutura
type_token key_words[] = {
    {IF, "if", 0},
    {THEN, "then", 0},
    {ELSE, "else", 0},
    {WHILE, "while", 0},
    {DO, "do", 0},
    {NUM, "integer", 0},
    {READ, "read", 0},
    {WRITE, "write", 0},
    {FOR, "for", 0},
    {STRUCT, "struct", 0},
    {RETURN, "return", 0},
    {BREAK, "break", 0},
    {CONTINUE, "continue", 0},
    {SWITCH, "switch", 0},
    {CASE, "case", 0},
    {DEFAULT, "default", 0},
    {ENUM, "enum", 0},
    {SIZEOF, "sizeof", 0},
    {TYPEDEF, "typedef", 0},
    {INT, "int", 0},
    {FLOAT, "float", 0},
    {STRING, "string", 0},
    {CHAR, "char", 0},
    {BOOL, "bool", 0},
    {VOID, "void", 0},
};

// Definicao e inicializacao da tabela de caracteres especiais
type_token special_chars[] = {
    {PLUS, "+", 0},
    {MINUS, "-", 0},
    {MULT, "*", 0},
    {DIV, "/", 0},
    {OPEN_PAR, "(", 0},
    {CLOSE_PAR, ")", 0},
    {BRACKET_OPEN, "{", 0},
    {BRACKET_CLOSE, "}", 0},
    {EQUAL, "=", 0},
    {SEMICOLON, ";", 0},
    {COMMA, ",", 0},
    {ARROWLEFT, "<", 0},
    {ARROWRIGHT, ">", 0},
    {GE, ">=", 0},
    {LE, "<=", 0},
    {ENDTOKEN, "\0", 0}};

/**
 * @brief Processo de inicializacao do lexico. Recebe o arquivo de entrada
 * contendo codigo e carrega-o em memoria.
 *
 */
void initLex(char input_file_name[])
{
    input_file = fopen(input_file_name, "r");
    if (input_file == NULL)
    {
        printf("[ERRO]\n\tArquivo de entrada não encontrado: %s\n\n", input_file_name);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Analisa o proximo comando no código de entrada e retorna estrutura de
 * dados com Token correspondente (ponteiro).
 *
 * @return type_token*
 */

type_token *getToken()
{
    char buffer[MAX_CHAR];
    int pos_buffer;
    type_token *token;
    type_token *key_found;
    type_token *special_char_found;
    char ch;

    pos_buffer = 0;
    token = (type_token *)malloc(sizeof(type_token));
    strcpy(buffer, "");
    ch = fgetc(input_file);

    // Consome espacos, tabulacoes e quebras de linha
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
    {
        ch = fgetc(input_file);
    }

    // Verifica se NUMERO
    if (isdigit(ch))
    {
        // constroi buffer com os digitos
        while (isdigit(ch))
        {
            buffer[pos_buffer++] = ch;
            ch = fgetc(input_file);
        }
        ungetc(ch, input_file);
        buffer[pos_buffer] = '\0';
        token->tag = NUM;
        strcpy(token->lexema, buffer); // copia buffer para lexema
    } // Verifica se entrada eh um alfa-numerico (palavra reservada ou identificador)
    else if (isalpha(ch))
    {
        buffer[pos_buffer++] = ch;
        ch = fgetc(input_file);
        while (isalnum(ch))
        {
            buffer[pos_buffer++] = ch;
            ch = fgetc(input_file);
        }
        ungetc(ch, input_file);
        buffer[pos_buffer] = '\0';
        key_found = keyWordFind(buffer);
        if (key_found != NULL)
        { // Palavra reservada
            token->tag = key_found->tag;
            strcpy(token->lexema, key_found->lexema);
            token->value = key_found->value;
            // o token sera retornado no final da funcao
        }
        else
        { // Identificador
            token->tag = ID;
            strcpy(token->lexema, buffer);
            token->value = 0;
        }
    }
    else
    {
        buffer[pos_buffer++] = ch;
        ch = fgetc(input_file);
        if ((buffer[0] == '>' && ch == '=') || (buffer[0] == '<' && ch == '='))
        {
            buffer[pos_buffer++] = ch;
        }
        else
        {
            ungetc(ch, input_file);
        }
        buffer[pos_buffer] = '\0';
        special_char_found = specialCharFind(buffer);
        if (special_char_found != NULL)
        {
            token->tag = special_char_found->tag;
            strcpy(token->lexema, special_char_found->lexema);
            token->value = special_char_found->value;
        }
        else if (buffer[0] == EOF)
        {
            token->tag = ENDTOKEN;
            strcpy(token->lexema, "\0");
            printf("[INFO] Fim do arquivo\n");
        }
        else
        {
            token->tag = ERROR;
            strcpy(token->lexema, "");
            printf("[ERRO] Caractere não reconhecido: %s\n", buffer);
        }
    }

    return token;
}

/**
 * @brief Busca na lista de palavras reservadas o parâmetro informado, retornando
 * o respectivo token, ou nulo caso nao exista.
 *
 * @param char* palavra a ser verificada se corresponde a uma palavra reservada.
 * @return type_token* com o endereco de memoria do token correspondente, ou nulo.
 */
type_token *keyWordFind(char *word)
{
    int i;
    i = 0;

    while (key_words[i].lexema[0] != '\0')
    {
        if (strcmp(word, key_words[i].lexema) == 0)
            return &key_words[i];
        i++;
    }
    return NULL;
}

/**
 * @brief Busca na lista de simbolos o parâmetro informado, retornando
 * o respectivo token, ou nulo caso nao exista.
 *
 * @param char* simbolo a ser verificado se corresponde a um simbolo.
 * @return type_token* com o endereco de memoria do token correspondente, ou nulo.
 */
type_token *specialCharFind(char *symbol)
{
    int i;
    i = 0;

    while (special_chars[i].lexema[0] != '\0')
    {
        if (strcmp(symbol, special_chars[i].lexema) == 0)
            return &special_chars[i];
        i++;
    }
    return NULL;
}