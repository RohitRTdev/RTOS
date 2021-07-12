#include <glib/rstrings.h>

bool risdigit(char ch)
{
    if(ch >= '0' && ch <= '9')
        return true;
    else
    {
        return false;
    }
    
}