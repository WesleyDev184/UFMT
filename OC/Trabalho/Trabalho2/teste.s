.globl _start

string:  .asciz "Number: \n"
number:  .word 123

_start:
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, string       # buffer
    li a2, 9            # size
    li a7, 64           # syscall write (64)
    ecall

    jal print

_end:
    li a0, 0            # exit code
    li a7, 93           # syscall exit
    ecall

print:
    la t3, number       # Load the base address of the number variable into t3

    li t0, 10           # Load the value 10 into t0 (decimal base)
    li t1, 0            # Initialize the digit counter in t1

convert:
    rem t2, t3, t0      # Get the least significant digit
    addi t2, t2, 48     # Convert the digit to ASCII format (48 + digit = ASCII)
    addi t1, t1, 1      # Increment the digit counter
    srai t3, t3, 4      # Shift the number to the right
    bnez t3, convert    # Check if reached the end of the digits

    addi t1, t1, 1      # Increment the digit counter for the newline character

    # Allocate space for the digits and newline character
    li a0, 0            # file descriptor = 0 (stdin)
    mv a1, t1           # Number of digits + 1 (for newline character)
    li a7, 9            # syscall sbrk (9)
    ecall

    mv t4, a0           # Store the address of the allocated space in t4

    # Store the digits in reverse order
store:
    addi t1, t1, -1     # Decrement the digit counter
    lbu t2, 0(t4)       # Load the byte at the allocated address
    addi t4, t4, 1      # Increment the address
    addi t2, t2, 48     # Convert the ASCII digit back to the original value
    sb t2, 0(t4)        # Store the digit in the allocated space
    bnez t1, store      # Check if all digits are stored

    # Store the newline character
    li t2, 10           # Load the ASCII value of newline character
    sb t2, 0(t4)        # Store the newline character at the end

    # Print the string
    li a0, 1            # file descriptor = 1 (stdout)
    mv a1, t4           # Buffer containing the digits and newline character
    mv a2, t1           # Size of the buffer
    li a7, 64           # syscall write (64)
    ecall

    # Deallocate the allocated space
    li a0, 0            # file descriptor = 0 (stdin)
    mv a1, t4           # Address of the allocated space
    li a7, 10           # syscall brk (10)
    ecall

    ret
