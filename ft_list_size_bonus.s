global ft_list_size
section .text
; **************     int ft_list_size(t_list *begin_list)     **************
; [rdi] == begin_list->data
; [rdi + 8] == begin_list->next
; typedef struct s_list
; {
;     void            *data;
;     struct s_list   *next;
; }   t_list;
ft_list_size:
    xor rax, rax            ; rax = result = 0
.loop:
    ; if begin_list == NULL, return
    test rdi, rdi
    je .end

    mov rdi, qword [rdi + 8]      ; begin_list = begin_list->next
    inc rax                 ; result += 1
    jmp .loop
.end:
    ret