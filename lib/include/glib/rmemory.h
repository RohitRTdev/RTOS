#ifndef _GLIB_R_MEMORY_H_
#define _GLIB_R_MEMORY_H_

#include <rtos/rtypes.h>

#define BYTE_CAST(operand) ((uint8_t*)operand)

void* rmemcpy(void *dest, const void *src, size_t n);
int8_t rmemcmp(const void *block1, const void *block2, size_t n);
void* rmemset(void *block, int8_t value, size_t n);
void rzeromem(void *block, size_t n);

#endif