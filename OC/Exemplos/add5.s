.globl _start # global label

  numero: .word 5 # numero = 5

  add5:
      lw t0, numero # load numero to t0
      add a0, a0, t0 # add t0 to a0
      jalr zero, 0(ra) # return to ra

  _start: # main
      li a0, 1 # print_int
      jal ra, add5  # jump to add5 and save position to ra

  _end:
      li a0, 0            # exit code
      li a7, 93           # syscall exit
      ecall