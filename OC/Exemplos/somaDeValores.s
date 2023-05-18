.global _start

    array: .word 1, 2, 3 # Vetor de entrada

    _start:
        la a0, array # Carrega o endereço do vetor
        li a1, 3 # Carrega o tamanho do vetor
        jal sum # Chama a função sum

    _end:
        li a0, 0 # Código de saída
        li a7, 93 # Carrega o código da syscall para sair do programa
        ecall # Executa a syscall

    sum:
        li t0, 0 # Inicializa o acumulador
        li t1, 0 # Inicializa o contador

        loop:
            beq t1, a1, end # Se o contador for igual ao tamanho do vetor, pula para o fim
            lw t2, 0(a0) # Carrega o valor do vetor
            add t0, t0, t2 # Acumula o valor
            addi t1, t1, 1 # Incrementa o contador
            addi a0, a0, 4 # Incrementa o endereço do vetor
            j loop # Pula para o início do loop

        end:
            mv a0, t0 # Carrega o valor do acumulador
            ret # Retorna para o endereço de retorno