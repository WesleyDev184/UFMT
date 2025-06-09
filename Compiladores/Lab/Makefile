EXEC = synt

LEX = lex.l
YACC = synt.y

LEX_C = lex.yy.c
YACC_C = synt.tab.c
YACC_H = synt.tab.h

CC = gcc
CFLAGS = -Wall -g

all: $(EXEC)

$(EXEC): $(LEX_C) $(YACC_C)
	$(CC) $(CFLAGS) -o $(EXEC) $(LEX_C) $(YACC_C) -lfl

$(YACC_C) $(YACC_H): $(YACC)
	bison -d $(YACC)

$(LEX_C): $(LEX)
	flex $(LEX)

lex_test: $(LEX_C)
	$(CC) $(CFLAGS) -o lex_test $(LEX_C) -lfl

clean:
	rm -f $(EXEC) $(LEX_C) $(YACC_C) $(YACC_H)
