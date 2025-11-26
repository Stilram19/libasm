global ft_strdup
section .text
extern ft_strlen
extern ft_strcpy
extern malloc
ft_strdup:
    sub rsp, 8                  ; allocate stack space to save strdup's argument (stack is well aligned)
    mov [rsp], rdi              ; saving strdup's argument
    call ft_strlen              ; calculate the length of (const char *s), also stack is well aligned
    mov rdi, rax                ; rdi = len(s)
    inc rdi                     ; rdi += 1 (making room for '\0')
    call malloc wrt ..plt       ; allocate memory for the new string, also stack is well aligned
    test rax, rax               ; check malloc return value
    je .malloc_failed           ; return if malloc failed (malloc sets errno)
    mov rsi, [rsp]              ; passing the second argument for ft_strcpy (char *src) 
    mov rdi, rax                ; passing first argument for ft_strcpy (char *dest)
    call ft_strcpy              ; copy str into the newly allocated memory, also stack is well aligned
    add rsp, 8                  ; restore stack
    ret
.malloc_failed:
    add rsp, 8                  ; restore stack
    ret