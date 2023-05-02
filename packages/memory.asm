section .text

global alloc
alloc:
pop edi
 mov	eax, 45		 ;sys_brk
   xor	ebx, ebx
   int	80h

   pop ebx
   add	eax, ebx	 ;number of bytes to be reserved
   mov	ebx, eax
   mov	eax, 45
   int	80h
	
   cmp	eax, 0
   jl	exit	;exit, if error 
;   mov	edi, eax
  sub	eax, 4		 ;pointing to the last DWORD  
    ; xor eax, eax
   std
   cld
   push edi
   ret

exit:
   mov	eax, 1
   xor	ebx, ebx
   int	80h