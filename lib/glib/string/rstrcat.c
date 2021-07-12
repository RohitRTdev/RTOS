#include <glib/rstrings.h>

void rstrcat(char *dest, char *src)
{
    u64 destLength = rstrlen(dest);
    u64 length = 0;
    while(src[length] != '\0')
        dest[destLength++] = src[length++];
    dest[destLength] = '\0';

}