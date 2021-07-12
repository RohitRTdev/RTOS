#ifndef _MODULES_H_
#define _MODULES_H_

#include <refi/refi.h>

#define MODULE_MAX 10

#define KERNEL 1
#define	STACK 2
#define FONT 3

typedef struct{
	UINT8 module_type;
	CHAR16* module_path;
	CHAR8* module_name;
}boot_time_modules;


typedef struct {
	char module_name[10];
	UINT8 module_id;
	UINT64 module_size;
	VOID* module_start;
	UINT8 module_type;
	union{
		struct{
			VOID* module_entry;
			VOID* reloc_section;
		}kernel;
	};
}boot_module;


//Kernel module entry function signatures
typedef void (*kernel)(boot_info*);


EFI_STATUS load_boot_modules(boot_time_modules* boot_time_loaded_modules, UINT64 number_of_modules);

UINT8 create_boot_module(CHAR8* ModuleName, UINT8 ModuleType, VOID* ModuleEntry, UINT64 ModuleSize, VOID* ModuleStart, VOID* ModuleReloc);

#endif