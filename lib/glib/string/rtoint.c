#include <glib/rstrings.h>

i8 rtoint(char ch)
{
    i8 value;
    if(risdigit(ch))
    {
        value = ch - 48;
    }
    else
    {
        value = -1;
    }
    return value;
    
}