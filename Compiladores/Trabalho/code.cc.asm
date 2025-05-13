;UFMT-Compiladores
;Prof. Ivairton
;Procedimento para geracao do executavel apos compilacao (em Linux):
;(1) compilacao do Assembly com nasm: $ nasm -f elf64 <nome_do_arquivo>
;(2) likedicao: $ ld -m elf_x86_64 <nome_arquivo_objeto>

extern printf
extern scanf
extern exit

; Label da funcao
teste:

	;escreve valor string

	mov rdi, fmt_output_string
	mov rsi, str0
	xor eax, eax
	call printf

	;escreve valor inteiro

	mov rdi, fmt_output_int
	mov esi, [v]
	xor eax, eax
	call printf

	;escreve valor string

	mov rdi, fmt_output_string
	mov rsi, str1
	xor eax, eax
	call printf

	;escreve valor string

	mov rdi, fmt_output_string
	mov rsi, [n]
	xor eax, eax
	call printf

	;escreve valor string

	mov rdi, fmt_output_string
	mov rsi, str2
	xor eax, eax
	call printf

	; Retorna para o endereco de chamada
	ret

section .bss
	valor: resq 1
	name: resb 256
	v: resq 1
	n: resb 256

section .text
	global main

main:
	;escreve valor string

	mov rdi, fmt_output_string
	mov rsi, str3
	xor eax, eax
	call printf

	;le valor inteiro

	mov rdi, fmt_input_int
	lea rsi, [valor]
	xor eax, eax
	call scanf

	;Armazenamento de valor de variavel

	push qword [name]


	; Empilha o endereço do literal de string str4
	lea rax, [str4]
	push rax

	; Atribuicao de string para name
	pop rax
	mov qword [name], rax

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
	jle label_bool_0
	mov rcx, 0

label_bool_0:
	mov rax, rcx
	push rax

	;jump condicional

	pop rax
	cmp rax, 0
	jz label1

	;escreve valor string

	mov rdi, fmt_output_string
	mov rsi, str5
	xor eax, eax
	call printf

	;Armazenamento de valor de variavel

	push qword [valor]

	;Atribuicao de valor a variavel

	pop rax
	mov [v], rax

	;Armazenamento de valor de variavel

	push qword [name]

	; Atribuicao de string para n
	pop rax
	mov qword [n], rax

	; Chamada da funcao 'teste'
	call teste

	;Armazenamento de valor de variavel

	push qword [valor]

	;Armazenamento de valor de variavel

	push qword [valor]

	;Armazenamento de inteiro

	mov rax,1
	push rax

	;Adicao

	pop rax
	pop rbx
	add rax,rbx
	push rax

	;Atribuicao de valor a variavel

	pop rax
	mov [valor], rax

	;jump incondicional

	jmp label0

label1:

	;escreve valor string

	mov rdi, fmt_output_string
	mov rsi, str6
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
	;name: db "                " 
	;v: dd "%d", 4
	;n: db "                " 
	str0: db "valor: ", 0
	str1: db "nome: ", 0
	str2: db "", 0
	str3: db "Digite um valor:", 0
	str4: db "teste", 0
	str5: db "print do while", 0
	str6: db "fim", 0
