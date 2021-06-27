#include <refi/refilib.h>

void wrstrcpy(CHAR16 *dest, CHAR16 *src)
{
    UINT64 length = 0;
    while(src[length] != L'\0')
    {
        dest[length] = src[length];
        length++;
    }
    dest[length] = L'\0';
}