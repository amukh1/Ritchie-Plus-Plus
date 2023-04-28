section .bss
array: resb 4
size: resb 4
v1: resb 4
v2: resb 4
v3: resb 4

section .text

global _start

_start:
    mov DWORD [array + 0*4], x
    mov DWORD [array + 1*4], y
    mov DWORD [array + 2*4], msg
    mov DWORD [array + 3*4], x
    
    mov eax, [array + 0*4]
    mov ecx, eax
    mov edx, 1
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    mov ecx, NEWLINE
    mov edx, 1
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    mov eax, [array + 1*4]
    mov ecx, eax
    mov edx, 1
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    mov ecx, NEWLINE
    mov edx, 1
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    mov eax, [array + 2*4]
    mov ecx, eax
    mov edx, 8
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    mov ecx, NEWLINE
    mov edx, 1
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    mov eax, [array + 3*4]
    mov ecx, eax
    mov edx, 1
    mov ebx, 1
    mov eax, 4
    int 0x80


    mov     eax, 1
    int     0x80

section .data
    x db '5'
    y db '3'
    msg db  "sum of x"
    len equ $ - msg
     NEWLINE db 10

segment .bss

    sum resb 1
