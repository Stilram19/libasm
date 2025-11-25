global ft_strlen
section .text

ft_strlen:
    xor rax, rax                ; offset = 0
.loop:
    cmp byte [rdi + rax], 0     ; *(byte *)(base + offset) == '\0'
    je .end                     ; return if '\0' is reached
    inc rax                     ; offset += 1
    jmp .loop
.end:
    ret