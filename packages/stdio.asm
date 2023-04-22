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

push edi
ret