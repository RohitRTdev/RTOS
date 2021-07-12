#include <glib/rstrings.h>

void wrstrcat(wchar_t *dest, wchar_t *src)
{
    uint64_t destLength = wrstrlen(dest);
    uint64_t length = 0;
    while(src[length] != L'\0')
        dest[destLength++] = src[length++];
    dest[destLength] = L'\0';

}