section .text

global _start


printstr:
pop edi
pop edx
pop ecx
mov ebx, 1
mov eax, 4
int 0x80

mov edx, 1
mov ecx, NEWLINE
mov ebx, 1
mov eax, 4
int 0x80

push edi
ret

_start: 

    mov     eax, [x]
    sub     eax, '0'
    mov     ebx, [y]
    sub     ebx, '0'
    add     eax, ebx
    add     eax, '0'

    mov     [sum], eax
    
    mov DWORD [esp], msg
    %define SUPER_VAR esp
    mov eax, [SUPER_VAR]
    push eax
    
    ; mov eax, msg
    ; push eax
    mov eax, len     
    push eax
    call printstr

    mov     ecx, sum
    mov     edx, 1
    mov     ebx, 1
    mov     eax, 4
    int     0x80

    mov     eax, 1
    int     0x80

section .data
    x db '5'
    y db '3'
    msg db  "sum of x and y is "
    len equ $ - msg
    NEWLINE db 10

segment .bss

    sum resb 1
