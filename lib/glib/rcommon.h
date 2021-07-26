#ifndef _GLIB_R_COMMON_H_
#define _GLIB_R_COMMON_H_

#include <rtos/rtypes.h>

uint64_t ralign(uint64_t value, uint64_t boundary);
uint64_t ralign_op(uint64_t val, uint64_t alignment);
boolean alignmentcheck(size_t alignment);
boolean verify_function_pointers(void** params_array, size_t number_of_params);

void swap(size_t *address_1, size_t* address_2, size_t swap_size);
void swap_op8(size_t *address_1, size_t *address_2);
void swap_op(size_t *address_1, size_t *address_2);

void quick_sort(void *lisize_t, size_t lisize_t_size, void *mem_address, size_t size_truct_size);


#endif