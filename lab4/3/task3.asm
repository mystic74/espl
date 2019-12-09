section .data

         my_string:    db 'abcdefg', 10
         my_string_length: equ $-my_string
         my_buffer :  db 0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0

section .text
         global main
         extern printf

main:
	nop
	
	push	ebp
	mov	ebp, esp
	push ecx
	push ebx
	mov ecx, 0 ; Using as counter
	mov ebx, my_string_length
	dec ebx
my_cpy:
	mov al, byte [my_string + ebx] ; Copying byte format
	mov byte [my_buffer + ecx],  al
	inc ecx ; Inc\Dec counter
	dec ebx
	jnz my_cpy

; Last copy out of loop
	mov bl, byte [my_string]
	mov byte [my_buffer + ecx], bl

FINISH:
; Printing
; commented because the string does not have a null term, so it will print both buffers
;	push my_string
;    call printf
;    add esp, 4

	push my_buffer
    call printf
    add esp, 4

	pop ebx
	pop ecx
	mov esp, ebp ; return home.
	pop ebp
	xor eax, eax
	ret