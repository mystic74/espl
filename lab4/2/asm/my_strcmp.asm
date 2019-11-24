section .text
	global cmpstr ;make strcmp transparent to other modules
strcmp:
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ecx;
	push ebx;
	
get_arguments:
	movzx eax, BYTE [ebp+8] ;retrieves the first function argument, READ about MOVZX
	movzx ecx, BYTE [ebp+12] ;retrieves the second function argument, READ about MOVZX

cmpstr:
	mov ecx, 0; Loop index
str_cmp_loop:
	 mov dl, BYTE [eax+ecx]
     mov dh, BYTE [ebx+ecx]
     inc ecx
     cmp dl, 0 ; Check null term
     cmp BYTE dl, BYTE dh
     je str_cmp_loop
     jl F_BIG
     jg S_BIG

F_FINISHED:
	cmp dh, 0
	jne S_BIG
	mov eax, 0;
	jmp FINISH
F_BIG:
	mov eax, 1 ;return value need to be stored in eax register
	jmp FINISH
	
S_BIG:
	mov eax, 2 ;return value need to be stored in eax register
	jmp FINISH
	
FINISH:
	pop ebx;
	pop ecx;
	mov esp, ebp ;stack maintenance
	pop ebp ;stack maintenance
	
	ret ;stack maintenance