.file "system_ops.s"
.global _cr_0, _cr_2, _cr_3, _cr_4, _cr_8
.section .text
.align 0x10
_cr_0:
    cmp $0, %rdx
    je _cr_0_read
    jmp _cr_0_write

_cr_0_read:
    mov %cr0, %rax
    ret
_cr_0_write:
    mov %rcx, %cr0
    ret

_cr_2:
    cmp $0, %rdx
    je _cr_2_read
    jmp _cr_2_write

_cr_2_read:
    mov %cr2, %rax
    ret
_cr_2_write:
    mov %rcx, %cr2
    ret

_cr_3:
    cmp $0, %rdx
    je _cr_3_read
    jmp _cr_3_write

_cr_3_read:
    mov %cr3, %rax
    ret
_cr_3_write:
    mov %rcx, %cr3
    ret
_cr_4:
    cmp $0, %rdx
    je _cr_4_read
    jmp _cr_4_write

_cr_4_read:
    mov %cr4, %rax
    ret
_cr_4_write:
    mov %rcx, %cr4
    ret

_cr_8:
    cmp $0, %rdx
    je _cr_8_read
    jmp _cr_8_write

_cr_8_read:
    mov %cr8, %rax
    ret
_cr_8_write:
    mov %rcx, %cr8
    ret    
