compiler: lex.o synt.o gen.o symbols.o
	gcc -o compiler lex.o synt.o gen.o symbols.o -I. -g

lex.o: lex.c
	gcc -c -g lex.c

synt.o: synt.c
	gcc -c -g synt.c

gen.o: gen.c
	gcc -c -g gen.c

symbols.o: symbols.c
	gcc -c -g symbols.c

tstLex: lex.o tst_lex.o
	gcc -o tstLexCompiler lex.o tst_lex.o -I. -g

tst_lex.o: tst_lex.c
	gcc -c -g tst_lex.c

asm.o: code.cc.asm
	nasm -f elf64 code.cc.asm

testAsm: asm.o
	ld -e main -melf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc code.cc.o -o code

clean:
	rm *.o compiler tstLexCompiler code