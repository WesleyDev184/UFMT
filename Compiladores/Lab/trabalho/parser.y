%{
    #define _GNU_SOURCE
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
	#include "symbolTable.h"
	#include "codeGeneration.h"

    void yyerror(char*);
    int yylex();
    Parameter* parseParameterString(char* paramStr, int* paramCount);
    
    // Helper function for safe string concatenation
    static void safe_concat(char *dest, size_t dest_size, const char *src1, const char *src2) {
        int ret = snprintf(dest, dest_size, "%s%s", src1, src2);
        if (ret >= (int)dest_size) {
            fprintf(stderr, "Warning: String concatenation truncated\n");
        }
    }

    extern SymTable table;
    extern FunctionTable functionTable;
    extern ScopedSymTable scopedTable;
    extern int cont_lines;

    char s_decs[256];

%}

%union {
	struct code_t
	{
		char str[32768]; // string para o codigo asm (increased to 32KB)
		int op; // opcoes (por exemplo nos jumps)
		int type; // type information for expressions (using int instead of Type enum)
	} c;
}

%type <c> programa declaracoes_e_funcoes item_declaracao declaracao bloco lista_instrucoes instrucao
%type <c> declaracao_inteiro declaracao_float declaracao_char declaracao_bool declaracao_string
%type <c> prototipo_funcao implementacao_funcao
%type <c> lista_parametros parametro
%type <c> chamada_funcao
%type <c> comando comando_atribuicao comando_io comando_condicional comando_repeticao comando_retorno
%type <c> expressao termo expressao_logica lista_expressoes

%token <c> ID NUM FLOAT_NUM LITERAL_STR CHAR_LITERAL TRUE_VAL FALSE_VAL
%token <c> INT_TYPE FLOAT_TYPE CHAR_TYPE BOOL_TYPE STRING_TYPE WRITE READ IF ELSE WHILE EQ NE LE GE RETURN AND OR
%left OR
%left AND
%right '!'
%left '<' '>' LE GE EQ NE
%left '+' '-'
%left '*' '/' '%'
%right UMINUS
%right '=' 
%left ';'
%nonassoc THEN
%nonassoc ELSE


%%


programa: declaracoes_e_funcoes  {
		// Check if main function was defined
		FunctionEntry *mainFunc = findFunction(&functionTable, "main");
		if (mainFunc == NULL || !mainFunc->isDefined) {
			fprintf(stderr, "Error: Main function must be defined\n");
			YYABORT;
		}
		
		// Write declarations and functions
		dumpCodeDeclarationEnd();
		fprintf(out_file, "%s", $1.str);  // Write all content
	}
;


declaracoes_e_funcoes: item_declaracao declaracoes_e_funcoes  {
		strcpy($$.str, $1.str);
		sprintf($$.str + strlen($$.str), "%s", $2.str);
	}

	| %empty { $$.str[0] = '\0'; }
;

item_declaracao: declaracao { strcpy($$.str, $1.str); }
	| prototipo_funcao { strcpy($$.str, $1.str); }
	| implementacao_funcao { strcpy($$.str, $1.str); }
;


declaracao: declaracao_inteiro { strcpy($$.str, $1.str); }
	| declaracao_float { strcpy($$.str, $1.str); }
	| declaracao_char { strcpy($$.str, $1.str); }
	| declaracao_bool { strcpy($$.str, $1.str); }
	| declaracao_string { strcpy($$.str, $1.str); }
;

declaracao_inteiro: INT_TYPE ID ';'  {
		// Check current scope level to determine which table to use
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, INTEGER, NULL);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, INTEGER, NULL, 0);
		}
		makeCodeDeclaration($$.str, $2.str, INTEGER, NULL);
	}
	| INT_TYPE ID '=' NUM ';'  {
		// Check current scope level to determine which table to use
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, INTEGER, $4.str);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, INTEGER, $4.str, 0);
		}
		makeCodeDeclaration($$.str, $2.str, INTEGER, $4.str);
	}
	| INT_TYPE ID '=' expressao ';'  {
		// Declaration with expression initialization
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, INTEGER, NULL);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, INTEGER, NULL, 0);
		}
		
		// Generate code: declaration + assignment
		char tempDecl[32768];
		makeCodeDeclaration(tempDecl, $2.str, INTEGER, NULL);
		
		char tempAssign[32768];
		if (!makeCodeAssignment(tempAssign, $2.str, $4.str)) {
			YYABORT;
		}
		
		safe_concat($$.str, sizeof($$.str), tempDecl, tempAssign);
	}
;

declaracao_float: FLOAT_TYPE ID ';'  {
		// Check current scope level to determine which table to use
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, FLOAT, NULL);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, FLOAT, NULL, 0);
		}
		makeCodeDeclaration($$.str, $2.str, FLOAT, NULL);
	}
	| FLOAT_TYPE ID '=' FLOAT_NUM ';'  {
		// Check current scope level to determine which table to use
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, FLOAT, $4.str);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, FLOAT, $4.str, 0);
		}
		makeCodeDeclaration($$.str, $2.str, FLOAT, $4.str);
	}
	| FLOAT_TYPE ID '=' NUM ';'  {
		// Allow float initialization with integer
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, FLOAT, $4.str);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, FLOAT, $4.str, 0);
		}
		makeCodeDeclaration($$.str, $2.str, FLOAT, $4.str);
	}
	| FLOAT_TYPE ID '=' expressao ';'  {
		// Float declaration with expression initialization
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, FLOAT, NULL);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, FLOAT, NULL, 0);
		}
		
		// Generate code: declaration + assignment
		char tempDecl[32768];
		makeCodeDeclaration(tempDecl, $2.str, FLOAT, NULL);
		
		char tempAssign[32768];
		if (!makeCodeAssignment(tempAssign, $2.str, $4.str)) {
			YYABORT;
		}
		
		safe_concat($$.str, sizeof($$.str), tempDecl, tempAssign);
	}
;

declaracao_char: CHAR_TYPE ID ';'  {
		// Check current scope level to determine which table to use
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, CHAR, NULL);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, CHAR, NULL, 0);
		}
		makeCodeDeclaration($$.str, $2.str, CHAR, NULL);
	}
	| CHAR_TYPE ID '=' CHAR_LITERAL ';'  {
		// Check current scope level to determine which table to use
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, CHAR, $4.str);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, CHAR, $4.str, 0);
		}
		makeCodeDeclaration($$.str, $2.str, CHAR, $4.str);
	}
	| CHAR_TYPE ID '=' expressao ';'  {
		// Char declaration with expression initialization
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, CHAR, NULL);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, CHAR, NULL, 0);
		}
		
		// Generate code: declaration + assignment
		char tempDecl[32768];
		makeCodeDeclaration(tempDecl, $2.str, CHAR, NULL);
		
		char tempAssign[32768];
		if (!makeCodeAssignment(tempAssign, $2.str, $4.str)) {
			YYABORT;
		}
		
		safe_concat($$.str, sizeof($$.str), tempDecl, tempAssign);
	}
;

declaracao_bool: BOOL_TYPE ID ';'  {
		// Check current scope level to determine which table to use
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, BOOL, NULL);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, BOOL, NULL, 0);
		}
		makeCodeDeclaration($$.str, $2.str, BOOL, NULL);
	}
	| BOOL_TYPE ID '=' TRUE_VAL ';'  {
		// Check current scope level to determine which table to use
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, BOOL, $4.str);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, BOOL, $4.str, 0);
		}
		makeCodeDeclaration($$.str, $2.str, BOOL, $4.str);
	}
	| BOOL_TYPE ID '=' FALSE_VAL ';'  {
		// Check current scope level to determine which table to use
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, BOOL, $4.str);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, BOOL, $4.str, 0);
		}
		makeCodeDeclaration($$.str, $2.str, BOOL, $4.str);
	}
	| BOOL_TYPE ID '=' expressao ';'  {
		// Bool declaration with expression initialization
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, BOOL, NULL);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, BOOL, NULL, 0);
		}
		
		// Generate code: declaration + assignment
		char tempDecl[32768];
		makeCodeDeclaration(tempDecl, $2.str, BOOL, NULL);
		
		char tempAssign[32768];
		if (!makeCodeAssignment(tempAssign, $2.str, $4.str)) {
			YYABORT;
		}
		
		safe_concat($$.str, sizeof($$.str), tempDecl, tempAssign);
	}
;

declaracao_string: STRING_TYPE ID ';'  {
		// Check current scope level to determine which table to use
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, STRING, NULL);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, STRING, NULL, 0);
		}
		makeCodeDeclaration($$.str, $2.str, STRING, NULL);
	}
	| STRING_TYPE ID '=' LITERAL_STR ';'  {
		// Check current scope level to determine which table to use
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, STRING, $4.str);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, STRING, $4.str, 0);
		}
		makeCodeDeclaration($$.str, $2.str, STRING, $4.str);
	}
	| STRING_TYPE ID '=' expressao ';'  {
		// String declaration with expression initialization
		int currentLevel = getCurrentScopeLevel(&scopedTable);
		
		if (currentLevel == 0) {
			// Global scope - add to global table only
			if (findSymTable(&table, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addSymTable(&table, $2.str, STRING, NULL);
		} else {
			// Local scope - add to scoped table only
			if (findSymbolInCurrentScope(&scopedTable, $2.str) != NULL) {
				fprintf(stderr, "Error: Variable '%s' already declared in current scope at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			addScopedSymbol(&scopedTable, $2.str, STRING, NULL, 0);
		}
		
		// Generate code: declaration + assignment
		char tempDecl[32768];
		makeCodeDeclaration(tempDecl, $2.str, STRING, NULL);
		
		char tempAssign[32768];
		if (!makeCodeAssignment(tempAssign, $2.str, $4.str)) {
			YYABORT;
		}
		
		safe_concat($$.str, sizeof($$.str), tempDecl, tempAssign);
	}
;


prototipo_funcao: INT_TYPE ID '(' ')' ';' {
		// Process function prototype without parameters
		if (!addFunctionPrototype(&functionTable, $2.str, INTEGER, NULL, 0, 0)) {
			fprintf(stderr, "Error: Function '%s' already declared at line %d\n", $2.str, cont_lines);
			YYABORT;
		}
		$$.str[0] = '\0'; // No code generation for prototypes
	}
	| INT_TYPE ID '(' lista_parametros ')' ';' {
		// Process function prototype with parameters
		int paramCount = 0;
		Parameter *params = parseParameterString($4.str, &paramCount);
		
		if (!addFunctionPrototype(&functionTable, $2.str, INTEGER, params, paramCount, 0)) {
			fprintf(stderr, "Error: Function '%s' already declared at line %d\n", $2.str, cont_lines);
			freeParameters(params);
			YYABORT;
		}
		$$.str[0] = '\0'; // No code generation for prototypes
	}
	| FLOAT_TYPE ID '(' ')' ';' {
		// Process float function prototype without parameters
		if (!addFunctionPrototype(&functionTable, $2.str, FLOAT, NULL, 0, 0)) {
			fprintf(stderr, "Error: Function '%s' already declared at line %d\n", $2.str, cont_lines);
			YYABORT;
		}
		$$.str[0] = '\0'; // No code generation for prototypes
	}
	| FLOAT_TYPE ID '(' lista_parametros ')' ';' {
		// Process float function prototype with parameters
		int paramCount = 0;
		Parameter *params = parseParameterString($4.str, &paramCount);
		
		if (!addFunctionPrototype(&functionTable, $2.str, FLOAT, params, paramCount, 0)) {
			fprintf(stderr, "Error: Function '%s' already declared at line %d\n", $2.str, cont_lines);
			freeParameters(params);
			YYABORT;
		}
		$$.str[0] = '\0'; // No code generation for prototypes
	}
	| CHAR_TYPE ID '(' ')' ';' {
		// Process char function prototype without parameters
		if (!addFunctionPrototype(&functionTable, $2.str, CHAR, NULL, 0, 0)) {
			fprintf(stderr, "Error: Function '%s' already declared at line %d\n", $2.str, cont_lines);
			YYABORT;
		}
		$$.str[0] = '\0'; // No code generation for prototypes
	}
	| CHAR_TYPE ID '(' lista_parametros ')' ';' {
		// Process char function prototype with parameters
		int paramCount = 0;
		Parameter *params = parseParameterString($4.str, &paramCount);
		
		if (!addFunctionPrototype(&functionTable, $2.str, CHAR, params, paramCount, 0)) {
			fprintf(stderr, "Error: Function '%s' already declared at line %d\n", $2.str, cont_lines);
			freeParameters(params);
			YYABORT;
		}
		$$.str[0] = '\0'; // No code generation for prototypes
	}
	| BOOL_TYPE ID '(' ')' ';' {
		// Process bool function prototype without parameters
		if (!addFunctionPrototype(&functionTable, $2.str, BOOL, NULL, 0, 0)) {
			fprintf(stderr, "Error: Function '%s' already declared at line %d\n", $2.str, cont_lines);
			YYABORT;
		}
		$$.str[0] = '\0'; // No code generation for prototypes
	}
	| BOOL_TYPE ID '(' lista_parametros ')' ';' {
		// Process bool function prototype with parameters
		int paramCount = 0;
		Parameter *params = parseParameterString($4.str, &paramCount);
		
		if (!addFunctionPrototype(&functionTable, $2.str, BOOL, params, paramCount, 0)) {
			fprintf(stderr, "Error: Function '%s' already declared at line %d\n", $2.str, cont_lines);
			freeParameters(params);
			YYABORT;
		}
		$$.str[0] = '\0'; // No code generation for prototypes
	}
	| STRING_TYPE ID '(' ')' ';' {
		// Process string function prototype without parameters
		if (!addFunctionPrototype(&functionTable, $2.str, STRING, NULL, 0, 0)) {
			fprintf(stderr, "Error: Function '%s' already declared at line %d\n", $2.str, cont_lines);
			YYABORT;
		}
		$$.str[0] = '\0'; // No code generation for prototypes
	}
	| STRING_TYPE ID '(' lista_parametros ')' ';' {
		// Process string function prototype with parameters
		int paramCount = 0;
		Parameter *params = parseParameterString($4.str, &paramCount);
		
		if (!addFunctionPrototype(&functionTable, $2.str, STRING, params, paramCount, 0)) {
			fprintf(stderr, "Error: Function '%s' already declared at line %d\n", $2.str, cont_lines);
			freeParameters(params);
			YYABORT;
		}
		$$.str[0] = '\0'; // No code generation for prototypes
	}
;

implementacao_funcao: INT_TYPE ID '(' ')' {
		// Enter function scope before processing body
		if (!enterScope(&scopedTable, SCOPE_FUNCTION, $2.str)) {
			fprintf(stderr, "Error: Failed to enter function scope at line %d\n", cont_lines);
			YYABORT;
		}
	} bloco {
		// Exit function scope after processing body
		if (!exitScope(&scopedTable)) {
			fprintf(stderr, "Error: Failed to exit function scope at line %d\n", cont_lines);
			YYABORT;
		}
		
		// Special case for main function
		if (strcmp($2.str, "main") == 0) {
			// This is a main function - treat it specially
			if (!addFunctionPrototype(&functionTable, "main", INTEGER, NULL, 0, 1)) {
				fprintf(stderr, "Error: Main function already declared at line %d\n", cont_lines);
				YYABORT;
			}
			markFunctionDefined(&functionTable, "main");
			makeCodeMain($$.str, $6.str);
		} else {
			// Regular function logic
			FunctionEntry *func = findFunction(&functionTable, $2.str);
			if (func != NULL) {
				if (func->isDefined) {
					fprintf(stderr, "Error: Function '%s' already defined at line %d\n", $2.str, cont_lines);
					YYABORT;
				}
				// Check signature compatibility here
				markFunctionDefined(&functionTable, $2.str);
			} else {
				// Add as new function if not prototyped
				if (!addFunctionPrototype(&functionTable, $2.str, INTEGER, NULL, 0, 0)) {
					YYABORT;
				}
				markFunctionDefined(&functionTable, $2.str);
			}
			makeCodeFunction($$.str, $2.str, INTEGER, $6.str);
		}
	}
	| INT_TYPE ID '(' lista_parametros ')' {
		// Enter function scope and add parameters
		if (!enterScope(&scopedTable, SCOPE_FUNCTION, $2.str)) {
			fprintf(stderr, "Error: Failed to enter function scope at line %d\n", cont_lines);
			YYABORT;
		}
		
		// Add parameters to function scope
		int paramCount = 0;
		Parameter *params = parseParameterString($4.str, &paramCount);
		if (!addFunctionParameters(&scopedTable, params)) {
			fprintf(stderr, "Error: Failed to add function parameters at line %d\n", cont_lines);
			freeParameters(params);
			YYABORT;
		}
		freeParameters(params);
	} bloco {
		// Exit function scope after processing body
		if (!exitScope(&scopedTable)) {
			fprintf(stderr, "Error: Failed to exit function scope at line %d\n", cont_lines);
			YYABORT;
		}
		
		// Integer function with parameters
		if (strcmp($2.str, "main") == 0) {
			fprintf(stderr, "Error: Main function cannot have parameters at line %d\n", cont_lines);
			YYABORT;
		}
		
		FunctionEntry *func = findFunction(&functionTable, $2.str);
		if (func != NULL) {
			if (func->isDefined) {
				fprintf(stderr, "Error: Function '%s' already defined at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		} else {
			int paramCount = 0;
			Parameter *params = parseParameterString($4.str, &paramCount);
			if (!addFunctionPrototype(&functionTable, $2.str, INTEGER, params, paramCount, 0)) {
				freeParameters(params);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		}
		makeCodeFunctionWithParams($$.str, $2.str, INTEGER, $7.str, $4.str);
	}
	| FLOAT_TYPE ID '(' ')' bloco {
		// Float function without parameters
		FunctionEntry *func = findFunction(&functionTable, $2.str);
		if (func != NULL) {
			if (func->isDefined) {
				fprintf(stderr, "Error: Function '%s' already defined at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		} else {
			if (!addFunctionPrototype(&functionTable, $2.str, FLOAT, NULL, 0, 0)) {
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		}
		makeCodeFunction($$.str, $2.str, FLOAT, $5.str);
	}
	| FLOAT_TYPE ID '(' lista_parametros ')' {
		// Enter function scope before parsing body for float functions
		if (!enterScope(&scopedTable, SCOPE_FUNCTION, $2.str)) {
			fprintf(stderr, "Error: Failed to enter function scope at line %d\n", cont_lines);
			YYABORT;
		}

		// Add parameters to function scope
		int paramCount = 0;
		Parameter *params = parseParameterString($4.str, &paramCount);
		if (!addFunctionParameters(&scopedTable, params)) {
			fprintf(stderr, "Error: Failed to add function parameters at line %d\n", cont_lines);
			freeParameters(params);
			YYABORT;
		}
		freeParameters(params);
	} bloco {
		// Exit function scope after processing body
		if (!exitScope(&scopedTable)) {
			fprintf(stderr, "Error: Failed to exit function scope at line %d\n", cont_lines);
			YYABORT;
		}
		
		// Float function with parameters
		FunctionEntry *func = findFunction(&functionTable, $2.str);
		if (func != NULL) {
			if (func->isDefined) {
				fprintf(stderr, "Error: Function '%s' already defined at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		} else {
			int paramCount = 0;
			Parameter *params = parseParameterString($4.str, &paramCount);
			if (!addFunctionPrototype(&functionTable, $2.str, FLOAT, params, paramCount, 0)) {
				freeParameters(params);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		}
		makeCodeFunctionWithParams($$.str, $2.str, FLOAT, $7.str, $4.str);
	}
	| CHAR_TYPE ID '(' ')' bloco {
		// Char function without parameters
		FunctionEntry *func = findFunction(&functionTable, $2.str);
		if (func != NULL) {
			if (func->isDefined) {
				fprintf(stderr, "Error: Function '%s' already defined at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		} else {
			if (!addFunctionPrototype(&functionTable, $2.str, CHAR, NULL, 0, 0)) {
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		}
		makeCodeFunction($$.str, $2.str, CHAR, $5.str);
	}
	| CHAR_TYPE ID '(' lista_parametros ')' {
		// Enter function scope before parsing body for char functions
		if (!enterScope(&scopedTable, SCOPE_FUNCTION, $2.str)) {
			fprintf(stderr, "Error: Failed to enter function scope at line %d\n", cont_lines);
			YYABORT;
		}

		// Add parameters to function scope
		int paramCount = 0;
		Parameter *params = parseParameterString($4.str, &paramCount);
		if (!addFunctionParameters(&scopedTable, params)) {
			fprintf(stderr, "Error: Failed to add function parameters at line %d\n", cont_lines);
			freeParameters(params);
			YYABORT;
		}
		freeParameters(params);
	} bloco {
		// Exit function scope after processing body
		if (!exitScope(&scopedTable)) {
			fprintf(stderr, "Error: Failed to exit function scope at line %d\n", cont_lines);
			YYABORT;
		}
		
		// Char function with parameters
		FunctionEntry *func = findFunction(&functionTable, $2.str);
		if (func != NULL) {
			if (func->isDefined) {
				fprintf(stderr, "Error: Function '%s' already defined at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		} else {
			int paramCount = 0;
			Parameter *params = parseParameterString($4.str, &paramCount);
			if (!addFunctionPrototype(&functionTable, $2.str, CHAR, params, paramCount, 0)) {
				freeParameters(params);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		}
		makeCodeFunctionWithParams($$.str, $2.str, CHAR, $7.str, $4.str);
	}
	| BOOL_TYPE ID '(' ')' bloco {
		// Bool function without parameters
		FunctionEntry *func = findFunction(&functionTable, $2.str);
		if (func != NULL) {
			if (func->isDefined) {
				fprintf(stderr, "Error: Function '%s' already defined at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		} else {
			if (!addFunctionPrototype(&functionTable, $2.str, BOOL, NULL, 0, 0)) {
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		}
		makeCodeFunction($$.str, $2.str, BOOL, $5.str);
	}
	| BOOL_TYPE ID '(' lista_parametros ')' {
		// Enter function scope before parsing body for bool functions
		if (!enterScope(&scopedTable, SCOPE_FUNCTION, $2.str)) {
			fprintf(stderr, "Error: Failed to enter function scope at line %d\n", cont_lines);
			YYABORT;
		}

		// Add parameters to function scope
		int paramCount = 0;
		Parameter *params = parseParameterString($4.str, &paramCount);
		if (!addFunctionParameters(&scopedTable, params)) {
			fprintf(stderr, "Error: Failed to add function parameters at line %d\n", cont_lines);
			freeParameters(params);
			YYABORT;
		}
		freeParameters(params);
	} bloco {
		// Exit function scope after processing body
		if (!exitScope(&scopedTable)) {
			fprintf(stderr, "Error: Failed to exit function scope at line %d\n", cont_lines);
			YYABORT;
		}
		
		// Bool function with parameters
		FunctionEntry *func = findFunction(&functionTable, $2.str);
		if (func != NULL) {
			if (func->isDefined) {
				fprintf(stderr, "Error: Function '%s' already defined at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		} else {
			int paramCount = 0;
			Parameter *params = parseParameterString($4.str, &paramCount);
			if (!addFunctionPrototype(&functionTable, $2.str, BOOL, params, paramCount, 0)) {
				freeParameters(params);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		}
		makeCodeFunctionWithParams($$.str, $2.str, BOOL, $7.str, $4.str);
	}
	| STRING_TYPE ID '(' ')' bloco {
		// String function without parameters
		FunctionEntry *func = findFunction(&functionTable, $2.str);
		if (func != NULL) {
			if (func->isDefined) {
				fprintf(stderr, "Error: Function '%s' already defined at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		} else {
			if (!addFunctionPrototype(&functionTable, $2.str, STRING, NULL, 0, 0)) {
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		}
		makeCodeFunction($$.str, $2.str, STRING, $5.str);
	}
	| STRING_TYPE ID '(' lista_parametros ')' {
		// Enter function scope before parsing body for string functions
		if (!enterScope(&scopedTable, SCOPE_FUNCTION, $2.str)) {
			fprintf(stderr, "Error: Failed to enter function scope at line %d\n", cont_lines);
			YYABORT;
		}

		// Add parameters to function scope
		int paramCount = 0;
		Parameter *params = parseParameterString($4.str, &paramCount);
		if (!addFunctionParameters(&scopedTable, params)) {
			fprintf(stderr, "Error: Failed to add function parameters at line %d\n", cont_lines);
			freeParameters(params);
			YYABORT;
		}
		freeParameters(params);
	} bloco {
		// Exit function scope after processing body
		if (!exitScope(&scopedTable)) {
			fprintf(stderr, "Error: Failed to exit function scope at line %d\n", cont_lines);
			YYABORT;
		}
		
		// String function with parameters
		FunctionEntry *func = findFunction(&functionTable, $2.str);
		if (func != NULL) {
			if (func->isDefined) {
				fprintf(stderr, "Error: Function '%s' already defined at line %d\n", $2.str, cont_lines);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		} else {
			int paramCount = 0;
			Parameter *params = parseParameterString($4.str, &paramCount);
			if (!addFunctionPrototype(&functionTable, $2.str, STRING, params, paramCount, 0)) {
				freeParameters(params);
				YYABORT;
			}
			markFunctionDefined(&functionTable, $2.str);
		}
		makeCodeFunctionWithParams($$.str, $2.str, STRING, $7.str, $4.str);
	}
;


bloco : '{' {
		// Enter block scope only if not already in a function scope
		if (getCurrentScopeLevel(&scopedTable) > 0) {
			if (!enterScope(&scopedTable, SCOPE_BLOCK, "block")) {
				fprintf(stderr, "Error: Failed to enter block scope at line %d\n", cont_lines);
				YYABORT;
			}
		}
	} lista_instrucoes '}' {
		// Exit block scope if we entered one
		if (getCurrentScopeLevel(&scopedTable) > 1) {
			if (!exitScope(&scopedTable)) {
				fprintf(stderr, "Error: Failed to exit block scope at line %d\n", cont_lines);
				YYABORT;
			}
		}
		strcpy($$.str, $3.str);
	}
	| '{' '}' {
		$$.str[0] = '\0';
	}
;

lista_instrucoes: instrucao lista_instrucoes  {
		strcpy($$.str, $1.str);
		sprintf($$.str + strlen($$.str), "%s", $2.str);
	}
	| %empty { $$.str[0] = '\0'; }
;

instrucao: declaracao { strcpy($$.str, $1.str); }
	| comando { strcpy($$.str, $1.str); }
;


comando: comando_atribuicao { strcpy($$.str, $1.str); }
	| comando_io { strcpy($$.str, $1.str); }
	| comando_condicional { strcpy($$.str, $1.str); }
	| comando_repeticao { strcpy($$.str, $1.str); }
	| comando_retorno { strcpy($$.str, $1.str); }
	| chamada_funcao { strcpy($$.str, $1.str); }
;

comando_atribuicao: ID '=' expressao ';'  {
		// Use hybrid search to find in all scopes
		Type foundType;
		int isFromGlobal;
		
		if (!findSymbolHybrid(&scopedTable, &table, $1.str, &foundType, &isFromGlobal)) {
			fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1.str, cont_lines);
			YYABORT;
		}
		
		if (!makeCodeAssignment($$.str, $1.str, $3.str))
			YYABORT;
	}
;

comando_io: READ '(' ID ')' ';'  {
		// Use hybrid search to find in all scopes
		Type foundType;
		int isFromGlobal;
		
		if (!findSymbolHybrid(&scopedTable, &table, $3.str, &foundType, &isFromGlobal)) {
			fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $3.str, cont_lines);
			YYABORT;
		}
		
		makeCodeRead($$.str, $3.str, foundType);
	}
	| WRITE '(' expressao ')' ';'  {
		strcpy($$.str, $3.str);
		makeCodeWrite($$.str, (Type)$3.type);
	}
	| WRITE '(' LITERAL_STR ')' ';'  {
		makeCodeWriteString($$.str, $3.str);
	}
;

comando_condicional: IF '(' expressao_logica ')' bloco %prec THEN {
		makeCodeIf($$.str, $3.str, $5.str);
	}
	| IF '(' expressao_logica ')' bloco ELSE bloco {
		makeCodeIfElse($$.str, $3.str, $5.str, $7.str);
	}
;

comando_repeticao: WHILE '(' expressao_logica ')' {
		// Enter new block scope for while statement
		if (!enterScope(&scopedTable, SCOPE_BLOCK, NULL)) {
			fprintf(stderr, "Error: Failed to enter while block scope at line %d\n", cont_lines);
			YYABORT;
		}
	} bloco {
		// Exit block scope
		if (!exitScope(&scopedTable)) {
			fprintf(stderr, "Error: Failed to exit while block scope at line %d\n", cont_lines);
			YYABORT;
		}
		makeCodeWhile($$.str, $3.str, $6.str);
	}
;

comando_retorno: RETURN expressao ';'  {
		makeCodeReturn($$.str, $2.str, (Type)$2.type);
	}
;

chamada_funcao: ID '(' ')' ';'  {
		// Check if function exists
		FunctionEntry* func = findFunction(&functionTable, $1.str);
		if (func == NULL) {
			fprintf(stderr, "Error: Function '%s' not declared at line %d\n", $1.str, cont_lines);
			YYABORT;
		}
		
		// Generate call code without arguments
		makeCodeFunctionCall($$.str, $1.str, "", func->returnType);
	}
;


expressao: termo  {
		strcpy($$.str, $1.str);
		$$.type = $1.type;
	}
	| expressao '+' expressao  {
		// Check type compatibility
		if (!checkTypeCompatibility((Type)$1.type, (Type)$3.type)) {
			printTypeMismatchError(cont_lines, "addition", (Type)$1.type, (Type)$3.type);
			YYABORT;
		}
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeAdd($$.str, (Type)$1.type);
		$$.type = $1.type;
	}
	| expressao '-' expressao  {	
		// Check type compatibility
		if (!checkTypeCompatibility((Type)$1.type, (Type)$3.type)) {
			printTypeMismatchError(cont_lines, "subtraction", (Type)$1.type, (Type)$3.type);
			YYABORT;
		}
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeSub($$.str, (Type)$1.type);
		$$.type = $1.type;
	}
	| expressao '*' expressao  {	
		// Check type compatibility
		if (!checkTypeCompatibility((Type)$1.type, (Type)$3.type)) {
			printTypeMismatchError(cont_lines, "multiplication", (Type)$1.type, (Type)$3.type);
			YYABORT;
		}
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeMul($$.str, (Type)$1.type);
		$$.type = $1.type;
	}
	| expressao '/' expressao  {
		// Check type compatibility
		if (!checkTypeCompatibility((Type)$1.type, (Type)$3.type)) {
			printTypeMismatchError(cont_lines, "division", (Type)$1.type, (Type)$3.type);
			YYABORT;
		}
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeDiv($$.str, (Type)$1.type);
		$$.type = $1.type;
	}
	| expressao '%' expressao  {
		// Check type compatibility and that it's integer only
		if (!checkTypeCompatibility((Type)$1.type, (Type)$3.type)) {
			printTypeMismatchError(cont_lines, "modulo", (Type)$1.type, (Type)$3.type);
			YYABORT;
		}
		if ($1.type != INTEGER) {
			fprintf(stderr, "Error at line %d: Modulo operation is only allowed with integers.\n", cont_lines);
			YYABORT;
		}
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeMod($$.str);
		$$.type = INTEGER;
	}
	| '-' expressao %prec UMINUS {
		strcpy($$.str, $2.str);
		makeCodeNeg($$.str, (Type)$2.type);
		$$.type = $2.type;
	}
	| '(' expressao ')'  {
		strcpy($$.str, $2.str);
		$$.type = $2.type;
	}
;

termo: NUM  {
		makeCodeLoad($$.str, $1.str, 0);
		$$.type = INTEGER;
	}
	| FLOAT_NUM  {
		makeCodeLoad($$.str, $1.str, 0);
		$$.type = FLOAT;
	}
	| CHAR_LITERAL  {
		makeCodeLoad($$.str, $1.str, 0);
		$$.type = CHAR;
	}
	| TRUE_VAL  {
		makeCodeLoad($$.str, "1", 0);
		$$.type = BOOL;
	}
	| FALSE_VAL  {
		makeCodeLoad($$.str, "0", 0);
		$$.type = BOOL;
	}
	| LITERAL_STR  {
		makeCodeLoad($$.str, $1.str, 0);
		$$.type = STRING;
	}
	| ID  {
		// Use hybrid search to find in all scopes  
		Type foundType;
		int isFromGlobal;
		
		if (!findSymbolHybrid(&scopedTable, &table, $1.str, &foundType, &isFromGlobal)) {
			fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1.str, cont_lines);
			YYABORT;
		}
		
		if (!makeCodeLoad($$.str, $1.str, 1))
			YYABORT;
		$$.type = foundType;
	}
	| ID '(' ')'  {
		// Function call in expression without arguments
		FunctionEntry* func = findFunction(&functionTable, $1.str);
		if (func == NULL) {
			fprintf(stderr, "Error: Function '%s' not declared at line %d\n", $1.str, cont_lines);
			YYABORT;
		}
		
		makeCodeFunctionCallExpression($$.str, $1.str, "", func->returnType);
		$$.type = func->returnType;
	}
	| ID '(' lista_expressoes ')'  {
		// Function call in expression with arguments
		FunctionEntry* func = findFunction(&functionTable, $1.str);
		if (func == NULL) {
			fprintf(stderr, "Error: Function '%s' not declared at line %d\n", $1.str, cont_lines);
			YYABORT;
		}
		
		makeCodeFunctionCallExpression($$.str, $1.str, $3.str, func->returnType);
		$$.type = func->returnType;
	}
;


expressao_logica: expressao '<' expressao  {
		// Check type compatibility
		if (!checkTypeCompatibility((Type)$1.type, (Type)$3.type)) {
			printTypeMismatchError(cont_lines, "comparison", (Type)$1.type, (Type)$3.type);
			YYABORT;
		}
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeComparison($$.str, "<", (Type)$1.type);
		$$.type = INTEGER; // comparison result is always integer (0 or 1)
	}
	| expressao '>' expressao  {
		// Check type compatibility
		if (!checkTypeCompatibility((Type)$1.type, (Type)$3.type)) {
			printTypeMismatchError(cont_lines, "comparison", (Type)$1.type, (Type)$3.type);
			YYABORT;
		}
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeComparison($$.str, ">", (Type)$1.type);
		$$.type = INTEGER;
	}
	| expressao LE expressao  {
		// Check type compatibility
		if (!checkTypeCompatibility((Type)$1.type, (Type)$3.type)) {
			printTypeMismatchError(cont_lines, "comparison", (Type)$1.type, (Type)$3.type);
			YYABORT;
		}
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeComparison($$.str, "<=", (Type)$1.type);
		$$.type = INTEGER;
	}
	| expressao GE expressao  {
		// Check type compatibility
		if (!checkTypeCompatibility((Type)$1.type, (Type)$3.type)) {
			printTypeMismatchError(cont_lines, "comparison", (Type)$1.type, (Type)$3.type);
			YYABORT;
		}
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeComparison($$.str, ">=", (Type)$1.type);
		$$.type = INTEGER;
	}
	| expressao EQ expressao  {
		// Check type compatibility
		if (!checkTypeCompatibility((Type)$1.type, (Type)$3.type)) {
			printTypeMismatchError(cont_lines, "comparison", (Type)$1.type, (Type)$3.type);
			YYABORT;
		}
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeComparison($$.str, "==", (Type)$1.type);
		$$.type = INTEGER;
	}
	| expressao NE expressao  {
		// Check type compatibility
		if (!checkTypeCompatibility((Type)$1.type, (Type)$3.type)) {
			printTypeMismatchError(cont_lines, "comparison", (Type)$1.type, (Type)$3.type);
			YYABORT;
		}
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeComparison($$.str, "!=", (Type)$1.type);
		$$.type = INTEGER;
	}
	| expressao_logica AND expressao_logica  {
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeAnd($$.str);
		$$.type = INTEGER;
	}
	| expressao_logica OR expressao_logica  {
		strcpy($$.str, $1.str);
		strcat($$.str, $3.str);
		makeCodeOr($$.str);
		$$.type = INTEGER;
	}
	| '!' expressao_logica  {
		strcpy($$.str, $2.str);
		makeCodeNot($$.str);
		$$.type = INTEGER;
	}
	| '(' expressao_logica ')'  {
		strcpy($$.str, $2.str);
		$$.type = $2.type;
	}
	| TRUE_VAL  {
		makeCodeLoad($$.str, "1", 0);
		$$.type = BOOL;
	}
	| FALSE_VAL  {
		makeCodeLoad($$.str, "0", 0);
		$$.type = BOOL;
	}
	| ID  {
		// Use hybrid search to find in all scopes  
		Type foundType;
		int isFromGlobal;
		
		if (!findSymbolHybrid(&scopedTable, &table, $1.str, &foundType, &isFromGlobal)) {
			fprintf(stderr, "Error: Variable '%s' not declared at line %d\n", $1.str, cont_lines);
			YYABORT;
		}
		
		if (!makeCodeLoad($$.str, $1.str, 1))
			YYABORT;
		$$.type = foundType;
	}
;

lista_expressoes: expressao  {
		strcpy($$.str, $1.str);
	}
	| lista_expressoes ',' expressao  {
		safe_concat($$.str, sizeof($$.str), $1.str, $3.str);
	}
;

lista_parametros: parametro {
		strcpy($$.str, $1.str);
	}
	| lista_parametros ',' parametro {
		strcpy($$.str, $1.str);
		strcat($$.str, ",");
		strcat($$.str, $3.str);
	}
;

parametro: INT_TYPE ID {
		strcpy($$.str, "int ");
		strcat($$.str, $2.str);
	}
	| FLOAT_TYPE ID {
		strcpy($$.str, "float ");
		strcat($$.str, $2.str);
	}
	| CHAR_TYPE ID {
		strcpy($$.str, "char ");
		strcat($$.str, $2.str);
	}
	| BOOL_TYPE ID {
		strcpy($$.str, "bool ");
		strcat($$.str, $2.str);
	}
	| STRING_TYPE ID {
		strcpy($$.str, "string ");
		strcat($$.str, $2.str);
	}
;


%%

void yyerror(char *s) {
   fprintf(stderr, "Syntax Error: %s at line %d\n", s, cont_lines);
   fprintf(stderr, "Check your syntax near line %d\n", cont_lines);
}

// Parse parameter string and create parameter list
Parameter* parseParameterString(char* paramStr, int* paramCount) {
    if (paramStr == NULL || strlen(paramStr) == 0) {
        *paramCount = 0;
        return NULL;
    }
    
    Parameter* head = NULL;
    Parameter* tail = NULL;
    *paramCount = 0;
    
    // Make a copy of the string to tokenize
    char* str = strdup(paramStr);
    char* token = strtok(str, ",");
    
    while (token != NULL) {
        // Remove leading whitespace
        while (*token == ' ') token++;
        
        // Parse "type name" format
        char* space = strchr(token, ' ');
        if (space != NULL) {
            *space = '\0';
            char* typeName = token;
            char* varName = space + 1;
            
            // Remove trailing whitespace from varName
            int len = strlen(varName);
            while (len > 0 && varName[len-1] == ' ') {
                varName[len-1] = '\0';
                len--;
            }
            
            Type type;
            if (strcmp(typeName, "int") == 0) type = INTEGER;
            else if (strcmp(typeName, "float") == 0) type = FLOAT;
            else if (strcmp(typeName, "char") == 0) type = CHAR;
            else if (strcmp(typeName, "bool") == 0) type = BOOL;
            else if (strcmp(typeName, "string") == 0) type = STRING;
            else type = INTEGER; // default
            
            Parameter* param = createParameter(varName, type);
            if (param != NULL) {
                if (head == NULL) {
                    head = tail = param;
                } else {
                    tail->next = param;
                    tail = param;
                }
                (*paramCount)++;
            }
        }
        
        token = strtok(NULL, ",");
    }
    
    free(str);
    return head;
}
