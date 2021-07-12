#include <glib/rmemory.h>

void rzeromem(void *block, st n)
{
    rmemset(block, 0, n);
}