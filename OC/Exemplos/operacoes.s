.globl _start

.data
    input1:     .word 10
    input2:     .word 5
    result:     .word 0
    newline:    .asciz "\n"

.text
_start:
    # Carrega os valores dos operandos
    lw a0, input1
    lw a1, input2

    # Realiza uma adição
    add a2, a0, a1

    # Imprime o resultado da adição
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, result       # buffer
    li a2, 4            # size (assumindo que o resultado seja um número de 32 bits)
    li a7, 64           # syscall write (64)
    ecall

    # Imprime uma nova linha
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, newline      # buffer
    li a2, 1            # size
    li a7, 64           # syscall write (64)
    ecall

    # Realiza uma subtração
    sub a2, a0, a1

    # Imprime o resultado da subtração
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, result       # buffer
    li a2, 4            # size (assumindo que o resultado seja um número de 32 bits)
    li a7, 64           # syscall write (64)
    ecall

    # Imprime uma nova linha
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, newline      # buffer
    li a2, 1            # size
    li a7, 64           # syscall write (64)
    ecall

    # Realiza uma multiplicação
    mul a2, a0, a1

    # Imprime o resultado da multiplicação
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, result       # buffer
    li a2, 4            # size (assumindo que o resultado seja um número de 32 bits)
    li a7, 64           # syscall write (64)
    ecall

    # Imprime uma nova linha
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, newline      # buffer
    li a2, 1            # size
    li a7, 64           # syscall write (64)
    ecall

    # Realiza uma divisão
    div a2, a0, a1

    # Imprime o resultado da divisão
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, result       # buffer
    li a2, 4            # size (assumindo que o resultado seja um número de 32 bits)
    li a7, 64           # syscall write (64)
    ecall

    # Imprime uma nova linha
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, newline      # buffer
    li a2, 1            # size
    li a7, 64           # syscall write (64)
    ecall

    # Termina o programa
    li a0, 0            # exit code
    li a7, 93           # syscall exit
    ecall
