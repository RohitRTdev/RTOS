#include <rmemory.h>

void* rmemcpy(void *dest, const void *src, size_t n)
{    
    size_t i = 0;
    while(i < n)
    {
        *BYTE_CAST(dest + i) = *BYTE_CAST(src + i);
        i++;
    }
    return dest;
}