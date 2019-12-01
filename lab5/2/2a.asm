section .data
  file db "testfile",0 ;filename ends with '\0' byte
section .bss
  descriptor resb 4 ;memory for storing descriptor
  buffer resb 1025
  len equ 50
section .text
         global main

main:
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
  jne FINISH
  mov edx,eax ;storing count of readed bytes to edx
  mov eax,4 ;write to file
  mov ebx,1 ; stdout
  mov ecx,buffer ;from buffer
  int 80h ;write to terminal all readed bytes from buffer
  jmp READ_ME
  
FINISH:
  mov edx,eax ;storing count of readed bytes to edx
  mov eax,4 ;write to file
  mov ebx,1 ; stdout
  mov ecx,buffer ;from buffer
  int 80h ;write to terminal all readed bytes from buffer

  mov eax,6 ;close file
  mov ebx,[descriptor] ;your file descriptor
  int 80h ;close your file

  mov eax,1
  mov ebx,0
  int 80h