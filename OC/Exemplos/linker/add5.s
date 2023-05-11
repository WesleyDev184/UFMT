  numero: .word 5 # numero = 5

  add5:
      lw t0, numero # load numero to t0
      add a0, a0, t0 # add t0 to a0
      jalr zero, 0(ra) # return to ra