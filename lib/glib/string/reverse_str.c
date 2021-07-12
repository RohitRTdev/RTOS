#include <glib/rstrings.h>

void reverse_str(char *str)
{
    u64 length = rstrlen(str);
    char hold;
    for(u64 index = 0;index < length / 2; index++)
    {
        hold = str[index];  
        str[index] = str[length - index - 1];
        str[length - index - 1] = hold;
    }
}