section .text
	global funcA
	
funcA:
	push	ebp
	mov	ebp, esp
	push ebx
	mov	eax,-1 ; Set counter on -1

.L2:
	add eax, 1 ; start counting!
	mov ebx, eax
	add ebx, [ebp+8] ; Add counter to pointer
	movzx	ebx, BYTE [ebx] ; Get the lower byte and pad with zeros
	test bl,bl ; Check the Zero Flag for lower byte zero
	jne .L2 ; repeat as needed
	pop ebx
	mov esp, ebp ; return home.
	pop ebp
	ret