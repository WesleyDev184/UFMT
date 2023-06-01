# Ponto de entrada do programa
.global _start

string:  .asciz "Hello World!!!\n"  # Define um rótulo "string" e aloca a sequência de caracteres na memória.

_start:            # Ponto de entrada do programa.

    li a0, 1            # Carrega o valor imediato 1 em a0 (stdout - descritor de arquivo para saída padrão).
    la a1, string       # Carrega o endereço da string na memória em a1.
    li a2, 19           # Carrega o tamanho da string em a2.
    li a7, 64           # Carrega o valor imediato 64 em a7 (syscall write).
    ecall               # Faz a chamada do sistema write.

    jal strLen          # Chama a função strLen.

_end:              # Rótulo para marcar o final do código.

    li a0, 0            # Carrega o valor imediato 0 em a0 (código de saída).
    li a7, 93           # Carrega o valor imediato 93 em a7 (syscall exit).
    ecall               # Faz a chamada do sistema exit.

strLen:            # Definição da função strLen.

    li t1, 0           # Inicializa o contador de caracteres em 0.
    li t2, 0           # Inicializa o byte atual em 0.

    loop:              # Início do loop.

        lb t2, 0(a1)   # Carrega o byte da string em t2.
        beq t2, zero, end  # Se o byte for zero (fim da string), termina o loop.
        addi t1, t1, 1  # Incrementa o contador de caracteres.
        addi a1, a1, 1  # Incrementa o endereço da string.
        j loop          # Volta para o início do loop.

    end:               # Fim do loop.
        mv  a1, t1     # Move o valor de t1 para a1 (a0 = t1).
        ret             # Retorna da função strLen.
