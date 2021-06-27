#include <refi/refilib.h>

void wrstrcat(CHAR16 *dest, CHAR16 *src)
{
    UINT64 destLength = wrstrlen(dest);
    UINT64 length = 0;
    while(src[length] != L'\0')
        dest[destLength++] = src[length++];
    dest[destLength] = L'\0';

}