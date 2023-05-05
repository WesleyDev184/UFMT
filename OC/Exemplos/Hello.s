# Imprime "Hello, world!" na tela e encerra o programa.

# Define a mensagem a ser impressa.
msg:
	.string: .asciiz "Hello, world!\n"

# Ponto de entrada do programa.
_start:
	# Chama a função de sistema para imprimir a mensagem.
	li a0, 4   # Carrega o número da syscall para imprimir.
	la a1, msg # Carrega o endereço da mensagem.
	li a2, 14  # Carrega o tamanho da mensagem.
	li a7, 64  # Carrega o número da syscall para execução.
	ecall     # Chama a syscall.

	# Chama a função de sistema para encerrar o programa.
	li a0, 0   # Carrega o código de saída.
	li a7, 93  # Carrega o número da syscall para sair.
	ecall     # Chama a syscall.
