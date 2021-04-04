.file "ralign_op.s"
.global ralign_op
.align 0x10

ralign_op:
    sub   $1, %rdx
    add %rdx, %rcx
    not %rdx
    and %rdx, %rcx
    mov %rcx, %rax
    ret
