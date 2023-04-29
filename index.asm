
section .bss

v: resb 4
e: resb 4
a: resb 4
b: resb 4
section	.text
 
println: 
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

print: 
pop edi 
pop edx 
pop ecx 
mov ebx, 1 
mov eax, 4 
int 0x80 

mov eax, 0 
push edi 
ret

main2:
mov eax,4
  mov eax, RPP_CONSTANT_0
  push eax
  mov eax, 12
  push eax
  call println

mov eax, 0
mov [v], eax
mov eax, RPP_CONSTANT_1
mov [v], eax
mov eax, v
mov [e], eax
  mov eax, [v]
  push eax
  mov eax, 2
  push eax
  call println

lea eax, v
mov [a], eax
mov eax, [a]
 mov edx, [eax] 
 mov [b], edx
  mov eax, [b]
  push eax
  mov eax, 2
  push eax
  call println

  mov eax, 0
   ret

section .data

 NEWLINE db 10
RPP_CONSTANT_0 db "Hello World!", 0
RPP_CONSTANT_1 db "hi", 0
