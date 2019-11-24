section .text
	global funcA
	
funcA:
	push	ebp
	mov	ebp, esp
	mov	eax,-1
.L2:
	add eax, 1
	mov ebx, eax
	add ebx, [ebp+8] ; Using just one param.
	movzx	ebx, BYTE [ebx] ; Saving the lower byte and using unsigned i guess?
	test bl,bl
	jne .L2
	mov esp, ebp
	pop ebp
	ret