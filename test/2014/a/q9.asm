section .text
	global main 

main:
	mov edx, len2
	mov ecx, msg1
	mov ebx, 1
	mov eax, 4
	int 0x80
	mov eax, 1
	int 0x80

section .data
msg1 db 'Hello '
len1 equ $ - msg1
msg2 db 'world!', 0xa
len2 equ $-msg1
