#include <rstrings.h>

void reverse_str(char *str)
{
    uint64_t length = rstrlen(str);
    char hold;
    for(uint64_t index = 0;index < length / 2; index++)
    {
        hold = str[index];  
        str[index] = str[length - index - 1];
        str[length - index - 1] = hold;
    }
}