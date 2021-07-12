#include <glib/rstrings.h>

void rstrcpy(char *dest, char *src)
{
    u64 length = 0;
    while(src[length] != '\0')
    {
        dest[length] = src[length];
        length++;
    }
    dest[length] = '\0';
}