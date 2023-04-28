section .bss
array: resb 16
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
pop ebx
mov esi, [ebx]
mov [edx + 4*(esi-1)], eax
mov DWORD [ebx],6
push edi
ret

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
    mov WORD [size], 5
    mov eax, x
    mov [array + 0*4], eax
    mov eax, y
    mov [array + 1*4], eax
    mov eax, msg
    mov [array + 2*4], eax
    mov eax, msg2
    mov [array + 3*4], eax
    
    mov eax, 1
    mov [sizes + 0*4], eax
    mov eax, 1
    mov [sizes + 1*4], eax
    mov eax, 15
    mov [sizes + 2*4], eax
    mov eax, 13
    mov [sizes + 3*4], eax
    mov eax, 15
    mov [sizes + 4*4], eax
    
    lea eax, size
    push eax
    mov eax, array
    push eax
    mov eax, msg
    push eax
    call push_back
    
    
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
    msg db  "pointer arrays!"
    msg2 db  "arrays r cool"
    len equ $ - msg
     NEWLINE db 10

segment .bss

    sum resb 1
