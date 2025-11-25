extern __errno_location
global ft_write
section .text
ft_write:
    mov rax, 1                      ; write system call
    syscall                         ; perform system call
    cmp rax, 0                      ; check syscall return status
    jge .end                        ; return if the syscall was successful
    mov rdi, rax                    ; rdi = rax (-errno_value)
    neg rdi                         ; rdi = errno_value
    call __errno_location wrt ..plt ; get the address of the thread-local errno
    mov [rax], rdi                  ; *ptr_to_errno = rdi
    mov rax, -1                     ; return value is -1 to indicate an error
.end:
    ret