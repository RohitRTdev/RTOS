#include <refi/refilib.h>

VOID refizeromem(VOID *dest, UINT64 size_to_copy)
{
    UINT8 *dest_ptr = dest;
    UINT64 index = 0;
    while(index < size_to_copy)
    {
        dest_ptr[index++] = 0;
    }
}