/**
 * @file gen.c
 * @author Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo gerador de codigo
 * @version 0.2
 * @date 2022-02-23
 *
 */

// Inclusao do cabecalho
#include "gen.h"

// Inclusao explicita de variaveis globais de outro contexto (symbols.h)
extern type_symbol_table_variables global_symbol_table_variables;
extern type_symbol_table_string symbol_table_string;
char output_file_name[MAX_CHAR];
FILE *output_file;

/**
 * @brief Funcao que gera codigo de montagem para SOMA
 *
 */
void genAdd()
{
    printf("pop rax\n");
    printf("pop rbx\n");
    printf("add rax,rbx\n");
    printf("push rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para SUBTRACAO
 *
 */
void genSub()
{
    printf("pop rbx\n");
    printf("pop rax\n");
    printf("sub rax,rbx\n");
    printf("push rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para MULTIPLICACAO
 *
 */
void genMult()
{
    printf("pop rax\n");
    printf("pop rbx\n");
    printf("imult rax,rbx\n");
    printf("push rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para DIVISAO
 *
 */
void genDiv()
{
    printf("pop rbx\n");
    printf("pop rax\n");
    printf("idiv rax,rbx\n");
    printf("push rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para armazenamento de NUMERAL
 *
 * @param num_string
 */
void genNum(char num_string[MAX_TOKEN])
{
    printf("mov rax,%s\n", num_string);
    printf("push rax\n");
}

/**
 * @brief Funcao que gera um preambulo que permite o uso das funcoes do C (scanf e printf)
 *
 */
void gen_preambule(void) {
    fprintf(output_file, "; UFMT-Compiladores\n");
    fprintf(output_file, "; Prof. Ivairton\n");
    fprintf(output_file, "; Procedimento para geracao do executavel apos compilacao (em Linux 64):\n");
    fprintf(output_file, "; (1) compilacao do Assembly com nasm: $ nasm -f elf64 <nome_do_arquivo>\n");
    fprintf(output_file, "; (2) likedicao: $ ld -e main -melf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc <nome_arquivo_objeto> -o <arquivo_executavel>\n\n");
    fprintf(output_file, "extern printf\n");
    fprintf(output_file, "extern scanf\n");
    fprintf(output_file, "extern exit\n");
}

/**
 * @brief Funcao que gera codigo da secao de dados (declaracao de variaveis).
 */
void gen_data_section(void)
{
    int i, n;

    fprintf(output_file, "\nsection .data\n");

    // emite strings de formato fixo
    fprintf(output_file, "fmt_i_int db \"%%d\", 0\n");
    fprintf(output_file, "fmt_o_int db \"%%d\", 10, 0\n");
    fprintf(output_file, "fmt_i_float db \"%%f\", 0\n");
    fprintf(output_file, "fmt_o_float db \"%%f\", 10, 0\n");

    // processa cada simbolo da tabela e gera um ponteiro para cada variavel na memoria
    n = global_symbol_table_variables.n_variables;
    for (i = 0; i < n; i++)
    {
        switch (global_symbol_table_variables.variable[i].type)
        {
        case STRING:
            fprintf(output_file, "%s: db \"                \" \n", global_symbol_table_variables.variable[i].name);
            break;
        case CHAR:
            fprintf(output_file, "%s: db 0\n", global_symbol_table_variables.variable[i].name);
            break;
        default:
            break;
        }
    }

    n = symbol_table_string.n_strings;
    for (i = 0; i < n; i++)
    {
        fprintf(output_file, "%s: db %s\n", symbol_table_string.string[i].name, symbol_table_string.string[i].value);
    }

    fprintf(output_file, "\nsection .bss\n");
    n = global_symbol_table_variables.n_variables;
    for (i = 0; i < n; i++)
    {
        switch (global_symbol_table_variables.variable[i].type)
        {
        case INT:
            fprintf(output_file, "%s resd 1\n", global_symbol_table_variables.variable[i].name);
            break;
        case FLOAT:
            fprintf(output_file, "%s resd 1\n", global_symbol_table_variables.variable[i].name);
            break;
        case BOOL:
            fprintf(output_file, "%s resd 1\n", global_symbol_table_variables.variable[i].name);
            break;
        default:
            break;
        }
    }
}   

/**
 * @brief Funcao que gera a marcacao do inicio da secao de codigo
 *
 */
void gen_preambule_code(void) {
    // Secao .text
    fprintf(output_file, "\nsection .text\n");
    fprintf(output_file, "\tglobal main,_start\n");
    fprintf(output_file, "main:\n");
    fprintf(output_file, "_start:\n");
}

/**
 * @brief Funcao que encerra o codigo inserindo comandos de fechamento
 * 
 */
void gen_epilog_code(void) {
    // Encerramento do programa, com retorno zero
    fprintf(output_file, "\n;encerra programa\n");
    fprintf(output_file, "\tmov ebx,0\n");
    fprintf(output_file, "\tmov eax,1\n");
    fprintf(output_file, "\tint 0x80\n");

    // Secao exit, util para tratamento de erro
    fprintf(output_file, "\n;Label para chamada do exit/encerra programa\n");
    fprintf(output_file, "exit:\n");
    fprintf(output_file, "\tmov rdi, 0;\n");
    fprintf(output_file, "\tcall exit\n");
}

/**
 * @brief Gera codigo para o comando READ
 *
 * @param lexeme_of_id nome do identificador
 */
void gen_read(char *lexeme_of_id)
{
    fprintf(output_file, "\n;le valor inteiro\n");
    fprintf(output_file, "  mov rdi, fmt_i_int\n");
    fprintf(output_file, "  lea rsi, [%s]\n", lexeme_of_id);
    fprintf(output_file, "  xor eax, eax\n");
    fprintf(output_file, "  call scanf\n");
}

/**
 * @brief Gera codigo para o comando WRITE
 *
 * @param lexeme_of_id nome do identificador
 */
void gen_write(char *lexeme_of_id)
{
    fprintf(output_file, "\n;escreve valor inteiro\n");
    fprintf(output_file, "  mov rdi, fmt_o_int\n");
    fprintf(output_file, "  mov esi, [%s]\n", lexeme_of_id);
    fprintf(output_file, "  xor eax, eax\n");
    fprintf(output_file, "  call printf\n");
}