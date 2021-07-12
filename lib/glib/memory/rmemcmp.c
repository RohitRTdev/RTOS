#include <glib/rmemory.h>


i8 rmemcmp(const void *block1, const void *block2, st n)
{
    st i = 0;
    while(i < n)
    {
        if(*BYTE_CAST(block1 + i) != *BYTE_CAST(block2 + i))
            break;
        i++;
    }
    if(i != n)
    {
        if(*BYTE_CAST(block1 + i) > *BYTE_CAST(block2 + i))
            return 1;
        else 
            return -1;
    }
    else
    {
        return 0;
    }
    
}