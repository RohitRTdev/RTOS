#include <glib/rstrings.h>

void rstrcat(char *dest, char *src)
{
    uint64_t destLength = rstrlen(dest);
    uint64_t length = 0;
    while(src[length] != '\0')
        dest[destLength++] = src[length++];
    dest[destLength] = '\0';

}