section .text
	global utoa_s ;make my open transparent to other modules

section .data
    strResult db  '00000000000000000000000000000000', 0 ; string buffer to store results
    my_string_length: equ 31


utoa_s:
	push ebp ;stack maintenance
	mov ebp, esp ;stack maintenance
	push ecx;
	push ebx;

    mov eax, [ebp+8] ; number to be converted
	mov ecx, 10 ; divisor
    xor edx, edx
    mov ebx, 31


divide:
    xor edx, edx        ; high part = 0
    div ecx             ; eax = edx:eax/ecx, edx = remainder
    ;push dx             ; DL is a digit in range [0..9]
    add dl, '0' ; Convert to ASCII
    mov byte [strResult + ebx], dl
    dec ebx              ; count digits
    test eax, eax       ; EAX is 0?
    jnz divide          ; no, continue

    mov eax, strResult
FINISH:
	pop ebx;
	pop ecx;
	mov esp, ebp ;stack maintenance
	pop ebp ;stack maintenance
	
	ret ;stack maintenance
    