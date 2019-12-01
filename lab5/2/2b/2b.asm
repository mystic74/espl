section .data
  file db "testfile",0 ;filename ends with '\0' byte
  word_count_str  db  "-w", 0
  words_count db 0; Boolean, actually.
  argcstr     db `words = %d\n\0`      ; backquotes for C-escapes
section .bss
  descriptor resb 4 ;memory for storing descriptor
  buffer resb 1025
  len equ 50
  ctab equ 9
  cspace equ 32
  cnewline equ 10
section .text
        global main
        extern cmpstr ; From lab 4
        extern printf ;

main:

    push ebp                    ; Prolog
    mov ebp, esp
    sub esp, 12                  ; Allocate local variable
    mov eax, 0
    mov [ebp - 4], eax          ; zero for -w counter
    mov [ebp - 8], eax          ; zero for words count
    mov [ebp - 12], eax         ; in_words var
    push ebx                    ; Callee saved registers
    push esi

    mov eax, [ebp + 8]          ; argc
    cmp eax, 1
    je .J2
    mov esi, [ebp + 12]         ; **argv
    mov ebx, 0                  ; Index of argv
    .J1:
    mov eax, [esi + ebx * 4]    ; *argv[ebx]
    test eax, eax               ; Null pointer?
    je .J2                      ; Yes -> end of loop
    push eax                    ; Pointer to string
    push word_count_str
    call cmpstr
    
    cmp eax, 0
    jne .Diff
    mov eax, 1
    mov [ebp - 4], eax
    mov eax, 0
    ;call printf                 ; Call libc
    .Diff:
    add esp, (2*4)              ; Adjust stack by 3 arguments
    inc ebx
    jmp .J1                     ; Loop
    .J2:

READ_FILE:
  mov eax,5 ;open
  mov ebx,file ;filename
  mov ecx,0 ;read only
  int 80h ;open filename for read only

  mov [descriptor],eax ;storing the descriptor

READ_ME:
  mov eax,3 ;read from file
  mov ebx,[descriptor] ;your file descriptor
  mov ecx,buffer ;read to buffer
  mov edx,len ;read len bytes
  int 80h ;read len bytes to buffer from file
  push eax
  mov eax, [ebp - 4]  ; Get the -w parameter
  test eax, eax
  jnz CNTWORDS  ; jump if its set to 1.
  
  mov edx,[esp] ;storing count of read bytes to edx
  mov eax,4 ;write to file
  mov ebx,1 ; stdout
  mov ecx,buffer ;from buffer
  int 80h ;write to terminal all read bytes from buffer
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
  mov eax,6 ;close file
  mov ebx,[descriptor] ;your file descriptor
  int 80h ;close your file

  ; Debug print
    mov eax, [ebp - 8]
    push eax
    push argcstr
    call printf
    add esp, (2*4)
  ; Done
FINISH:
  pop esi                     ; Epilog
  pop ebx
  mov eax,1
  mov ebx,0
  int 80h



