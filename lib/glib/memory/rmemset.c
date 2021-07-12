#include <glib/rmemory.h>


void* rmemset(void *block, i8 c, st n)
{
    st i = 0;
    while(i < n)
    {
        *BYTE_CAST(block + i++) = c;
    }
    return block;
}

