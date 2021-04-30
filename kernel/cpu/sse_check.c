#include <cpu/cpu.h>

uint8_t sse_check()
{
    cpuid_registers registers = {1, 0, 0, 0};
    uint8_t SSE_version = 0;
    cpuid(&registers);

    if(registers.edx & (1 << 25))
        SSE_version = 10;
    if(registers.edx & (1 << 26))
        SSE_version = 20;
    if(registers.ecx & 1)
        SSE_version = 30;
    if(registers.ecx & (1 << 9))
        SSE_version = 31;
    if(registers.ecx & (1 << 19))
        SSE_version = 41;
    if(registers.ecx & (1 << 20))
        SSE_version = 42;

    return SSE_version;
}
