global ft_strcmp
section .text
; int     ft_strcmp(const char *s1, const char *s2);

; s1 (rdi), s2 (rsi)
ft_strcmp:
    xor rax, rax                ; rax = 0 (clearing first temp)
    xor rdx, rdx                ; rdx = 0 (clearing second temp)
.loop:
    mov al, byte [rdi]          ; (byte)rax = *s1
    mov dl, byte [rsi]          ; (byte)rdx = *s2
    cmp al, dl                  ; compare *s1 and *s2
    jne .break                  ; break the loop if *s1 != *s2

    ; if *s1 == '\0' or *s2 == '\0', break the loop
    test al, al
    je .break
    test dl, dl
    je .break

    inc rdi                     ; s1 += 1
    inc rsi                     ; s2 += 1
    jmp .loop                   ; iterate
.break
    sub rax, rdx
    ret