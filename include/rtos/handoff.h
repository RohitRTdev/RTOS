#ifndef _GLOBAL_HANDOFF_H_
#define _GLOBAL_HANDOFF_H_

#include <rtos/rtypes.h>
#include <refi/refi.h>

typedef enum{
	KERNEL = 1,
	BOOTLOADER,
	STACK,
	FONT,
	MAP
}module_types;


typedef struct {
    size_t MapSize;
    size_t DescSize;
    size_t MapKey;
    uint32_t DescVer;
    EFI_MEMORY_DESCRIPTOR *Map;
}map_descriptor;



typedef struct {
	const char* module_name;
	size_t module_size;
	module_types module_type;
	void* module_start;

	union {
		struct {
			void* module_entry;
			void* reloc_section;
			const wchar_t* module_path;
		}rtmod;
		struct {
			size_t desc_size;
			size_t map_key;
			size_t desc_ver;
			EFI_MEMORY_DESCRIPTOR* system_memory_map;
		}map;
	};
}boot_module;

typedef struct {
	uint32_t h_res;
	uint32_t v_res;
	uint32_t pixels_per_scanline;
	EFI_GRAPHICS_PIXEL_FORMAT pixel_format;
	size_t framebuffer_base;
	size_t framebuffer_size;
}gop;

typedef struct {
	void* rsdp_table;
	gop display;
	size_t number_of_modules;
	boot_module loaded_modules[]; 
}boot_handoff;





#endif