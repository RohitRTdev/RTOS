#ifndef _PHY_MEM_TOOLS_H_
#define _PHY_MEM_TOOLS_H_

#include <error/syserror.h>
#include <mm/phyMemstructs.h>
#include <rtos/handoff.h>

#define ADDRESS_NOT_FOUND 0xffffffffffffffff

size_t* phy_block_finder(map_descriptor *map);

SYS_ERROR phy_set_blocks(map_descriptor *map, Super_Mem_desc *desc);
SYS_ERROR defrag_at_free(free_mem_desc *free_block, Super_Mem_desc *global_desc);
SYS_ERROR smallest_fit(size_t* size, Super_Mem_desc *desc, void **block_address);

void init_free_blocks(Super_Mem_desc *desc);
void phy_defrag(Super_Mem_desc *desc);
void setup_AllocPool(AllocPoolHeader *block_ptr, uint64_t resc_size, boolean type, AllocPoolHeader *main_node);

#endif