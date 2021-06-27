#ifndef _R_COMMON_H_
#define _R_COMMON_H_

#include <rtypes.h>

uint64_t ralign(uint64_t value, uint64_t boundary);
uint64_t ralign_op(uint64_t val, uint64_t alignment);
boolean alignmentcheck(size_t alignment);

void swap(size_t *address_1, size_t* address_2, size_t swap_size);
void swap_op8(size_t *address_1, size_t *address_2);
void swap_op(size_t *address_1, size_t *address_2);

void quick_sort(void *list, size_t list_size, void *mem_address, size_t struct_size);


#endif