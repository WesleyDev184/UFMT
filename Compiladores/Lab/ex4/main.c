#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE *yyin;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (!yyin)
    {
        fprintf(stderr, "Erro ao abrir arquivo: %s\n", argv[1]);
        return 1;
    }
    int ret = yyparse(); // chamada do analisador sintatico
    fclose(yyin);
    return ret;
}
