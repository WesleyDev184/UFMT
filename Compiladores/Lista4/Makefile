compiler: lex.o synt.o gen.o main.o
	gcc -o compiler main.o lex.o synt.o gen.o -I. -g

lex.o: lex.c
	gcc -c -g lex.c

synt.o: synt.c
	gcc -c -g synt.c

gen.o: gen.c
	gcc -c -g gen.c

main.o: main.c
	gcc -c -g main.c

tstLex: lex.o tst_lex.o
	gcc -o tstLexCompiler lex.o tst_lex.o -I. -g

tst_lex.o: tst_lex.c
	gcc -c -g tst_lex.c

clean:
	rm *.o compiler tstLexCompiler