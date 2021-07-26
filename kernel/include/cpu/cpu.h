#ifndef _CPU_H_
#define _CPU_H_

#include <error/syserror.h>
#include <cpu/system.h>
#include <cpu/features.h>

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

typedef struct{
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
}cpuid_registers;

#define AMD_VENDOR "AuthenticAMD"
#define INTEL_VENDOR "GenuineIntel"

#define AMD 0
#define INTEL 1

void cpuid(volatile cpuid_registers *registers);
SYS_ERROR CPU_init();
uint64_t rdmsr(uint32_t msr_address);
void wrmsr(uint32_t msr_address, uint64_t write);
#endif