.global _start


    _start:
        li a0, 1 # a0 = 1
        jal f1  # jump to f1 and save position to ra

    f1:
        add t5, a0, a1; # t5 = a0 + a1
        add t5, t5, a3; # t5 = t5 + a3
        mv  a0, t5 # a0 = t5
        jalr ra, 0(ra) # jump to ra and save position to ra

    _end:
        j _end