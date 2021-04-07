#ifndef _PHY_MEM_TOOLS_H_
#define _PHY_MEM_TOOLS_H_

#include <kernel.h>
#include <error/syserror.h>
#include <mm/phyMemstructs.h>

#define ADDRESS_NOT_FOUND 0xffffffffffffffff

uint64_t phy_block_finder(Map_descriptor *map);

SYS_ERROR phy_set_blocks(Map_descriptor *map, Free_Mem_desc *base_address, uint64_t *no_of_desc, Super_Mem_desc *desc);
SYS_ERROR defrag_at_free(size_t block_address, size_t pages, Super_Mem_desc *global_desc);
SYS_ERROR smallest_fit(size_t* size, Super_Mem_desc *desc, void **block_address);
SYS_ERROR relocate_main_block(Super_Mem_desc *desc);

void init_free_blocks(Free_Mem_desc *mem, Super_Mem_desc *desc);
void phy_defrag(Super_Mem_desc *desc, Free_Mem_desc *block_address);
void set_allocation_algorithm(boolean allocation_algorithm);
void setup_AllocPool(AllocPoolHeader *block_ptr, uint64_t resc_size, boolean type, AllocPoolHeader *main_node);

#endif