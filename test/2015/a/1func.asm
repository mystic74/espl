section .text
    global func

func:
    xor edx, edx
    add edx, [esp + 4]
    mov edx , [edx]
    mov eax, [esp + 8]
    mov eax, [eax]
    mov ebx, [esp + 4]
    mov [ebx], eax
    mov eax, [esp + 12]
    mov eax, [eax]
    mov ebx, [esp+8]
    mov [ebx], eax
    mov ebx, [esp + 4]
    mov [ebx], ed   x
    ret