#ifndef _PHY_MEM_H_
#define _PHY_MEM_H_

#include <kernel.h>
#include <error/syserror.h>

SYS_ERROR phyMem_init(Map_descriptor *MemMap);
SYS_ERROR AllocMem(size_t *size, void **buffer);
SYS_ERROR FreeMem(void *buffer);
SYS_ERROR ReAllocMem(size_t *size, void **buffer);

void allocation_algorithm(boolean algorithm);
void add_free_mem_entry(size_t size, void *address);

#endif