#include <glib/rmemory.h>


void* rmemset(void *block, int8_t c, size_t n)
{
    size_t i = 0;
    while(i < n)
    {
        *BYTE_CAST(block + i++) = c;
    }
    return block;
}

