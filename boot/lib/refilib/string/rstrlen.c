#include <refilib/refilib.h>

UINT64 rstrlen(char *str)
{
    UINT64 length = 0;
    while(str[length] != '\0')
    {
        length++;
    }
    return length;
}