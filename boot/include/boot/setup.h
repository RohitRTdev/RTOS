#ifndef _BOOT_SETUP_H_
#define _BOOT_SETUP_H_

#include <rtos/handoff.h>
#include <refilib/refilib.h>
#include <boot/modules.h>

typedef void (*entry_point)(boot_handoff* kernel_essentials, EFI_SYSTEM_TABLE* system_table);

extern UINTN mapkey;
extern entry_point kernel_entry;

VOID* get_ACPI2_0_table();
EFI_STATUS get_mem_map(const boot_time_modules* system_map_descriptor);
EFI_STATUS setup_gop();


#endif