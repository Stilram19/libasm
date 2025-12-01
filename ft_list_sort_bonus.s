global ft_list_sort
section .text

; *********** void ft_list_sort(t_list **begin_list, int (*cmp)()) ***********
; rdi: pointer to the head of the linked list
; rsi: pointer to the compare function used in sorting
; typedef struct s_list
; {
;     void            *data;
;     struct s_list   *next;
; }   t_list;

ft_list_sort:
    ; parameters validation (no parameter should be NULL)
    test rdi, rdi
    je .bad_parameter
    cmp qword [rdi], 0
    je .bad_parameter
    test rsi, rsi
    je .bad_parameter

    ; saving callee saved registers
    push rbp
    push rbx
    push r12
    push r13
    push r14
    push r15
    sub rsp, 8                               ; align the stack

    mov rbx, rdi                             ; rbx = first parameter
    mov r12, rsi                             ; r12 = second parameter

    mov r15, 1                               ; swapped = true (default)
.outer_loop:
    ; if no swap happened in .inner_loop, the list is sorted => go to .end
    test r15, r15
    je .end

    xor r15, r15                            ; swapped = false
    mov r13, qword [rbx]                    ; curr = *begin_list
.inner_loop:
    ; if curr->next == NULL go to .outer_loop
    mov r14, qword [r13 + 8]                ; next = curr->next
    test r14, r14
    je .outer_loop

    ; compare curr->data and next->data
    mov rdi, qword [r13]                    ; first parameter is curr->data
    mov rsi, qword [r14]                    ; second parameter is next->data
    call r12

    ; checking comparison's result
    cmp eax, 0                              ; attention!! return value is in eax not rax
    jle .no_swap
.swap:
    ; swap curr->data and next->data
    mov r10, qword [r13]
    mov r11, qword [r14]
    mov qword [r13], r11
    mov qword [r14], r10

    mov r15, 1                              ; swapped = true
    mov r13, qword [r13 + 8]                ; curr = curr->next
    jmp .inner_loop
.no_swap:
    mov r13, qword [r13 + 8]                ; curr = curr->next
    jmp .inner_loop

.bad_parameter:
    ret

.end:
    ; restore stack
    add rsp, 8
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret