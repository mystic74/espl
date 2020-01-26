section .text
	global my_open ;make my open transparent to other modules
my_open:
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ecx;
	push ebx;
	
get_arguments:
	
    mov eax, [ebp+8] ; syscall number
	mov ebx, [ebp+12] ; string pointer for file name
    mov ecx, [ebp + 16]; flags for the syscall
    int 80h

FINISH:
	pop ebx;
	pop ecx;
	mov esp, ebp ;stack maintenance
	pop ebp ;stack maintenance
	
	ret ;stack maintenance