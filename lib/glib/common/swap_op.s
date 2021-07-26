.file "swap_op.s"
.global swap_op8, swap_op
.align 0x10

swap_op8:
    movq (%rcx), %rax
    xchgq (%rdx), %rax
    movq %rax, (%rcx) 
    ret
swap_op:
    movb (%rcx), %al
    xchgb (%rdx), %al
    movb %al, (%rcx)
    ret
    