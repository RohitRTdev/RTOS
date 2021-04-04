#include <cpu/cpu.h>

uint8_t sse_check()
{
    uint32_t edx = 0, ecx = 0, eax = 1, ebx = 0;
    uint8_t SSE_version = 0;
    cpuid(&eax, &ebx, &ecx, &edx);

    if(edx & (1 << 25))
        SSE_version = 10;
    if(edx & (1 << 26))
        SSE_version = 20;
    if(ecx & 1)
        SSE_version = 30;
    if(ecx & (1 << 9))
        SSE_version = 31;
    if(ecx & (1 << 19))
        SSE_version = 41;
    if(ecx & (1 << 20))
        SSE_version = 42;

    return SSE_version;
}
