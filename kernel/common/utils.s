.file "utils.s"
.global _cli, _sti, load_gdt, store_gdt
.align 0x10
.section .text

_cli:
    cli
    ret
_sti:
    sti
    ret
load_gdt:
    lgdt (%rcx)
    ret
store_gdt:
    sgdt (%rcx)
    ret
    