#include <glib/rstrings.h>

u64 wrstrlen(wchar *str)
{
    u64 length = 0;
    while(str[length] != '\0')
    {
        length++;
    }
    return length;
}
