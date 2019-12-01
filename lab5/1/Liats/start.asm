section .text
	
global _start
global read
global write
global open
global close
global strlen

extern main
_start:

	;TODO: handles command line input parameters
	pop    dword ecx    ; ecx = argc
	mov    ebx,esp      ; ebx = argv
	push   ebx   ; char** argv
	push   ecx   ; int argc

	;push dword[esp + 8]
	;push dword[esp + 4]
	;add esp, 20
	call	main
    mov     ebx,eax
	mov	eax,1
	int 0x80

read:
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ecx;
	push ebx;
	push edx;	
	mov eax, 3 ;read from file
  	mov ebx,[ebp + 8] ;your file descriptor
 	mov ecx,[ebp + 12] ;read to buffer
  	mov edx,[ebp + 16] ;read len bytes
  	int 80h ;read len bytes to buffer from file
	pop edx;
	pop ebx;
	pop ecx;
	mov esp, ebp ;stack maintenance
	pop ebp ;stack maintenance
	ret ;stack maintenance
write:
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ecx;
	push ebx;
	push edx;	
	mov eax,4 ;write to file
  	mov ebx,[ebp + 8] ; stdout
  	mov ecx,[ebp + 12] ;from buffer
  	mov edx,[ebp + 16] ;storing count of readed bytes to edx
	int 80h ;write to terminal all readed bytes from buffer
	pop edx;
	pop ebx;
	pop ecx;
	mov esp, ebp ;stack maintenance
	pop ebp ;stack maintenance
	ret ;stack maintenance

open:
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ecx;
	push ebx;
	mov eax, 5	
    mov ebx, [ebp+8] ; string pointer for file name
    mov ecx, [ebp + 12]; flags for the syscall
    int 80h
	pop ebx;
	pop ecx;
	mov esp, ebp ;stack maintenance
	pop ebp ;stack maintenance
	ret ;stack maintenance
close:
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ebx;
	mov eax, [ebp+8] ; syscall number
	mov ebx, [ebp+12] ; fd number
    int 80h
	pop ebx;
	mov esp, ebp ;stack maintenance
	pop ebp ;stack maintenance
	
	ret ;stack maintenance
strlen:
	ret
