section .text
	global utoa_s ;make my open transparent to other modules

section .data
    strResult  times 35 db 0 ; string buffer to store results
    my_string_length: equ 31


utoa_s:
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ecx;
	push ebx;
    push edx;
    mov eax, [ebp+8] ; number to be converted
	mov ecx, 10 ; divisor
    xor edx, edx
    xor ebx, ebx


divide:
    xor edx, edx        ; high part = 0
    div ecx             ; eax = edx:eax/ecx, edx = remainder
    add dx, '0'         ; Convert to ASCII
    push dx
    inc ebx             ; count digits
    test eax, eax       ; EAX is 0?
    jnz divide          ; no, continue

; Now using eax as a counter!
reverse_string:
    pop dx
    mov byte [strResult + eax], dl; DL is a ascii in range [0..9]
    inc eax
    dec ebx
    jnz reverse_string

    mov byte [ strResult + eax], 10 
    mov eax, strResult
FINISH:
    pop edx
	pop ebx;
	pop ecx;
	mov esp, ebp ;stack maintenance
	pop ebp ;stack maintenance
	
	ret ;stack maintenance
    