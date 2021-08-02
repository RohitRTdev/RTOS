#ifndef _MODULES_H_
#define _MODULES_H_

#include <refi/refi.h>
#include <rtos/handoff.h>

#define MAX_BOOT_MODULES 10

extern boot_handoff* kernel_essentials;

typedef struct{
	UINT8 module_type;
	CHAR16* module_path;
	char* module_name;
}boot_time_modules;



EFI_STATUS init_boot_module(const boot_time_modules* bootloader_description, EFI_HANDLE image_handle, void* boot_module_entry);

EFI_STATUS load_boot_modules(const boot_time_modules* boot_time_loaded_modules, UINTN number_of_modules, EFI_HANDLE image_handle);

EFI_STATUS add_boot_module(const char* module_name, module_types module_type, const CHAR16* module_path, VOID* module_start, VOID* module_entry, UINT64 module_size, VOID* reloc_section, map_descriptor* map);

#endif
