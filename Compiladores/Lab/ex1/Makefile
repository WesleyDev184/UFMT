# The name of the final executable
EXEC = compiler

# Source file names
LEX_SRC = lex.l
YACC_SRC = parser.y

# Generated C source files
LEX_C = lex.yy.c
YACC_C = parser.tab.c
YACC_H = parser.tab.h
MAIN_C = main.c

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Default target
all: $(EXEC)

# Rule to link the final executable
$(EXEC): $(YACC_C) $(LEX_C) $(MAIN_C)
	$(CC) $(CFLAGS) -o $(EXEC) $(YACC_C) $(LEX_C) $(MAIN_C) -lfl

# Rule to generate the parser C file and header from the Bison grammar
$(YACC_C) $(YACC_H): $(YACC_SRC)
	bison -d -o $(YACC_C) $(YACC_SRC)

# Rule to generate the scanner C file from the Flex definition
$(LEX_C): $(LEX_SRC) $(YACC_H)
	flex -o $(LEX_C) $(LEX_SRC)

# Target to test only the lexer/scanner
lex_test: $(LEX_C)
	$(CC) $(CFLAGS) -o lex_test $(LEX_C) -lfl

# Clean up generated files
clean:
	rm -f $(EXEC) $(LEX_C) $(YACC_C) $(YACC_H) lex_test