#include <rstrings.h>

void rstrcpy(char *dest, char *src)
{
    uint64_t length = 0;
    while(src[length] != RTEXT('\0'))
    {
        dest[length] = src[length];
        length++;
    }
    dest[length] = RTEXT('\0');
}