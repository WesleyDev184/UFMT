.globl _start

num: .word 123

_start:
  # Configurar o argumento da função
  lui a0, %hi(num)        # Carregar os bits mais significativos do endereço de 'num' em a0
  addi a0, a0, %lo(num)   # Adicionar os bits menos significativos do endereço de 'num' em a0

  # Chamar a função print
  jal print           # Chamar a função 'print' e salvar o endereço de retorno em ra

_end:
  # Finalizar o programa
  li a0, 0                # Código de saída 0: sem erros
  li a7, 93               # Código do sistema para sair (93 para o RISC-V)
  ecall                   # Fazer a chamada do sistema para encerrar o programa

print:
  # Alocar espaço para os dígitos na memória
  li t0, 10               # Divisor (10 para separar os dígitos)
  lw a0, 4(sp)            # Carregar o argumento (inteiro)
  li t1, 0                # Inicializar contador
  li t3, -1               # Inicializar offset na memória

  loop:
    rem t2, a0, t0        # Calcular o resto da divisão (dígito atual)
    addi t2, t2, 48       # Converter o dígito para o padrão ASCII
    add t4, a1, t3        # Calcular o endereço de destino
    sb t2, 0(t4)          # Armazenar o dígito na memória
    addi t3, t3, -1       # Avançar para o próximo endereço (ordem reversa)
    addi t1, t1, 1        # Incrementar o contador

    div a0, a0, t0        # Dividir o número pelo divisor
    bnez a0, loop         # Repetir o loop enquanto o número não for zero

  # Imprimir os dígitos na saída padrão
  li a1, 1                # Descritor de arquivo 1: saída padrão
  mv a0, a1               # Mover o endereço de memória para a saída
  neg a2, t3              # Calcular o tamanho do buffer negativo
  li a7, 64               # Código do sistema para escrever
  ecall                   # Fazer a chamada do sistema para escrever

  ret
