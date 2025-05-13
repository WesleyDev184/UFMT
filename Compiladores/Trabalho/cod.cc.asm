;UFMT-Compiladores
;Prof. Ivairton
;Procedimento para geracao do executavel apos compilacao (em Linux):
;(1) compilacao do Assembly com nasm: $ nasm -f elf64 <nome_do_arquivo>
;(2) likedicao: $ ld -m elf_x86_64 <nome_arquivo_objeto>

extern printf
extern scanf
extern exit

; Label da funcao
f1:

	;Armazenamento de valor de variavel

	push qword [i]

	;Armazenamento de inteiro

	mov rax,1
	push rax

	;Atribuicao de valor a variavel

	pop rax
	mov [i], rax

	; Retorna para o endereco de chamada
	ret

section .bss
	i: resq 1
	x: resq 1
	y: resq 1

section .text
	global main

main:
	;Armazenamento de valor de variavel

	push qword [i]

	;Armazenamento de inteiro

	mov rax,0
	push rax

	;Atribuicao de valor a variavel

	pop rax
	mov [i], rax

	;Armazenamento de valor de variavel

	push qword [i]

	;Atribuicao de valor a variavel

	pop rax
	mov [x], rax

	;Armazenamento de valor de variavel

	push qword [i]

	;Atribuicao de valor a variavel

	pop rax
	mov [y], rax

	; Chamada da funcao 'f1'
	call f1

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

	;i: dd "%d", 4
	;x: dd "%d", 4
	;y: dd "%d", 4
