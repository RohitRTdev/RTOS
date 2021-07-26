#include <cpu/cpu.h>

void cpuid(volatile cpuid_registers *registers)
{
    volatile uint32_t *eax = &registers->eax;
    volatile uint32_t *ebx = &registers->ebx;
    volatile uint32_t *ecx = &registers->ecx;
    volatile uint32_t *edx = &registers->edx;
    __asm__ (
         "CPUID \n\t"
        : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)   
        : "a"(*eax)                                           
    );
}