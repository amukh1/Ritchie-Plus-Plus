section .bss
v: resb 4
vp: resb 4

section .text

global _start

alloc:
pop edi
 mov	eax, 45		 ;sys_brk
   xor	ebx, ebx
   int	80h

   pop ebx
   add	eax, ebx	 ;number of bytes to be reserved
   mov	ebx, eax
   mov	eax, 45		 ;sys_brk
   int	80h
	
   cmp	eax, 0
   jl	exit	;exit, if error 
;   mov	edi, eax	 ;EDI = highest available address
  sub	eax, 4		 ;pointing to the last DWORD  
    ; xor eax, eax
   std			 ;backward
   cld			 ;put DF flag to normal state
   push edi
   ret

_start:
    mov eax, 4
    push eax
    call alloc
    
    ; mov ebx, [eax]
    mov [v], eax ; make v pointer to whatever eax is pointing to
   
   mov edi, msg
   mov [eax], edi ; put value at pointed address
   
   mov ecx, [v]
   mov ebx, [ecx]
   mov [vp], ebx ; deref
  
   mov	ecx, [vp]
   mov	eax, 4
   mov	ebx, 1
   mov	edx, len
   int	80h		 ;print a message
   
   exit:
   mov	eax, 1
   xor	ebx, ebx
   int	80h

section .data
    x db '5'
    y db '3'
    msg    	db	"Allocated 16 kb of memory!", 10
    len equ $ - msg

segment .bss

    sum resb 1
