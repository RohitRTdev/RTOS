#include <glib/rcommon.h>

u64 ralign(u64 value, u64 boundary)
{
    u64 res;
    if(value % boundary != 0)
        res = (value/boundary + 1) * boundary;
    else
    {
        res = value;
    }
    
        return res;
}

