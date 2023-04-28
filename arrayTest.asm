section .bss
array: resb 16
size: resb 4
index: resb 4
sizes: resb 4

section .text

global _start

log:
pop edi 
; pop edx
pop ecx
mov edx, [sizes + ecx*4]
mov ecx, [array + ecx*4]
mov ebx, 1 
mov eax, 4 
int 0x80 
push edi
ret

_start:
 
    mov WORD [index], 0
    mov WORD [size], 3
    mov eax, x
    mov [array + 0*4], eax
    mov eax, y
    mov [array + 1*4], eax
    mov eax, msg
    mov [array + 2*4], eax
    mov eax, x
    mov [array + 3*4], eax
    
    mov eax, 1
    mov [sizes + 0*4], eax
    mov eax, 1
    mov [sizes + 1*4], eax
    mov eax, 8
    mov [sizes + 2*4], eax
    mov eax, 1
    mov [sizes + 3*4], eax
    
    re:
    mov eax, [index]
    push eax
    call log
    
    mov eax, 1
    add [index], eax
    
    mov ecx, NEWLINE
    mov edx, 1
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    mov eax, [size]
    sub eax, [index]
    jnz re
    
    mov     eax, 1
    int     0x80
    
    ; mov eax, [index]
    ; mov eax, [array + eax*4]
    ; mov ecx, eax
    ; mov edx, 1
    ; mov ebx, 1
    ; mov eax, 4
    ; int 0x80
    
    ; mov eax, 1
    ; add [index], eax
    
    
    ; mov ecx, NEWLINE
    ; mov edx, 1
    ; mov ebx, 1
    ; mov eax, 4
    ; int 0x80
    
    ; mov eax, [index]
    ; mov eax, [array + eax*4]
    ; mov ecx, eax
    ; mov edx, 1
    ; mov ebx, 1
    ; mov eax, 4
    ; int 0x80
    
    ; mov eax, 1
    ; add [index], eax
    
    
    ; mov ecx, NEWLINE
    ; mov edx, 1
    ; mov ebx, 1
    ; mov eax, 4
    ; int 0x80
    
    ; mov eax, [index]
    ; mov eax, [array + eax*4]
    ; mov ecx, eax
    ; mov edx, 8
    ; mov ebx, 1
    ; mov eax, 4
    ; int 0x80
    
    ; mov ecx, NEWLINE
    ; mov edx, 1
    ; mov ebx, 1
    ; mov eax, 4
    ; int 0x80


section .data
    x db '5'
    y db '3'
    msg db  "sum of x"
    len equ $ - msg
     NEWLINE db 10

segment .bss

    sum resb 1
