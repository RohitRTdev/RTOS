#include <glib/rstrings.h>

int8_t rtoint(char ch)
{
    int8_t value;
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