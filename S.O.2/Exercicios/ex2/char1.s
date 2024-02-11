.section .text
.global firstChar
.global nChar

firstChar:
    lb a0, 2(a0) # load byte
    ret

nChar:
    add a0, a0, a1; # a0 = a0 + a1
    lb a0, 0(a0) # load byte
    ret
    