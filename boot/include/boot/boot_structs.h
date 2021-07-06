#ifndef _BOOT_STRUCTS_H_
#define _BOOT_STRUCTS_H_

#include <refi/refi.h>
#include "primary_loader.h"

//boot structs
#define STACK_SIZE 10*PAGESIZE 
#define RT_STACK 0x80000000
#define RT_MODULE 0x80000001
#define RT_MAP 0x80000002
#define RT_RCS 0x80000003


typedef struct{
    UINT8* basic_font_base;
    UINT64 basic_font_size;
}basic_font_info;

typedef struct{
    UINT8 *stack_top;
    UINT64 stack_size;
}stack_info;

typedef struct {
    UINTN MapSize;
    UINTN DescSize;
    UINTN MapKey;
    UINT32 DescVer;
    EFI_MEMORY_DESCRIPTOR *Map;
}Map_descriptor;

typedef struct{
    Map_descriptor *Map;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *framebuffer;
    Image_data *image;
    void *acpi;
    basic_font_info basic_font_base;
    stack_info stack;
    UINTN max_virtual_address;
}boot_info;

#endif