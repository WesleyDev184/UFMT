.global _start 


    _start:
        li a0, 10 # a0 = 10
        jal add5 # call add5

    _end:
        li a0, 0 # a0 = 0
        li a7, 93 # exit
        ecall

    add5:
        addi a0, a0, 5; # a0 = a0 + 5
        ret # return to caller