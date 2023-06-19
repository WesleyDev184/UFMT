# Inicialização do registrador para o número a ser impresso
li a0, 42   # Carrega o valor inteiro desejado para imprimir (42 neste exemplo)

# Chamada do sistema para imprimir o número
li a7, 1    # Código do serviço de impressão inteira (1)
ecall       # Executa a chamada do sistema

# Termina o programa
li a7, 10   # Código do serviço de término (10)
ecall       # Executa a chamada do sistema
