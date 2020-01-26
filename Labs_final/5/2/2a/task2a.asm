section .data
	file db "test5.txt", 0
section .bss
	desc resb 4 ; my file memory descriptor
	buffer resb 60 ; saving a large buffer cause i can.
	len equ 50 ; amount read every time.
section .text
	global main ; entry point.


main:
	; impelement open again..
	mov eax,5 ; open syscall
	mov ebx, file ; filename
	mov ecx, 0 ; RD_ONLY = 0
	int 80h

	mov [desc], eax ; storing the descriptor

READ_ME:
	mov eax, 3 ; read syscall
	mov ebx, [desc] ; the descriptor
	mov ecx, buffer ; the buffer we read into
	mov edx, len ; how much do we want to read
	int 80h

	push eax
	mov edx,[esp] ; esp contains eax now. ; the amount of bytes we want to write
	
	mov eax, 4 ; write syscall
	mov ebx, 1 ; stdout
	mov ecx, buffer ; the buffer we write
	int 80h
	
	pop eax
	cmp eax, len
	je READ_ME

mov eax, 6 ; close syscall
mov ebx, [desc]
int 80h

mov eax, 1
mov ebx, 0
int 80h;

