
CC      = gcc
CFLAGS  = -Wall -g
BISON   = bison -d -Wall
FLEX    = flex

all: tab_simb

tab_simb: tab_simb.tab.o lex.yy.o
	$(CC) $(CFLAGS) -o $@ $^

tab_simb.tab.c tab_simb.tab.h: tab_simb.y
	$(BISON) -o tab_simb.tab.c tab_simb.y

lex.yy.c: tab_simb.l tab_simb.tab.h
	$(FLEX) -o lex.yy.c tab_simb.l

# Compilações
tab_simb.tab.o: tab_simb.tab.c
	$(CC) $(CFLAGS) -c $<

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c $<

test: tab_simb teste.txt
	./tab_simb < teste.txt

clean:
	rm -f *.o tab_simb tab_simb.tab.c tab_simb.tab.h lex.yy.c

