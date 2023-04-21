addi t1, zero, 16 # t1: end. do dado de memoria
lw t0, 0(t1) # t0: dado de memoria
addi t0, t0, 1 # t0: dado de memoria + 1
sw t0, 0(t1) # dado de memoria: dado de memoria + 1
.word 33 # uma diretiva que define um dado de 32 bits