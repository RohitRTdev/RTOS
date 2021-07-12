#include <glib/rmemory.h>

void* rmemcpy(void *dest, const void *src, st n)
{    
    st i = 0;
    while(i < n)
    {
        *BYTE_CAST(dest + i) = *BYTE_CAST(src + i);
        i++;
    }
    return dest;
}