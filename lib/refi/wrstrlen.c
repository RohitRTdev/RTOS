#include <refi/refilib.h>

UINT64 wrstrlen(CHAR16 *str)
{
    UINT64 length = 0;
    while(str[length] != L'\0')
    {
        length++;
    }
    return length;
}
