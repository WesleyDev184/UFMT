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
ERROR_HANDLER_C = errorHandler.c

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -std=c99
# Suppress warnings for generated files
LEX_CFLAGS = -Wno-unused-function -Wno-implicit-function-declaration
DEBUG_FLAGS = -DDEBUG -fsanitize=address -fsanitize=undefined

# Default target
all: $(EXEC)

# Rule to link the final executable
$(EXEC): $(YACC_C) $(LEX_C) $(MAIN_SRC) $(CODE_GEN_C) $(SYMBOL_TABLE_C) $(ERROR_HANDLER_C)
	$(CC) $(CFLAGS) $(LEX_CFLAGS) -o $(EXEC) $(MAIN_SRC) $(YACC_C) $(LEX_C) $(CODE_GEN_C) $(SYMBOL_TABLE_C) $(ERROR_HANDLER_C) -lfl -lm

# Rule to generate the parser C file and header from the Bison grammar
$(YACC_C) $(YACC_H): $(YACC_SRC)
	bison -d -o $(YACC_C) $(YACC_SRC)

# Rule to generate the scanner C file from the Flex definition
$(LEX_C): $(LEX_SRC) $(YACC_H)
	flex -o $(LEX_C) $(LEX_SRC)

asm:
	./$(EXEC) ex.txt
	nasm -f elf64 ex.asm -o ex.o
	gcc -no-pie ex.o -o program
	./program

# Debug target with additional safety checks
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(EXEC)

# Release target with optimizations
release: CFLAGS += -O3 -DNDEBUG
release: $(EXEC)

# Quiet compilation (suppress flex/bison warnings)
quiet: LEX_CFLAGS += -w
quiet: $(EXEC)

# Test target
test: $(EXEC)
	@echo "Running compiler tests..."
	./$(EXEC) ex.txt
	@echo "Assembly generated successfully"

# Run automated test suite
test-suite: $(EXEC)
	@echo "Running automated test suite..."
	./run_tests.sh

# Clean up generated files
clean:
	rm -f $(EXEC) $(LEX_C) $(YACC_C) $(YACC_H) lex_test *.asm  *.o program