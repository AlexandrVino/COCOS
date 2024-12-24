.intel_syntax noprefix
.global _start
.data
    buffer:
        .fill 4096, 1, 0
.text
_start:
    mov rbx, 0  

loop:
    // read
    mov rax, 0
    mov rdi, 0
    lea rsi, [buffer]
    mov rdx, 4096
    syscall

    // read fails
    mov rbx, rax
    cmp rbx, -1
    je fail

    // read ends
    cmp rbx, 0
    je success

    // write
    mov rax, 1
    mov rdi, 1
    lea rsi, [buffer]
    mov rdx, rbx
    syscall

    // write fails
    cmp rax, -1
    je fail

    // loop
    jmp loop

success:
    mov rax, 60
    mov rdi, 0
    syscall
    jmp end

fail:
    mov rax, 60
    mov rdi, 1
    syscall
end:
