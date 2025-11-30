global ft_atoi_base
extern ft_strlen
section .text


; ************ int ft_atoi_base(char *str, char *base) ************
; rdi (char *str), rsi (char *base)

ft_atoi_base:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov [rsp], rdi                      ; save first arg in stack (str)
    mov [rsp + 8], rsi                  ; save second arg in stack (base)

    ; call .validate_base(char *base)
    mov rdi, rsi                        ; passing 'char *base' as .validate_base's arg
    call .validate_base                 ; base validation (stack aligned)
    cmp rax, -1
    je .base_validation_error           ; return with error if .validate_base failed

    ; calculate base's length
    mov rdi, [rsp + 8]                  ; pass ft_strlen's argument (char *base)
    call ft_strlen                      ; ft_strlen(base)
    mov r8, rax                         ; r8 = ft_strlen(base)

    ; restore stack after functions calls
    mov rdi, [rsp]
    mov rsi, [rsp + 8]
    add rsp, 16

    xor r9, r9                          ; str_index = 0

.skip_spaces:
    mov cl, byte [rdi + r9]             ; (byte)clx = *(str + str_index)
    cmp cl, 0
    je .detect_sign                     ; if *(str + str_index) == '\0' go to '.detect_sign'

    ; check if it's a whitespace
    cmp cl, 32                          ; whitespace
    je .next_space
    cmp cl, 9
    jb .detect_sign
    cmp cl, 13
    jbe .next_space                     ; 9..13
    jmp .detect_sign                    ; go to .detect_sign if the current char is not a space
.next_space:
    inc r9                              ; str_index += 1
    jmp .skip_spaces

.detect_sign:
    mov r10, 1                          ; using r10 for sign (by default +1)
    mov cl, byte [rdi + r9]             ; (byte)clx = *(str + str_index)
    cmp cl, '+'
    je .skip_plus_sign
    cmp cl, '-'
    je .skip_minus_sign
    jmp .start
.skip_plus_sign:
    inc r9                              ; str_index += 1 (to skip the plus sign character)
    jmp .start
.skip_minus_sign:
    inc r9                              ; str_index += 1 (to skip the minus sign character)
    mov r10, -1                         ; sign = -1

.start:
    xor rax, rax                        ; rax = accum = result = 0
.outer_loop:
    mov cl, byte [rdi + r9]             ; (byte)clx = *(str + str_index)
    cmp cl, 0
    je .finished_parsing                ; return if *(str + str_index) == '\0'
    xor r11, r11                        ; base_index = 0
.inner_loop:
    cmp byte [rsi + r11], 0                  
    je .finished_parsing                ; return if the current str char is not found in the base 
    cmp cl, byte [rsi + r11]
    je .found_digit
    inc r11
    jmp .inner_loop
.found_digit:
    imul rax, r8                        ; rax *= r8 (r8 is the base length)
    add rax, r11                        ; rax += curr_digit
    inc r9                              ; str_index += 1
    jmp .outer_loop

.finished_parsing:
    imul rax, r10                       ; rax *= sign (- or +)
    pop rbp
    ret

.base_validation_error:
    add rsp, 16                         ; restore stack
    pop rbp
    xor rax, rax                        ; return value is 0, to indicate error
    ret


; ************ int _validate_base(const char *base) ************ 
; rdi (const char *base)
; returns 0 if base is valid, -1 otherwise
.validate_base:
    sub rsp, 8                          ; allocating stack space
    mov [rsp], rdi                      ; saving _validate_base's argument (const char *base)

    ; ensure len(base) > 1
    call ft_strlen                      ; calculating base length (stack is well aligned)
    cmp rax, 1
    jbe .length_error                   ; return with error if len(base) <= 1

    mov rdi, [rsp]                      ; recover argument (const char *base) from stack
    add rsp, 8                          ; restore stack

    ; ensure all characters are printable, except '+', '-' and whitespaces
    xor rsi, rsi                        ; index = 0
.check_printable_loop:
    mov cl, byte [rdi + rsi]            ; (byte)rcx = *(base + index)
    ; printable check (whitespaces are excluded)
    cmp cl, 33
    jb .base_error
    cmp cl, 126
    ja .base_error
    ; '+', '-' check
    cmp cl, 43
    je .base_error
    cmp cl, 45
    je .base_error
    inc rsi                             ; index += 1
    cmp rsi, rax
    jb .check_printable_loop            ; iterate if index < len(base)

; ensure there are no duplicates
.check_duplicate:
    xor rsi, rsi                        ; outer_index = 0
.duplicate_outer_loop:
    mov cl, byte [rdi + rsi]            ; (byte)rcx = *(base + outer_index)
    xor rdx, rdx                        ; inner_index = 0
.duplicate_inner_loop:
    cmp rdx, rsi                        ; only comparisons of elements with different indices is valid
    je .duplicate_inner_next            ; if both indices are the same, increment index and loop again
    cmp cl, byte [rdi + rdx]
    je .base_error                      ; return with error if a duplicate is detected
.duplicate_inner_next:
    inc rdx                             ; inner_index += 1
    cmp rdx, rax
    jb .duplicate_inner_loop            ; iterate if inner_index < len(base)

    ; back to outer loop
    inc rsi
    cmp rsi, rax
    jb .duplicate_outer_loop            ; loop while outer_index < len(base)
    xor rax, rax                        ; return value is 0 (success)
    ret
.length_error:
    add rsp, 8
    mov rax, -1                         ; return value is -1 (error)
    ret
.base_error:
    mov rax, -1                         ; return value is -1 (error)
    ret