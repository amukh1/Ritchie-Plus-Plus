section .bss
array: resb 20
size: resb 4
index: resb 4
sizes: resb 4
i: resb 4

section .text

global _start

push_back:
pop edi
pop eax
pop edx
mov ebx, [edx]
mov [edx + 4*(ebx)], eax
push edi
ret

log:
pop edi 
; pop edx
pop ecx
mov edx, [sizes + (ecx+1)*4]
mov ecx, [array + (ecx+1)*4]
mov ebx, 1 
mov eax, 4 
int 0x80 
push edi
ret

set:
pop edi
pop eax
pop edx
pop esi
mov [eax + (edx+1)*4], esi
push edi
ret

_start:
 
    mov WORD [index], 0
    
    mov eax, 5
    mov [array + 0*4], eax
    mov eax, y
    mov [array + 1*4], eax
    mov eax, y
    mov [array + 2*4], eax
    mov eax, msg
    mov [array + 3*4], eax
    mov eax, msg2
    mov [array + 4*4], eax
    
    mov eax, 1
    mov [sizes + 0*4], eax
    mov eax, 1
    mov [sizes + 1*4], eax
    mov eax, 1
    mov [sizes + 2*4], eax
    mov eax, 15
    mov [sizes + 3*4], eax
    mov eax, 13
    mov [sizes + 4*4], eax
    mov eax, 15
    mov [sizes + 5*4], eax
    
    mov eax, array
    push eax
    mov eax, msg
    push eax
    call push_back
    
    mov eax, x
    push eax
    mov eax, 0
    push eax
    mov eax, array
    push eax
    call set
    
    
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
    
    mov eax, [array]
    sub eax, 1
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
    msg db  "pointer arrays!"
    msg2 db  "arrays r cool"
    len equ $ - msg
     NEWLINE db 10

segment .bss

    sum resb 1
