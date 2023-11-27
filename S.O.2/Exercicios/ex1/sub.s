.section .text
.globl subfunc

subfunc:
    sub a0, a0, a1 # a0 = a0 - a1
    ret
