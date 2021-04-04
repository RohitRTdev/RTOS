#ifndef _CPU_H_
#define _CPU_H_

#include <error/syserror.h>
#include <cpu/system.h>

 typedef struct{
    uint16_t physical_range: 8;
    uint16_t virtual_range: 8;
}cpu_range;

typedef struct{
    char vendor_string[13];

    uint64_t sse_version;
    uint64_t CPU;

    cpu_range cpu_range;

}processor_info;

#define AMD_VENDOR "AuthenticAMD"
#define INTEL_VENDOR "GenuineIntel"

#define AMD 0
#define INTEL 1

void cpuid(volatile uint32_t *eax,volatile uint32_t *ebx,volatile uint32_t *ecx,volatile uint32_t *edx);
SYS_ERROR CPU_init();

#endif