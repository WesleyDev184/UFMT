# Ponto de entrada do programa
.global _start

    string:  .asciz "Hello World!!!\n"

    _start:
        li a0, 1  # file descriptor = 1 (stdout)
        la a1, string # buffer
        li a2, 19 # size
        li a7, 64 # syscall write (64)
        ecall

        jal strLen # Chama a função strLen

    _end:
        li a0, 0 # Código de saída
        li a7, 93 # Carrega o código da syscall para sair do programa
        ecall # Executa a syscall

    strLen:
        li t1, 0 # Contador de caracteres
        li t2, 0 # Byte atual
        
        loop:
            lb t2, 0(a1) # Carrega o byte da string em t2    
            beq t2, zero, end # Se o byte for zero, termina o loop  
            addi t1, t1, 1 # Incrementa o contador de caracteres
            addi a1, a1, 1 # Incrementa o endereço da string
            j loop # Volta para o início do loop

        end:
            mv  a1, t1 # a0 = t1
            ret