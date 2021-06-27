#include <refi/refilib.h>

void rstrcat(char *dest, char *src)
{
    UINT64 destLength = rstrlen(dest);
    UINT64 length = 0;
    while(src[length] != '\0')
        dest[destLength++] = src[length++];
    dest[destLength] = '\0';

}