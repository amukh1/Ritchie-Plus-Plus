
section .text

;global _start
global retr

global vector
vector:
pop edi

push edi
ret

global push_back
push_back:
pop edi
pop eax
pop edx
mov ebx, [edx]
mov [edx + 4*(ebx)], eax
add ebx, 1
mov [edx], ebx
push edi
ret

global set
set:
pop edi
pop eax
pop edx
pop esi
mov [eax + (edx+1)*4], esi
push edi
ret

global retr
retr:
pop edi
pop edx
pop esi
mov eax, [esi + (edx + 2)*4]
push edi
ret
