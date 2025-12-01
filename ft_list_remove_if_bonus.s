global ft_list_remove_if
section .text
extern free

; void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *))
; rdi (begin_list)
; rsi (data_ref)
; rdx (cmp)
; rcx (free_fct)
; typedef struct s_list
; {
;     void            *data;
;     struct s_list   *next;
; }   t_list;
ft_list_remove_if:
    ; parameters validation (no parameter should be NULL)
    test rdi, rdi
    je .bad_parameter
    cmp qword [rdi], 0
    je .bad_parameter
    test rsi, rsi
    je .bad_parameter
    test rdx, rdx
    je .bad_parameter
    test rcx, rcx
    je .bad_parameter

    ; save callee saved registers & allocate stack space
    push rbp
    push rbx
    push r12
    push r13
    push r14
    push r15
    sub rsp, 24                     ; 16 * 1 + 8 (allocate stack space & align stack)

    mov rbx, 0                      ; prev = NULL
    mov r12, qword [rdi]            ; curr = *begin_list

    ; save the first two parameters into callee saved registers
    mov r14, rdi
    mov r15, rsi

.loop:
    ; if curr == NULL break
    test r12, r12
    je .end

    mov r13, qword [r12 + 8]        ; next = curr->next

    ; compare curr->data and data_ref

    ; save 3rd and 4th parameters
    mov qword [rsp], rdx
    mov qword [rsp + 8], rcx
    ; call cmp
    mov rdi, qword [r12]            ; first parameter (curr->data)
    mov rsi, r15                    ; second parameter (data_ref)
    call rdx
    ; recover 3rd and 4th parameters
    mov rdx, qword [rsp]
    mov rcx, qword [rsp + 8]

    test rax, rax
    je .equal_comparison
    jmp .not_equal_comparison
.equal_comparison:

    ; call free_fct

    ; save 3rd and 4th parameters
    mov qword [rsp], rdx
    mov qword [rsp + 8], rcx
    mov rdi, qword [r12]            ; parameter (curr->data)
    call rcx

    ; free(curr)
    mov rdi, r12                    ; parameter (curr)
    call free wrt ..plt

    ; recover 3rd and 4th parameters
    mov rdx, qword [rsp]
    mov rcx, qword [rsp + 8]

    ; if prev == NULL remove_head, otherwise remove_from_middle
    test rbx, rbx
    je .remove_head
    jmp .remove_middle
.remove_head:
    mov qword [r14], r13            ; *begin_list = next (remove head)
    mov r12, r13                    ; curr = next
    jmp .loop
.remove_middle:
    mov qword [rbx + 8], r13        ; prev->next = next (remove from middle)
    mov r12, r13                    ; curr = next
    jmp .loop

.not_equal_comparison:
    mov rbx, r12                    ; prev = curr
    mov r12, r13                    ; curr = next
    jmp .loop

.end:
    add rsp, 24
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret

.bad_parameter:
    ret