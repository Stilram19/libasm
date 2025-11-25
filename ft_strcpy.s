global ft_strcpy
section .text
; char    *strcpy(char *dest, const char *src)
; des (rdi), src (rsi)
ft_strcpy:
    mov rax, rdi            ; return value is the destination pointer (dest)
.loop:
    mov dl, byte [rsi]      ; (byte)rdx = *src
    mov byte [rdi], dl      ; *dest = *src    
    inc rdi                 ; dest += 1
    inc rsi                 ; src += 1
    test dl, dl             ; *src == '\0'
    jne .loop               ; iterate if *src != '\0'
    ret