CC = riscv64-linux-gnu-gcc
CFLAGS = -static

all: run

char1main.o: char1main.c
	@$(CC) -c $< -o $@

char1.o: char1.s
	@$(CC) -c $< -o $@

teste.x: char1.o char1main.o
	@$(CC) $(CFLAGS) $^ -o $@

run: teste.x
	@qemu-riscv64-static $<

clean:
	@rm -f *.o teste.x & clear