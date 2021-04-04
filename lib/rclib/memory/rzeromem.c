#include <rmemory.h>

void rzeromem(void *block, size_t n)
{
    rmemset(block, 0, n);
}