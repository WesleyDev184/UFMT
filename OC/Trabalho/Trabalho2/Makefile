clean:
	rm -f *.o *.x

compila:
	riscv64-linux-gnu-as -march=rv32g -mabi=ilp32 print.s -o print.o

linka:
	riscv64-linux-gnu-ld -m elf32lriscv print.o -o print.x

dump:
	riscv64-linux-gnu-objdump -D print.o

dumpx:
	riscv64-linux-gnu-objdump -D print.x

run:
	riscv64-linux-gnu-sim print.x