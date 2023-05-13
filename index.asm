
section .bss

vec: resb 4
v: resb 4
v0: resb 4
v1: resb 4
ap: resb 4
aa: resb 4
section	.text
 extern println
extern printstr
extern push_back
extern set
extern retr
extern alloc
extern malloc
global _start
    _start:
 call main 
 mov eax, 1
 int 0x80
main:
mov eax, RPP_CONSTANT_0
  push eax
mov eax, 2
  push eax
  call printstr

mov eax, 2
mov [vec], eax
lea eax, vec
mov [v], eax
mov eax, [v]
  push eax
mov eax, RPP_CONSTANT_1
  push eax
  call push_back

mov eax, [v]
  push eax
mov eax, 0
  push eax
  call retr

mov eax, eax
mov [v0], eax
mov eax, [v0]
  push eax
mov eax, 2
  push eax
  call printstr

mov eax, [v]
  push eax
mov eax, RPP_CONSTANT_2
  push eax
  call push_back

mov eax, [v]
  push eax
mov eax, 1
  push eax
  call retr

mov eax, eax
mov [v1], eax
mov eax, [v1]
  push eax
mov eax, 2
  push eax
  call printstr

mov eax, 4
  push eax
  call alloc

mov eax, eax
mov [ap], eax
mov eax, [ap]
  push eax
mov eax, RPP_CONSTANT_3
  push eax
  call malloc

mov eax, [ap]
 mov edx, [eax] 
 mov [aa], edx
mov eax, [aa]
  push eax
mov eax, 2
  push eax
  call printstr

mov eax, 0
  ret

section .data

 NEWLINE db 10
RPP_CONSTANT_0 db "hi", 0
RPP_CONSTANT_1 db "ch", 0
RPP_CONSTANT_2 db "sh", 0
RPP_CONSTANT_3 db "hi", 0
