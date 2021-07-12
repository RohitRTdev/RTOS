#include <glib/rcommon.h>

bool alignmentcheck(st alignment)
{
    st count = 0;
    bool bit_check = false;
    while(count < 64)
    {
        if(alignment & ((st)1 << count))
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