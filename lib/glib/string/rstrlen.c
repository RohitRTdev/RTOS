#include <glib/rstrings.h>

uint64_t rstrlen(char *str)
{
    uint64_t length = 0;
    while(str[length] != '\0')
    {
        length++;
    }
    return length;
}