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
 * @return int verdadeiro (1) se a análise foi bem-sucedida ou falso (0) caso contrário
 */
int program(void)
{
    if (!declarations())
        return false;
    // Se os comandos forem implementados, descomente e verifique:
    if (!statements())
        return false;
    return true;
}

/**
 * @brief Regra de derivacao para declaracoes
 * @return int verdadeiro (1) se todas as declaracoes foram processadas sem erro ou falso (0) caso contrário
 */
int declarations(void)
{
    while (is_variable_type(lookahead->tag))
    {
        if (!declaration())
            return false;
    }
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
 * @return int true/false
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
            return false;
        }

        ok1 = match(ID);        // Verifica se identificador vem a seguir
        ok2 = match(SEMICOLON); // Verifica se ; vem a seguir

        if (ok1 && ok2)
        {
            sym_declare(var_name, type_tag, 0, &global_symbol_table_variables);
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (lookahead->tag == ENDTOKEN)
    {
        // Verifica se fim de arquivo
        return false;
    }
    else
    {
        printf("[ERRO] Tipo desconhecido: %d %s.\n", lookahead->tag, lookahead->lexema);
        return false;
    }
}

/**
 * @brief Regra de derivacao para comandos
 * @return int verdadeiro (1) se os comandos foram processados sem erro ou falso (0) caso contrário
 */
int statements(void)
{
    while (statement())
        ;
    return true;
}

/**
 * @brief Regra de derivacao que processa um comando
 *
 * @return int true/false
 */
int statement(void)
{
    return false;
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

    // Chama a derivacao inicial e verifica se houve erros
    if (program())
    {
        printf("Compilação bem-sucedida.\n");
        printSTVariables(&global_symbol_table_variables); // Imprime tabela de simbolos

        strcpy(output_file_name, argv[1]);
        strcat(output_file_name, ".asm");
        output_file = fopen(output_file_name, "w+");
        gen_data_section(); // Gera codigo da secao de dados
        fclose(output_file);
        return EXIT_SUCCESS;
    }
    else
    {
        printf("Compilação falhou.\n");
        return EXIT_FAILURE;
    }
}