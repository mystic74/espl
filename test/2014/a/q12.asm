section .text
	global main 

main:
	mov edx, 1
	mov ecx, msg
	mov ebx, 1
	mov eax, 4
	int 0x80
	int 0x80

section .data
msg db 'H'