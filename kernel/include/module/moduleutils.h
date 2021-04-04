#ifndef _MODULE_UTILS_H_
#define _MODULE_UTILS_H_

#include <mm/phyMemstructs.h>

#define MODULE_NAME_BUFFER_SIZE BLOCK_SIZE(4096)
#define MODULE_ID_BUFFER_SIZE BLOCK_SIZE(4096)
#define MODULE_INTERFACE_BUFFER_SIZE BLOCK_SIZE(4096)

typedef struct{
    uintptr_t module_name_block;
    uintptr_t module_id_block;
    uintptr_t module_interface_block; 
    uint64_t max_list_index;
}module_buffers;

#endif