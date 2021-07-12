#ifndef _R_MEMORY_H_
#define _R_MEMORY_H_

#include "glib-types.h"

#define BYTE_CAST(operand) ((u8*)operand)

void* rmemcpy(void *dest, const void *src, st n);
i8 rmemcmp(const void *block1, const void *block2, st n);
void* rmemset(void *block, i8 value, st n);
void rzeromem(void *block, st n);

#endif