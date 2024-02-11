.section .text
.global _start

_start:
    # Informa ao S.O que qeremos executar a função write
    li a7, 64 # a7 = 64
    # configura os argumentos para a função write
    li a0, 1 # a0 = 1 (stdout)
    la a1, msg # a1 = endereço da string
    li a2, 13 # a2 = tamanho da string
    ecall # chama a função write (syscall)


  _end:  # Informa ao S.O que qeremos executar a função exit
    li a7, 93 # a7 = 93 (exit)
    li a0, 0 # a0 = 0 (sucesso)
    ecall # chama a função exit (syscall)

msg:
    .ascii "Hello World\n"
