#ifndef _GLOBAL_HANDOFF_H_
#define _GLOBAL_HANDOFF_H_

#include <rtos/rtypes.h>

typedef struct {
	uint8_t* module_name;
	size_t module_size;
	void* module_start;
	uint8_t module_type;
	union {
		void* module_entry;
		struct{
			void* module_entry;
			void* reloc_section;
		}kernel;
	};
}boot_module;



#endif