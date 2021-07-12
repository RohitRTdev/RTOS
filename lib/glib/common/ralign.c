#include <glib/rcommon.h>

uint64_t ralign(uint64_t value, uint64_t boundary)
{
    uint64_t res;
    if(value % boundary != 0)
        res = (value/boundary + 1) * boundary;
    else
    {
        res = value;
    }
    
        return res;
}

