; UFMT-Compiladores
; Prof. Ivairton
; Procedimento para geracao do executavel apos compilacao (em Linux 64):
; (1) compilacao do Assembly com nasm: $ nasm -f elf64 <nome_do_arquivo>
; (2) likedicao: $ ld -e main -melf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc <nome_arquivo_objeto> -o <arquivo_executavel>

extern printf
extern scanf
extern exit

section .data
fmt_i_int db "%d", 0
fmt_o_int db "%d", 10, 0
fmt_i_float db "%f", 0
fmt_o_float db "%f", 10, 0

section .bss
a resd 1

section .text
	global main,_start
main:
_start:

;le valor inteiro
  mov rdi, fmt_i_int
  lea rsi, [a]
  xor eax, eax
  call scanf

;escreve valor inteiro
  mov rdi, fmt_o_int
  mov esi, [a]
  xor eax, eax
  call printf

;encerra programa
	mov ebx,0
	mov eax,1
	int 0x80

;Label para chamada do exit/encerra programa
exit:
	mov rdi, 0;
	call exit
