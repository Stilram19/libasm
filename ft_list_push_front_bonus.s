global ft_list_push_front
section .text
extern malloc

; *********** void ft_list_push_front(t_list **begin_list, void *data) ***********
; rdi: pointer to the head of the linked list
; rsi: data of the new node that we need to create
; typedef struct s_list
; {
;     void            *data;
;     struct s_list   *next;
; }   t_list;
ft_list_push_front:
    ; validate arguments (no argument should be NULL)
    test rdi, rdi
    je .bad_argument
    test rsi, rsi
    je .bad_argument

    ; save argument into stack and align it
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov qword [rsp], rdi
    mov qword [rsp + 8], rsi

    ; allocate some memory for the new node
    mov edi, 16                     ; we need to allocate 16 byte block (sizeof(t_list))
    call malloc
    ; return if malloc failed
    test rax, rax
    je .bad_alloc

    ; restore stack (recover arguments)
    mov rdi, qword [rsp]
    mov rsi, qword [rsp + 8]
    add rsp, 16

    ; new_node->data = data
    mov qword [rax], rsi

    ; new_node->next = *begin_list
    mov rdx, qword [rdi]
    mov qword [rax + 8], rdx

    ; *begin_list = new_node
    mov qword [rdi], rax

    pop rbp
    ret

.bad_alloc:
    add rsp, 16
    pop rbp
    ret

.bad_argument:
    ret