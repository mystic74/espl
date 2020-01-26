section .data
	file db "test.txt", 0 ; filename
	word_count_str db "-w",0
section .bss
	descriptor resb 4 ; mem for the file descriptor
	buffer resb 60
	len equ 50
	
	ctab equ 9
	cspace equ 32
	cnewline equ 10

	sys_open equ 5
	sys_read equ 3
	sys_close equ 6 
	sys_write equ 4
section .text
	global main
	extern cmpstr ; lab 4
	extern utoa_s ; from task1b

main:

    push ebp                    ; Prolog
    mov ebp, esp
    sub esp, 20                  ; Allocate local variable
    mov eax, 0
    mov [ebp - 4], eax          ; zero for -w counter
    mov [ebp - 8], eax          ; zero for words count
    mov [ebp - 12], eax         ; in_words var
    mov [ebp - 16], eax 		; using file
    push ebx                    ; Callee saved registers
    push esi

    mov eax, [ebp + 8]          ; argc
    cmp eax, 1
    je .J2
    mov esi, [ebp + 12]         ; **argv
    mov ebx, 1                  ; Index of argv
    .J1:
    mov eax, [esi + ebx * 4]    ; *argv[ebx]
    test eax, eax               ; Null pointer?
    je .J2                      ; Yes -> end of loop
    push eax                    ; Pointer to string
    push word_count_str
    call cmpstr
    add esp, 8
    cmp eax, 0
    jne .Diff
    mov eax, 1
    mov [ebp - 4], eax
    mov eax, 0
    jmp .ReLoop
    ;call printf                 ; Call libc
    .Diff:
    mov eax, 1
    mov [ebp - 16], eax
    mov eax, [esi + ebx * 4]
    mov [ebp - 20], eax
   	.ReLoop:
    inc ebx
    jmp .J1                     ; Loop
    .J2:

CHOOSE_FILE:
  mov eax, [ebp - 16]
  cmp eax, 1
  mov ebx, file
  jne READ_FILE
  mov ebx, [ebp - 20]
READ_FILE:
  ;mov ebx,file ;filename
  mov eax, sys_open ;open
  mov ecx,0 ;read only
  int 80h ;open filename for read only

  mov [descriptor],eax ;storing the descriptor

READ_ME:
  mov eax,sys_read ;read from file
  mov ebx,[descriptor] ;your file descriptor
  mov ecx,buffer ;read to buffer
  mov edx,len ;read len bytes
  int 80h ;read len bytes to buffer from file

  push eax ; backup the current amount read

  mov eax, [ebp - 4]  ; Get the -w parameter
  test eax, eax
  jnz CNTWORDS  ; jump if its set to 1.
  
  mov edx,[esp] ;storing count of read bytes to edx
  mov eax,sys_write ;write to file
  mov ebx,1 ; stdout
  mov ecx,buffer ;from buffer
  int 80h ;write to terminal all read bytes from buffer

  ; lets see if we need to loop again
  pop eax
  cmp eax, len
  je READ_ME
  
  jmp DONE
CNTWORDS:
  mov eax, [esp]
  add eax, buffer
  ;mov eax, 0 ; Zero the counter
  mov edx, [ebp - 8]; words count; should start at zero and get bigger.
  mov ecx,buffer
; Setting the while loop on the buffer
BUFFER_LOOP:
  cmp byte[ecx], ctab
  je ZERO_IN_WORD
  cmp byte[ecx], cspace
  je ZERO_IN_WORD
  cmp byte[ecx], cnewline
  je ZERO_IN_WORD
  mov ebx, [ebp - 8] ; Get the current words amount
  mov edx, [ebp - 12] ; Get in_words at edx.
  cmp edx, 0
  jne SET_IN_WORDS
  inc ebx
  mov [ebp - 8], ebx
SET_IN_WORDS:
  mov edx, 1
  mov [ebp - 12], edx ; Set in_words as 1 regardless
  jmp CHECK_BUFF_LOOP ; Loop again

ZERO_IN_WORD:
  mov edx, 0 
  mov [ebp - 12], edx ; Set in_words as zero.

CHECK_BUFF_LOOP:
  inc ecx
  cmp eax, ecx
  jne BUFFER_LOOP
  pop eax ; Get the read bytes from before, don't need this actually
  cmp eax, len  
  je READ_ME
  jmp DONE


DONE:
  mov eax,sys_close ;close file
  mov ebx,[descriptor] ;your file descriptor
  int 80h ;close your file

  mov eax, [ebp - 8]  ; Get the -w parameter
  test eax, eax
  jz FINISH
  mov eax, [ebp - 8] ; The count of words
  push eax
  call utoa_s
  add esp, 4
  
  mov ecx, eax
  mov eax,sys_write ;write to file
  mov ebx, 1 ; stdout
  mov edx,32 ;storing count of readed bytes to edx
	int 80h ;write to terminal all readed bytes from buffer
	

FINISH:
  pop esi                     ; Epilog
  pop ebx
  mov eax,1
  mov ebx,0
  int 80h



