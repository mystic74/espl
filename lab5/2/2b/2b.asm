section .data
  file db "testfile",0 ;filename ends with '\0' byte
  fmtint  db  "%d", 10, 0
  fmtstr  db  "%s", 10, 0
  word_count_str  db  "-w", 0
  words_count db 0; Boolean, actually.
  argcstr     db `argc = %d\n\0`      ; backquotes for C-escapes
    argvstr     db `argv[%u] = %s\n\0`
section .bss
  descriptor resb 4 ;memory for storing descriptor
  buffer resb 1025
  len equ 50
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
    ;push eax
    ;push argcstr
    ;call printf                 ; Call libc
    ;add esp, (2*4)              ; Adjust stack by 2 arguments
    cmp eax, 1
    je .J2
    mov esi, [ebp + 12]         ; **argv
    mov ebx, 0                  ; Index of argv
    .J1:
    mov eax, [esi + ebx * 4]    ; *argv[ebx]
    test eax, eax               ; Null pointer?
    je .J2                      ; Yes -> end of loop
    push eax                    ; Pointer to string
    ;push ebx                    ; Integer
    ;push argvstr                ; Pointer to format string
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

  cmp eax, len
  jne FINISH_READ
  
  push eax
  mov eax, [ebp - 4] 
  test eax, eax
  jnz CNTWORDS 
  pop eax
  mov edx,eax ;storing count of readed bytes to edx
  mov eax,4 ;write to file
  mov ebx,1 ; stdout
  mov ecx,buffer ;from buffer
  int 80h ;write to terminal all readed bytes from buffer
  jmp READ_ME
CNTWORDS:
  pop eax ; Get the read bytes from before.
;  mov edx, eax
;CHAR_LOOP:
;  dec edx ; ?????
;  mov eax, 0 ; words counter
;  mov ebx, 0 ; char index
;  cmp edx
;  jnz CHAR_LOOP

FINISH_READ:
  mov edx,eax ;storing count of readed bytes to edx
  mov eax,4 ;write to file
  mov ebx,1 ; stdout
  mov ecx,buffer ;from buffer
  int 80h ;write to terminal all readed bytes from buffer

  mov eax,6 ;close file
  mov ebx,[descriptor] ;your file descriptor
  int 80h ;close your file


  ; Debug print
    mov eax, [ebp - 4]
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



