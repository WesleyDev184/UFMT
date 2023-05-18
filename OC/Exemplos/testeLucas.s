sum:
    mv t1, zero   # Variável de soma
    mv t2, a0     # Ponteiro para o vetor
    li t3, 3      # Contador de valores somados

laco:
    lb t0, 0(t2)    # Carrega o valor do vetor em t0
    beqz t0, fim_sum   # Verifica se o valor é zero
    add t1, t1, t0   # Soma o valor ao total (t1)
    addi t2, t2, 4   # Incrementa o ponteiro para o próximo elemento (4 bytes)
    addi t3, t3, -1  # Decrementa o contador

    bnez t3, laco   # Verifica se ainda é necessário somar mais valores

fim_sum:
    mv a0, t1
    j exit

.global _start

_start:
    la a0, vetor
    li a1, 3
    jal sum

exit:
    li a7, 93
    ecall

vetor: .word 1, 3, 5