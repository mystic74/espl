section .text
	global utoa_s ; make utoa_s transparent to other modules

section .data
	strRes times 34 db 0 ; Create a buffer large enough to contain a string, + \n + \0 if wanted.
	my_string_length : equ 31 ; Just a constant.
	divisor : equ 10


utoa_s : 
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ecx;
	push ebx;
    push edx;
    mov eax, [ebp+8] ; number to be converted
	mov ecx, divisor ; Setting once to prevent multiple moves.
    xor edx, edx
    xor ebx, ebx  ; divide part : count amount of digits, reverse part : reverse counter;

; While we still have a  number, dividing by 10, adding the reminder as ascii to the stack, and looping on.
divide:
    xor edx, edx        ; high part = 0
    div ecx             ; eax = edx:eax/ecx, edx = remainder
    add dx, '0'         ; Convert to ASCII
    push dx
    inc ebx             ; count digits
    test eax, eax       ; EAX is 0?
    jnz divide          ; no, continue

; Setting eax as a counter to control the offset for each byte.
; Using the amount counted in divide part (a) to 
reverse_string:
    pop dx
    mov byte [strRes + eax], dl; DL is a ascii in range [0..9]
    inc eax
    dec ebx
    jnz reverse_string

    ; Just for read causes.
    mov byte [strRes + eax], 10
    inc eax
    ; Real code.
    mov byte [strRes + eax], 0
    mov eax, strRes

FINISH :
	pop edx ; stack maintenance
	pop ebx
	pop ecx
	mov esp, ebp
	pop ebp
	ret; stack maintenance