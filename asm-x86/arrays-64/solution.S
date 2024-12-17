// Это комментарий, как в Си/С++
.text
.global sum
.intel_syntax noprefix


sum:     
    // len - edi arr1 - esi arr2 - edx arr3 = ecx
    
    mov r8d, ecx
    mov ecx, edi

    myloop:
        mov r9d, [esi + 4 * ecx - 4]
        add r9d, [edx + 4 * ecx - 4]
        mov [r8d + 4 * ecx - 4], r9d

    loop myloop

    ret
