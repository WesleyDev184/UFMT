.global _start      # Indica que o símbolo "_start" é global, ponto de entrada do programa.

string:  .asciz "Hello World!!!\n"  # Define um rótulo "string" e aloca a sequência de caracteres na memória.

_start:            # Ponto de entrada do programa.

    li a0, 1            # Carrega o valor imediato 1 em a0 (stdout - descritor de arquivo para saída padrão).
    la a1, string       # Carrega o endereço da string na memória em a1.
    li a2, 19           # Carrega o tamanho da string em a2.
    li a7, 64           # Carrega o valor imediato 64 em a7 (syscall write).
    ecall               # Faz a chamada do sistema write.

_end:              # Rótulo para marcar o final do código.

    li a0, 0            # Carrega o valor imediato 0 em a0 (código de saída).
    li a7, 93           # Carrega o valor imediato 93 em a7 (syscall exit).
    ecall               # Faz a chamada do sistema exit.