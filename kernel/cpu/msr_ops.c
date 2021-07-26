#include <cpu/cpu.h>

uint64_t rdmsr(uint32_t msr_address)
{
    uint32_t eax, edx;
    uint64_t res;
    asm("movl %[address], %%ecx\t\n"
        "rdmsr \t\n"
        :"=a"(eax), "=d"(edx)
        :[address]"m"(msr_address));

    res = ((uint64_t)edx << 32)|((uint64_t)eax);
    return res;         
}

void wrmsr(uint32_t msr_address, uint64_t write)
{
    uint32_t edx = write >> 32;
    uint32_t eax = write;
    asm("movl %[address], %%ecx\t\n"
        "movl %[upper32], %%eax\t\n"
        "movl %[lower32], %%edx\t\n"
        "wrmsr\t\n"
        ::[address]"m"(msr_address), [upper32]"m"(eax), [lower32]"m"(edx));
}