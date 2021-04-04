#include <cpu/cpu.h>

void cpuid(volatile uint32_t *eax,volatile uint32_t *ebx,volatile uint32_t *ecx,volatile uint32_t *edx)
{
    __asm__ (
         "CPUID \n\t"
        : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)   
        : "a"(*eax)                                           
    );
}