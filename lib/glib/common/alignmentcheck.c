#include <glib/rcommon.h>

boolean alignmentcheck(size_t alignment)
{
    size_t count = 0;
    boolean bit_check = false;
    while(count < 64)
    {
        if(alignment & ((size_t)1 << count))
        {
            if(!bit_check)
            {
                bit_check = true;
            }        
            else
            {
                break;
            }
               
        }    
        count++;
    }
    if(count == 64)
    {
        return true;
    }    
    else
    {
        return false;
    }
       
}