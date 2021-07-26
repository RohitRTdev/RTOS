#ifndef _VIRTUAL_MEM_H_
#define _VIRTUAL_MEM_H_

SYS_ERROR virtual_mem_init();
SYS_ERROR virtualMap(void *Physical_address, void *Virtual_address, size_t SizeToMap);
SYS_ERROR virtualUnMap(void *VirtualAddress, size_t MappedLength);
SYS_ERROR virtualAllocKernel(size_t bufSize, void **VirtualAddress);

#endif