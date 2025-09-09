%{
	#define _POSIX_C_SOURCE 200809L
	#include <string.h>
	#include <stdio.h>
	#include <unistd.h>
	#include "parser.tab.h"
	#include "symbolTable.h"
	/* Ensure fileno is declared for generated scanner code */
	int fileno(FILE *stream);
	void yyerror(char *); 
%}

ws [ \t]
letter [A-Za-z]
digit [0-9]



%%

"//".*\n  {
	cont_lines++;
}

"/*"([^*]|"*"[^/])*"*/"  {
	// Multi-line comment support
	for (int i = 0; yytext[i] != '\0'; i++) {
		if (yytext[i] == '\n') cont_lines++;
	}
}

"int"	{
	strcpy(yylval.c.str, yytext);
	return INT_TYPE;
}

"float"	{
	strcpy(yylval.c.str, yytext);
	return FLOAT_TYPE;
}

"char"	{
	strcpy(yylval.c.str, yytext);
	return CHAR_TYPE;
}

"bool"	{
	strcpy(yylval.c.str, yytext);
	return BOOL_TYPE;
}

"string"	{
	strcpy(yylval.c.str, yytext);
	return STRING_TYPE;
}

"true"	{
	strcpy(yylval.c.str, yytext);
	return TRUE_VAL;
}

"false"	{
	strcpy(yylval.c.str, yytext);
	return FALSE_VAL;
}

"if"	{
	strcpy(yylval.c.str, yytext);
	return IF;
}

"else"	{
	strcpy(yylval.c.str, yytext);
	return ELSE;
}

"while"	{
	strcpy(yylval.c.str, yytext);
	return WHILE;
}

"read"	{
	strcpy(yylval.c.str, yytext);
	return READ;
}

"write"	{
	strcpy(yylval.c.str, yytext);
	return WRITE;
}

"return"	{
	strcpy(yylval.c.str, yytext);
	return RETURN;
}

"=="	{
	strcpy(yylval.c.str, yytext);
	return EQ;
}

"!="	{
	strcpy(yylval.c.str, yytext);
	return NE;
}

"<="	{
	strcpy(yylval.c.str, yytext);
	return LE;
}

">="	{
	strcpy(yylval.c.str, yytext);
	return GE;
}

"&&"	{
	strcpy(yylval.c.str, yytext);
	return AND;
}

"||"	{
	strcpy(yylval.c.str, yytext);
	return OR;
}

{digit}+  {
	strcpy(yylval.c.str, yytext);
	return NUM;
}

{digit}+\.{digit}+  {
	strcpy(yylval.c.str, yytext);
	return FLOAT_NUM;
}

\"[^\"]*\"  {
	strcpy(yylval.c.str, yytext);
	return LITERAL_STR;
}

'.'  {
	strcpy(yylval.c.str, yytext);
	return CHAR_LITERAL;
}

{letter}({letter}|{digit}|_)*	{
	strcpy(yylval.c.str, yytext);
	return ID;
}

[-;:={}+*()<>/%!] {
	return *yytext;
}


{ws}           { }

\r?\n            { cont_lines++; }


. { yyerror("Invalid character"); }

%%

int yywrap (void)
{
 	return 1;
}
