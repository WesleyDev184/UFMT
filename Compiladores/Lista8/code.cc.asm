;UFMT-Compiladores
;Prof. Ivairton
;Procedimento para geracao do executavel apos compilacao (em Linux):
;(1) compilacao do Assembly com nasm: $ nasm -f elf64 <nome_do_arquivo>
;(2) likedicao: $ ld -m elf_x86_64 <nome_arquivo_objeto>

extern printf
extern scanf
extern exit

section .bss
	valor: resd 1

section .text
	global main

main:
	;escreve valor string

	mov rdi, fmt_output_string
	mov rsi, str0
	xor eax, eax
	call printf

	;le valor inteiro

	mov rdi, fmt_input_int
	lea rsi, [valor]
	xor eax, eax
	call scanf

	;Armazenamento de numero

	mov rax,2
	push rax

	;Armazenamento de numero

	mov rax,1
	push rax

	;Subtracao

	pop rbx
	pop rax
	sub rax,rbx
	push rax

	;jump condicional

	pop rax
	cmp rax, 0
	jz label0

	;escreve valor string

	mov rdi, fmt_output_string
	mov rsi, str1
	xor eax, eax
	call printf

	;jump incondicional

	jmp label1
label0:

	;escreve valor string

	mov rdi, fmt_output_string
	mov rsi, str2
	xor eax, eax
	call printf
label1:

;encerra programa

.exit:
	mov rdi, 0
	call exit

section .data
	fmt_input_int db "%d", 0
	fmt_output_int db "%d", 10, 0
	fmt_input_float db "%lf", 0
	fmt_output_float db "%lf", 10, 0
	fmt_input_char db "%c", 0
	fmt_output_char db "%c", 10, 0
	fmt_input_string db "%s", 0
	fmt_output_string db "%s", 10, 0

	;valor: dd "%d", 4
	str0: db "Informe um valor:", 0
	str1: db "O valor do teste eh VERDADEIRO!, 0
	str2: db "O valor do teste eh FALSO!", 0
