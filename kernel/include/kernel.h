#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <boot.h>

#define getMemMapDescriptor(ptr, size, pos) ((EFI_MEMORY_DESCRIPTOR*)((uint8_t*)ptr + size*pos))
#define PAGESIZE 4096 
#define ALIGN(val, alignment) ((val + alignment - 1) & ~(alignment - 1))

typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;


#endif