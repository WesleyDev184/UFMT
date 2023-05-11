.globl _start

    _start:
        li a0, 2 # a0 = 2
        jal add5  # jump to add5 and save position to ra

    _end:
        li a0, 0            # exit code
        li a7, 93           # syscall exit
        ecall
        

        