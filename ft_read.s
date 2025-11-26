extern __errno_location
global ft_read
section .text

ft_read:
    mov rax, 0                          ; read system call
    syscall                             ; perform system call (arguments are already passed by the caller)
    cmp rax, 0                          ; check the status of the system call
    jge .end                            ; return label if the system call was successful
    mov rdi, rax                        ; rdi = rax (-errno_value)
    neg rdi                             ; rdi = errno_value
    sub rsp, 8                          ; making sure stack is well aligned before making a function call
    call __errno_location  wrt ..plt    ; get the location of the current thread-local errno
    add rsp, 8                          ; restore stack
    mov [rax], rdi                      ; *ptr_to_errno = rdi
    mov rax, -1                         ; set the returned value to -1 to indicate error
.end:
    ret