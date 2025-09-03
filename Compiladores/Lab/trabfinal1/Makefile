# The name of the final executable
EXEC = compiler

# Source file names
LEX_SRC = lex.l
YACC_SRC = parser.y
MAIN_SRC = main.c

# Generated C source files
LEX_C = lex.yy.c
YACC_C = parser.tab.c
YACC_H = parser.tab.h
CODE_GEN_C = codeGeneration.c
SYMBOL_TABLE_C = symbolTable.c

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Default target
all: $(EXEC)

# Rule to link the final executable
$(EXEC): $(YACC_C) $(LEX_C) $(MAIN_SRC) $(CODE_GEN_C) $(SYMBOL_TABLE_C)
	$(CC) $(CFLAGS) -o $(EXEC) $(MAIN_SRC) $(YACC_C) $(LEX_C) $(CODE_GEN_C) $(SYMBOL_TABLE_C) -lfl

# Rule to generate the parser C file and header from the Bison grammar
$(YACC_C) $(YACC_H): $(YACC_SRC)
	bison -d -o $(YACC_C) $(YACC_SRC)

# Rule to generate the scanner C file from the Flex definition
$(LEX_C): $(LEX_SRC) $(YACC_H)
	flex -o $(LEX_C) $(LEX_SRC)

# Clean up generated files
clean:
	rm -f $(EXEC) $(LEX_C) $(YACC_C) $(YACC_H) lex_test *.asm  *.o ex