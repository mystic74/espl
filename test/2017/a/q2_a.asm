section .data
	format db "result=%d",0xa,0
	msg1 db "HI",0
	msg2 db "How are you?",0
section .text
	global main 
	extern printf
main:
	push dword msg1
	call funcA
	mov ebx, eax
	push dword msg2
	call funcA
	; Notice how we didn't backup ebx? thats the issue. funcA will wipe it cause its used there..
	add ebx, eax
	push ebx
	push format
	call printf
	mov eax, 1
	int 0x80
funcA:
	push ebp
	mov ebp, esp
	mov eax, -1
	.L2:
	add eax,1
	mov ebx,eax
	add ebx, [ebp+8]
	movzx ebx, BYTE[ebx]
	test bl,bl
	jne .L2
	mov esp, ebp
	pop ebp
	ret
