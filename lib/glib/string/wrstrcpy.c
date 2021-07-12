#include <glib/rstrings.h>

void wrstrcpy(wchar_t *dest, wchar_t *src)
{
    uint64_t length = 0;
    while(src[length] != L'\0')
    {
        dest[length] = src[length];
        length++;
    }
    dest[length] = L'\0';
}