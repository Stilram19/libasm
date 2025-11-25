extern __errno_location
global ft_read
section .text

ft_read:
    mov rax, 0                          ; read system call
    syscall                             ; perform system call (arguments are already passed by the caller)
    cmp rax, 0                          ; check the status of the system call
    jge .done                           ; jump to .done label if the system call was successful
    mov rdi, rax                        ; use rdi as a temp (rax will be overriden in the next call)
    neg rdi                             ; rdi now has the value 'errno'
    call __errno_location  wrt ..plt    ; get the location of the current thread-local errno
    mov [rax], rdi                      ; *ptr_to_errno = errno_value
    mov rax, -1                         ; set the returned value to -1 to indicate error
.done:
    ret