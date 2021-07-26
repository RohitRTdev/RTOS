#include <glib/rstrings.h>

uint64_t wrstrlen(wchar_t *str)
{
    uint64_t length = 0;
    while(str[length] != L'\0') /*Since UNICODE is 2bytes */
    {
        length++; 
    }
    return length;
}
