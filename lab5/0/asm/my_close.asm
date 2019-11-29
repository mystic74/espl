section .text
	global my_close ;make my_close transparent to other modules
my_close:
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ebx;
	
get_arguments:
	
    mov eax, [ebp+8] ; syscall number
	mov ebx, [ebp+12] ; fd number
    int 80h

FINISH:
	pop ebx;
	mov esp, ebp ;stack maintenance
	pop ebp ;stack maintenance
	
	ret ;stack maintenance