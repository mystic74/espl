section .text
	global cmpstr ;make strcmp transparent to other modules
cmpstr:
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ecx;
	push ebx;
	push edx;
	
get_arguments:
	mov eax, [ebp+8] ;retrieves the first function argument, should be string pointer
	mov ebx, [ebp+12] ;retrieves the second function argument, should be string pointer

my_comp:
	mov ecx, 0; Loop index
str_cmp_loop:
	 mov  dl,  byte [eax + ecx] ; taking the value at pointer eax + value of ecx
     mov  dh,  byte [ebx + ecx] ; taking the value at pointer ebx + value of ecx
     inc ecx
     cmp al, 0
     je F_FINISHED
     cmp dh, dl  ; Check null term
     je str_cmp_loop
     jl F_BIG
     jg S_BIG
     

     ;cmp  dl, dh
     
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
	pop edx;
	pop ebx;
	pop ecx;
	mov esp, ebp ;stack maintenance
	pop ebp ;stack maintenance
	
	ret ;stack maintenance