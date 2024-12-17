// Это комментарий, как в Си/С++
.global very_important_function
.intel_syntax noprefix
.extern A

.data 
    aliboba: 
        .quad 0
    nigger: 
        .string "%d"
    do_work: 
        .string "%lld "
.text  

very_important_function:     
    // len - edi 
    
    mov rcx, rdi
    mov r13, 0
    mov r12, A

    myloop:
        push rcx

        lea rdi, [nigger]
        lea rsi, [aliboba]
        mov rax, 0
        call scanf

        movsxd rax, [aliboba]
        
        movsxd r8, [r12 + 4 * r13]
        imul r8

        lea rdi, [do_work]
        mov rsi, rax

        mov rax, 0
        call printf

        inc r13
        pop rcx

    loop myloop

    ret
