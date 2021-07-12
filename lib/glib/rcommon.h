#ifndef _R_COMMON_H_
#define _R_COMMON_H_

#include "glib-types.h"

u64 ralign(u64 value, u64 boundary);
u64 ralign_op(u64 val, u64 alignment);
bool alignmentcheck(st alignment);

void swap(st *address_1, st* address_2, st swap_size);
void swap_op8(st *address_1, st *address_2);
void swap_op(st *address_1, st *address_2);

void quick_sort(void *list, st list_size, void *mem_address, st struct_size);


#endif