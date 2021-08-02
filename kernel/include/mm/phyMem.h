#ifndef _PHY_MEM_H_
#define _PHY_MEM_H_

#include <error/syserror.h>
#include <rtos/handoff.h>

SYS_ERROR phyMem_init(map_descriptor *MemMap);
SYS_ERROR AllocMem(size_t *size, void **buffer); //AllocMem always gives a PAGESIZE aligned pointer 
SYS_ERROR FreeMem(void *buffer);
SYS_ERROR ReAllocMem(size_t *size, void **buffer);
SYS_ERROR AllocPool(size_t resc_size, void **buffer, size_t *pool_id);
SYS_ERROR FreePool(void *buffer, size_t *pool_id);

void add_free_mem_entry(size_t size, size_t address);
void add_allocated_mem_entry(size_t size, size_t address);

#endif