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
	;Armazenamento de valor de variavel

	push qword [valor]

	;Armazenamento de inteiro

	mov rax,9
	push rax

	;Atribuicao de valor a variavel

	pop rax
	mov [valor], rax
label0:

	;Armazenamento de valor de variavel

	push qword [valor]

	;Armazenamento de inteiro

	mov rax,10
	push rax

	;Aplica operador booleano/exp.logica

	pop rbx
	pop rax
	mov rcx,1
	cmp rax,rbx
	jl label_bool_0
	mov rcx, 0

label_bool_0:
	mov rax, rcx
	push rax

	;jump condicional

	pop rax
	add rsp, 8
	cmp rax, 0
	jz label1

	;escreve valor string

	mov rdi, fmt_output_string
	mov rsi, str0
	xor eax, eax
	call printf

	;Armazenamento de valor de variavel

	push qword [valor]

	;Armazenamento de inteiro

	mov rax,11
	push rax

	;Atribuicao de valor a variavel

	pop rax
	mov [valor], rax

	;jump incondicional

	jmp label0
label1:

	;escreve valor string

	mov rdi, fmt_output_string
	mov rsi, str1
	xor eax, eax
	call printf

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
	str0: db "print do while", 0
	str1: db "fim", 0
