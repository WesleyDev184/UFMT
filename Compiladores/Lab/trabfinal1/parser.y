%{
    #include <string.h>
    #include <stdio.h>
	#include "symbolTable.h"
	#include "codeGeneration.h"

    void yyerror(char*);
    int yylex();

    extern SymTable table;

    char s_decs[256];

%}

%union {
	struct code_t
	{
		char str[2044]; // string para o codigo asm
		int op; // opcoes (por exemplo nos jumps)
	} c;
}

%type <c> programa declaracoes declaracao bloco
%type <c> declaracao_inteiro declaracao_float 
%type <c> comandos comando comando_atribuicao comando_io comando_condicional comando_repeticao
%type <c> expressao termo expressao_logica

%token <c> ID NUM FLOAT_NUM LITERAL_STR INT FLOAT WRITE READ IF ELSE WHILE EQ NE LE GE
%left '+' '-'
%left '*' '/' '%'
%left '<' '>' LE GE EQ NE
%right UMINUS


%%


programa: declaracoes bloco  {
		fprintf(out_file, "%s", $1.str);
		dumpCodeDeclarationEnd();
		fprintf(out_file, "%s", $2.str);
	}
;


declaracoes: declaracao declaracoes  {
		strcpy($$.str, $1.str);
		//printf("{%s}\n", $2.str);
		sprintf($$.str + strlen($$.str), "%s", $2.str);
	}

	| %empty { $$.str[0] = '\0'; }
;


declaracao: declaracao_inteiro { strcpy($$.str, $1.str); }
	| declaracao_float { strcpy($$.str, $1.str); }
;

declaracao_inteiro: INT ID ';'  {
		// Check if variable has already been declared
		if (findSymTable(&table, $2.str) != NULL) {
			fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
			YYABORT;
		}
		addSymTable(&table, $2.str, INTEGER, NULL);
		makeCodeDeclaration($$.str, $2.str, INTEGER, NULL);
	}
	| INT ID '=' NUM ';'  {
		// Check if variable has already been declared
		if (findSymTable(&table, $2.str) != NULL) {
			fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
			YYABORT;
		}
		addSymTable(&table, $2.str, INTEGER, $4.str);
		makeCodeDeclaration($$.str, $2.str, INTEGER, $4.str);
	}
;

declaracao_float: FLOAT ID ';'  {
		// Check if variable has already been declared
		if (findSymTable(&table, $2.str) != NULL) {
			fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
			YYABORT;
		}
		addSymTable(&table, $2.str, REAL, NULL);
		makeCodeDeclaration($$.str, $2.str, REAL, NULL);
	}
	| FLOAT ID '=' FLOAT_NUM ';'  {
		// Check if variable has already been declared
		if (findSymTable(&table, $2.str) != NULL) {
			fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
			YYABORT;
		}
		addSymTable(&table, $2.str, REAL, $4.str);
		makeCodeDeclaration($$.str, $2.str, REAL, $4.str);
	}
	| FLOAT ID '=' NUM ';'  {
		// Allow float initialization with integer
		if (findSymTable(&table, $2.str) != NULL) {
			fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
			YYABORT;
		}
		addSymTable(&table, $2.str, REAL, $4.str);
		makeCodeDeclaration($$.str, $2.str, REAL, $4.str);
	}
;


bloco : '{' comandos '}'  {
		strcpy($$.str, $2.str);
	}
;


comandos : comando comandos  {
		strcpy($$.str, $1.str);
		sprintf($$.str + strlen($$.str), "%s", $2.str);
	}
	| %empty { $$.str[0] = '\0'; }
;

comando: comando_atribuicao { strcpy($$.str, $1.str); }
	| comando_io { strcpy($$.str, $1.str); }
	| comando_condicional { strcpy($$.str, $1.str); }
	| comando_repeticao { strcpy($$.str, $1.str); }
;

comando_atribuicao: ID '=' expressao ';'  {
		// Check if variable was declared
		SymTableEntry* var = findSymTable(&table, $1.str);
		if (var == NULL) {
			fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1.str, cont_lines);
			YYABORT;
		}
		
		if (!makeCodeAssignment($$.str, $1.str, $3.str))
			YYABORT;
	}
;

comando_io: READ '(' ID ')' ';'  {
		// Check if variable was declared
		SymTableEntry* var = findSymTable(&table, $3.str);
		if (var == NULL) {
			fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $3.str, cont_lines);
			YYABORT;
		}
		makeCodeRead($$.str, $3.str, var->type);
	}
	| WRITE '(' expressao ')' ';'  {
		strcpy($$.str, $3.str);
		makeCodeWrite($$.str);
	}
	| WRITE '(' LITERAL_STR ')' ';'  {
		makeCodeWriteString($$.str, $3.str);
	}
;

comando_condicional: IF '(' expressao_logica ')' bloco  {
		makeCodeIf($$.str, $3.str, $5.str);
	}
	| IF '(' expressao_logica ')' bloco ELSE bloco  {
		makeCodeIfElse($$.str, $3.str, $5.str, $7.str);
	}
;

comando_repeticao: WHILE '(' expressao_logica ')' bloco  {
		makeCodeWhile($$.str, $3.str, $5.str);
	}
;


expressao: termo  {
		strcpy($$.str, $1.str);
	}
	| expressao '+' expressao  {
		strcpy($$.str, $1.str);
		makeCodeAdd($$.str, $3.str);
	}
	| expressao '-' expressao  {	
		strcpy($$.str, $1.str);
		makeCodeSub($$.str, $3.str);
	}
	| expressao '*' expressao  {	
		strcpy($$.str, $1.str);
		makeCodeMul($$.str, $3.str);
	}
	| expressao '/' expressao  {
		strcpy($$.str, $1.str);
		makeCodeDiv($$.str, $3.str);
	}
	| expressao '%' expressao  {
		strcpy($$.str, $1.str);
		makeCodeMod($$.str, $3.str);
	}
	| '-' expressao %prec UMINUS {
		strcpy($$.str, $2.str);
		makeCodeNeg($$.str);
	}
	| '(' expressao ')'  {
		strcpy($$.str, $2.str);
	}
;

termo: NUM  {
		makeCodeLoad($$.str, $1.str, 0);
	}
	| FLOAT_NUM  {
		makeCodeLoad($$.str, $1.str, 0);
	}
	| ID  {
		// Check if variable was declared before using
		if (findSymTable(&table, $1.str) == NULL) {
			fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1.str, cont_lines);
			YYABORT;
		}
		if (!makeCodeLoad($$.str, $1.str, 1))
			YYABORT;
	}
;


expressao_logica: expressao '<' expressao  {
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeComparison($$.str, "<");
	}
	| expressao '>' expressao  {
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeComparison($$.str, ">");
	}
	| expressao LE expressao  {
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeComparison($$.str, "<=");
	}
	| expressao GE expressao  {
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeComparison($$.str, ">=");
	}
	| expressao EQ expressao  {
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeComparison($$.str, "==");
	}
	| expressao NE expressao  {
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeComparison($$.str, "!=");
	}
	| '!' expressao_logica  {
		strcpy($$.str, $2.str);
		makeCodeNot($$.str);
	}
	| '(' expressao_logica ')'  {
		strcpy($$.str, $2.str);
	}
;


%%

void yyerror(char *s) {
   fprintf(stderr, "Error: %s at line %d", s, cont_lines);
   fprintf(stderr, "\n");
}
