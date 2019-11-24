section .text
	global my_cmp ;make my_cmp transparent to other modules
my_cmp:
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ecx;
	
get_arguments:
	movzx eax, BYTE [ebp+8] ;retrieves the first function argument, READ about MOVZX
	movzx ecx, BYTE [ebp+12] ;retrieves the second function argument, READ about MOVZX

cmpare:
	cmp eax, ecx
	jnge S_BIG
	jmp F_BIG
	
	
F_BIG:
	mov eax, 1 ;return value need to be stored in eax register
	jmp FINISH
	
S_BIG:
	mov eax, 2 ;return value need to be stored in eax register
	jmp FINISH
	
FINISH:
	pop ecx;
	mov esp, ebp ;stack maintenance
	pop ebp ;stack maintenance
	
	ret ;stack maintenance