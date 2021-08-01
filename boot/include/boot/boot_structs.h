#ifndef _BOOT_STRUCTS_H_
#define _BOOT_STRUCTS_H_

#include <refi/refi.h>
#include <boot/modules.h>

typedef struct {
    UINTN MapSize;
    UINTN DescSize;
    UINTN MapKey;
    UINT32 DescVer;
    EFI_MEMORY_DESCRIPTOR *Map;
}Map_descriptor;

typedef struct{
    boot_module* loaded_modules_array;
    Map_descriptor *Map;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *framebuffer;
    VOID *acpi;
    UINTN max_virtual_address;
}boot_info;

#endif