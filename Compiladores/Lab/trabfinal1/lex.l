%{
	#define _POSIX_C_SOURCE 200809L
	#include <string.h>
	#include <stdio.h>
	#include "parser.tab.h"
	#include "symbolTable.h"
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
	return INT;
}

"float"	{
	strcpy(yylval.c.str, yytext);
	return FLOAT;
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
