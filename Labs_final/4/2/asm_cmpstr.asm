section .text
	global cmpstr ;make cmpstr transparent to other modules
cmpstr:
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ecx; Saving all registers in use
	push ebx
	;push edx
	
get_arguments:
	mov eax, [ebp+8] ;retrieves the first function argument
	mov ebx, [ebp+12] ;retrieves the second function argument

cmpare:
	mov ecx, 0 ; zeroing counter
str_cmp_loop:
 	mov  dl,  byte [eax + ecx] ; taking the value at pointer eax + value of ecx
 	mov  dh,  byte [ebx + ecx] ; taking the value at pointer ebx + value of ecx
 	inc ecx
 	cmp dl, 0 ; Check null term
 	je F_FINISHED
 	cmp dh, dl  ; Check if still eq
 	je str_cmp_loop
 	jl F_BIG
 	jg S_BIG

F_FINISHED:
	cmp dh, 0 ; Might both have finished?
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
	;pop edx
	pop ebx
	pop ecx;
	mov esp, ebp ;stack maintenance
	pop ebp ;stack maintenance
	
	ret ;stack maintenance