#define UNICODE
#include <rstrings.h>

void wrstrcat(wchar_t *dest, wchar_t *src)
{
    uint64_t destLength = crstrlen(dest);
    uint64_t length = 0;
    while(src[length] != RTEXT('\0'))
        dest[destLength++] = src[length++];
    dest[destLength] = RTEXT('\0');

}