extern printf
extern scanf
section .data
fmt_d: db "%ld", 0
fmt_f: db "%f", 0
fmt_s: db "%s", 0
fmt_dln: db "%ld", 10, 0
fmt_fln: db "%f", 10, 0
fmt_sln: db "%s", 10, 0

a: dq 5
b: dq 0
c: dq 3.000000
d: dq 0.0
s: db hello, 0

section .text
global main

main:
mov rbx,[b]
push rbx
mov rbx,10
push rbx
pop rcx
pop rbx
add rbx,rcx
push rbx
pop rbx
mov [a],rbx
mov rbx,[d]
push rbx
mov rbx,2
push rbx
pop rcx
pop rbx
imul rbx,rcx
push rbx
pop rbx
mov [c],rbx
mov rbx,[a]
push rbx
mov rbx,[b]
push rbx
pop rcx
pop rbx
sub rbx,rcx
push rbx
pop rbx
mov [a],rbx
mov rbx,[c]
push rbx
mov rbx,2
push rbx
pop r8
pop rax
xor rdx,rdx
idiv r8
push rax
pop rbx
mov [c],rbx
mov rax,0
ret
