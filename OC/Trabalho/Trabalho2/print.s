.globl _start

string:  .asciz "Number: \n"
number:  .word 120

_start:
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, string       # buffer
    li a2, 9            # size
    li a7, 64           # syscall write (64)
    ecall

    jal print

_end:
    li a0, 0            # exit code
    li a7, 93           # syscall exit
    ecall

print:
    la t3, number       # Carrega o endereço base da variável number em t3

    li t0, 10           # Carrega o valor 10 em t0 (base decimal)
    li t1, 0            # Inicializa o contador de dígitos em t1

loop:
    rem t2, t3, t0      # Obtém o dígito menos significativo
    addi t2, t2, 48     # Converte o dígito para o padrão ASCII (48 + dígito = ASCII)
    li a0, 1            # file descriptor = 1 (stdout)
    mv a1, t2           # Move o dígito ASCII para a1
    li a2, 1            # size = 1 byte
    li a3, 0            # offset = 0
    li a7, 64           # syscall write (64)
    ecall 

    srai t3, t3, 4      # Desloca o número para a direita
    addi t1, t1, 1      # Incrementa o contador de dígitos
    bnez t3, loop       # Verifica se chegou ao fim dos dígitos

    ret

#Nao consegui fazer imprimir no simulador Ale mas a logica de comversao para ascii esta correta