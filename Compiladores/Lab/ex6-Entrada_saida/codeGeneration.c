//Implementa CODEGENERATION.H

#include "codeGeneration.h"

// Codigo para declaracao de variaveis
void makeCodeDeclaration(char* dest, char* identifier, Type type, char* value)
{
    if (type == INTEGER)
    {
        if (value == NULL)
        	sprintf(dest, "%s: dq 0\n", identifier);

        else
        {
        	int x = atoi(value);
            sprintf(dest, "%s: dq %d\n", identifier, x);
        }
    }

    else if (type == REAL)
    {
    	if (value == NULL)
            sprintf(dest, "%s: dq 0\n", identifier);

        else
        {
          	double x = atof(value);
            sprintf(dest, "%s: dq %f\n", identifier, x);
        }
    }

    else if (type == STRING)
    {
    	if (value == NULL)
            sprintf(dest, "%s: times %d db 0 \n", identifier, STRING_SIZE);

        else
        {
            sprintf(dest, "%s: db %s, 0\n", identifier, value);
        }
    }
}


// Termino da secao de dados e comeco da secao de codigo
void dumpCodeDeclarationEnd()
{
    fprintf(out_file, "\nsection .text\n");
    fprintf(out_file, "global main\n");
    fprintf(out_file, "\nmain:\n");
}


// Codigo para leitura (scanf)
int makeCodeRead(char* dest, char *id)
{
    SymTableEntry* ret = findSymTable(&table,id);
    
    dest[0] = '\0';

    if (ret == NULL)
    {
        fprintf(stderr, "Error: %s not recognized at line %d\n", id, cont_lines);
        return 0;
    }

    if (ret->type == INTEGER)
    {
        sprintf(dest + strlen(dest), "mov rdi,fmt_d\n");
        sprintf(dest + strlen(dest), "mov rsi,%s\n", ret->identifier);
    }

    else if (ret->type == REAL)
    {
        sprintf(dest + strlen(dest), "mov rdi,fmt_f\n");
        sprintf(dest + strlen(dest), "mov rsi,%s\n", ret->identifier);
    }

    else
    {
        sprintf(dest + strlen(dest), "mov rdi,fmt_s\n");
        sprintf(dest + strlen(dest), "mov rsi,%s\n", ret->identifier);
    }

   
    sprintf(dest + strlen(dest), "mov rax,0\n");
    sprintf(dest + strlen(dest), "call scanf\n");

    return 1;

}


// Codigo para escrita (printf)
int makeCodeWrite(char* dest, char *id, int ln)
{
    SymTableEntry* ret = findSymTable(&table,id);
    
    dest[0] = '\0';

    if (ret == NULL)
    {
        fprintf(stderr, "Error: %s not recognized at line %d\n", id, cont_lines);
        return 0;
    }

    if (ret->type == INTEGER)
    {
        if (ln) sprintf(dest + strlen(dest), "mov rdi,fmt_dln\n");
        else sprintf(dest + strlen(dest), "mov rdi,fmt_d\n");
        sprintf(dest + strlen(dest), "mov rsi,[%s]\n", ret->identifier);
    }

    else if (ret->type == REAL)
    {
        if (ln) sprintf(dest + strlen(dest), "mov rdi,fmt_fln\n");
        else sprintf(dest + strlen(dest), "mov rdi,fmt_f\n");
        sprintf(dest + strlen(dest), "mov rsi,[%s]\n", ret->identifier);
    }

    else
    {
        if (ln) sprintf(dest + strlen(dest), "mov rdi,fmt_sln\n");
        else sprintf(dest + strlen(dest), "mov rdi,fmt_s\n");
        sprintf(dest + strlen(dest), "mov rsi,%s\n", ret->identifier);
    }

    sprintf(dest + strlen(dest), "mov rax,0\n");
    sprintf(dest + strlen(dest), "call printf\n");

    return 1;
}



int makeCodeAssignment(char* dest, char* id, char* expr)
{   
    SymTableEntry* ret = findSymTable(&table, id);
    dest[0] = '\0';

    if (ret == NULL)
    {
        fprintf(stderr, "Error: %s not recognized at line %d\n", id, cont_lines);
        return 0;
    }

 
    if (ret->type == INTEGER)
    {
        sprintf(dest + strlen(dest), "%s", expr);
        sprintf(dest + strlen(dest), "pop rbx\n");
        sprintf(dest + strlen(dest), "mov [%s],rbx\n", ret->identifier);
    }

    else
    {
        fprintf(stderr, "Unsuported operation envolving string or float at line %d\n",
            cont_lines);
        return 0;
    }

    return 1;
}





int makeCodeLoad(char* dest, char* id, int ref)
{
    dest[0] = '\0';

    if (ref == 0)
    {
        sprintf(dest + strlen(dest), "mov rbx,%s\n", id);
        sprintf(dest + strlen(dest), "push rbx\n");
        return 1;
    }

    SymTableEntry* ret = findSymTable(&table, id);

    if (ret == NULL)
    {
        fprintf(stderr, "Error: %s not recognized at line %d\n", id, cont_lines);
        return 0;
    }

    if (ret->type == STRING)
        sprintf(dest + strlen(dest), "mov rbx,%s\n", ret->identifier);
    else
        sprintf(dest + strlen(dest), "mov rbx,[%s]\n", ret->identifier);
    
    sprintf(dest + strlen(dest), "push rbx\n");
    return 1;
}


void makeCodeAdd(char* dest, char* value)
{
    sprintf(dest + strlen(dest), "%s", value);
    sprintf(dest + strlen(dest), "pop rcx\n");
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "add rbx,rcx\n");
    sprintf(dest + strlen(dest), "push rbx\n");
}


void makeCodeSub(char* dest, char* value)
{   
    sprintf(dest + strlen(dest), "%s", value);
    sprintf(dest + strlen(dest), "pop rcx\n");
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "sub rbx,rcx\n");
    sprintf(dest + strlen(dest), "push rbx\n");

}

void makeCodeMul(char* dest, char* value2)
{
    sprintf(dest + strlen(dest), "%s", value2);
    sprintf(dest + strlen(dest), "pop rcx\npop rbx\nimul rbx,rcx\npush rbx\n");
}


void makeCodeDiv(char* dest, char* value2)
{
    sprintf(dest + strlen(dest), "%s", value2);
    sprintf(dest + strlen(dest), "pop r8\n");
    sprintf(dest + strlen(dest), "pop rax\n");
    sprintf(dest + strlen(dest), "xor rdx,rdx\n");
    sprintf(dest + strlen(dest), "idiv r8\n");
    sprintf(dest + strlen(dest), "push rax\n");
}


void makeCodeMod(char* dest, char* value2)
{
    sprintf(dest + strlen(dest), "%s", value2);
    sprintf(dest + strlen(dest), "pop r8\n");
    sprintf(dest + strlen(dest), "pop rax\n");
    sprintf(dest + strlen(dest), "xor rdx,rdx\n");
    sprintf(dest + strlen(dest), "idiv r8\n");
    sprintf(dest + strlen(dest), "push rdx\n");
}