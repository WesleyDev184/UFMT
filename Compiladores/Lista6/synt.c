/**
 * @file synt.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador sintatico
 * @version 0.4
 * @date 2022-02-04
 *
 */

// Inclusao do cabecalho
#include "synt.h"

// Variaveis globais
type_token *lookahead;
extern type_symbol_table_variables global_symbol_table_variables;
extern type_symbol_table_string symbol_table_string;
extern char output_file_name[MAX_CHAR];
extern FILE *output_file;

/**
 * @brief Verifica se o proximo caracter (a frente) na cadeia eh o esperado
 *
 * @param token_tag (int) codigo do token a ser verificado
 * @return int true/false
 */
int match(int token_tag)
{
    if (lookahead->tag == token_tag)
    {
        lookahead = getToken(); // Pega o proximo token por meio do lexico
        return true;
    }
    printf("[ERRO] Entrada esperada: %s\n", lookahead->lexema);
    return false;
}

/**
 * @brief Regra de derivacao inicial
 */
int program(void)
{
    gen_preambule();

    if (declarations() == false)
    {
        gen_data_section();   // Chamada do gerador de codigo para declaracao de variaveis
        gen_preambule_code(); // Chamada do gerador de codigo para escrita do cabecalho da secao de codigo
    }
    else if (declarations() == ERROR)
    {
        printf("[ERRO] Falha ao processar as declarações.\n");
        return ERROR;
    }

    if (statements() == false)
    {
        gen_epilog_code();
    }
    else if (statements() == ERROR)
    {
        printf("[ERRO] Falha ao processar os comandos.\n");
        return ERROR;
    }
    return true;
}

/**
 * @brief Regra de derivacao para declaracoes
 * @return int verdadeiro (1) se as declaracoes foram processadas sem erro ou falso (0) caso contrário
 */
int declarations(void)
{
    while (true)
    {
        if (declaration() == false)
        {
            printf("[INFO] Fim de arquivo ou read, write.\n");
            return false;
            break;
        }
        else if (declaration() == ERROR)
        {
            return ERROR;
        }
    }; // Laco para processamento continuo das declaracoes
    return true;
}

/**
 * @brief Verifica se a tag é de um tipo de variável
 *
 * @param tag (int) código do token a ser verificado
 * @return int true/false
 */
int is_variable_type(int tag)
{
    return (tag == INT || tag == FLOAT || tag == STRING ||
            tag == CHAR || tag == BOOL);
}

/**
 * @brief Regra de derivacao declaracao
 * @return int verdadeiro (1) se a declaracao foi processada sem erro ou falso (0) caso contrário
 */
int declaration(void)
{
    type_symbol_table_entry *search_symbol;
    int ok1, ok2;
    char var_name[MAX_CHAR];

    // Verifica se a tag é de um tipo de variável
    if (is_variable_type(lookahead->tag))
    {
        int type_tag = lookahead->tag; // Armazena o tipo da variável
        match(lookahead->tag);
        strcpy(var_name, lookahead->lexema);
        search_symbol = sym_find(var_name, &global_symbol_table_variables);

        if (search_symbol != NULL)
        {
            printf("[ERRO] Variável '%s' já declarada.\n", var_name);
            return ERROR;
        }

        ok1 = match(ID); // Verifica se identificador vem a seguir
        if (!ok1)
        {
            printf("[ERRO] Identificador esperado após o tipo da variável.\n");
            return ERROR;
        }

        ok2 = match(SEMICOLON); // Verifica se ; vem a seguir
        if (!ok2)
        {
            printf("[ERRO] ';' esperado após o identificador da variável.\n");
            return ERROR;
        }

        if (ok1 && ok2)
        {
            if (!sym_declare(var_name, type_tag, 0, &global_symbol_table_variables))
            {
                printf("[ERRO] Falha ao registrar a variável '%s' na tabela de símbolos.\n", var_name);
                return ERROR;
            }
            return true;
        }
        else
        {
            printf("[ERRO] Falha ao processar a declaração.\n");
            return ERROR;
        }
    }
    else if (lookahead->tag == ENDTOKEN ||
             lookahead->tag == READ ||
             lookahead->tag == WRITE)
    {
        return false;
    }
    else
    {
        printf("[ERRO] Tipo desconhecido: %d %s.\n", lookahead->tag, lookahead->lexema);
        return ERROR;
    }
}

/**
 * @brief Regra de derivacao para comandos
 * @return int verdadeiro (1) se os comandos foram processados sem erro ou falso (0) caso contrário
 */
int statements(void)
{
    while (true)
    {
        if (statement() == false)
        {
            printf("[INFO] Fim de arquivo.\n");
            return false;
            break;
        }
        else if (statement() == ERROR)
        {
            return ERROR;
        }
    };
    return true;
}

/**
 * @brief Regra de derivacao que processa um comando
 *
 * @return int true/false
 */
int statement(void)
{
    char lexeme_of_id[MAX_CHAR];
    type_symbol_table_entry *search_symbol;

    if (lookahead->tag == READ)
    {
        match(READ);
        strcpy(lexeme_of_id, lookahead->lexema);
        match(ID);
        search_symbol = sym_find(lexeme_of_id, &global_symbol_table_variables);
        if (search_symbol == NULL)
        {
            printf("[ERRO] Variável '%s' não declarada.\n", lexeme_of_id);
            return ERROR;
        }
        gen_read(lexeme_of_id);
        match(SEMICOLON);
        return true;
    }
    else if (lookahead->tag == WRITE)
    {
        match(WRITE);
        strcpy(lexeme_of_id, lookahead->lexema);
        match(ID);
        search_symbol = sym_find(lexeme_of_id, &global_symbol_table_variables);
        if (search_symbol == NULL)
        {
            printf("[ERRO] Variável '%s' não declarada.\n", lexeme_of_id);
            return ERROR;
        }
        gen_write(lexeme_of_id);
        match(SEMICOLON);
        return true;
    }
    else if (lookahead->tag == ENDTOKEN)
    {
        return false;
    }
    else
    {
        printf("[ERRO] Comando desconhecido.\n");
        return ERROR;
    }
}

//--------------------- MAIN -----------------------

/**
 * @brief Funcao principal (main) do compilador
 *
 * @return int
 */
int main(int argc, char *argv[])
{

    // Inicializa a tabela de simbolo global
    initSymbolTableVariables(&global_symbol_table_variables);
    initSymbolTableString();

    // Verifica a passagem de parametro
    if (argc != 2)
    {
        printf("[ERRO]\n\tÉ necessário informar um arquivo de entrada (código) como parâmetro.\n\n");
        exit(EXIT_FAILURE);
    }

    initLex(argv[1]);       // Carrega codigo
    lookahead = getToken(); // Inicializacao do lookahead

    // Abre o arquivo de saida
    strcpy(output_file_name, argv[1]);
    strcat(output_file_name, ".asm");
    output_file = fopen(output_file_name, "w+");

    if (program())
    {
        printf("Compilação bem-sucedida.\n");
    }
    else if (program() == ERROR)
    {
        printf("Compilação falhou.\n");
    }

    fclose(output_file);
    return 1;
}