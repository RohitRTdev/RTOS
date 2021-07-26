#include <refilib/refilib.h>

BOOLEAN guid_check(EFI_GUID guid1, EFI_GUID guid2)
{
    UINTN j = 0;
    if(guid1.Data1 == guid2.Data1 && guid1.Data2 == guid2.Data2 && guid1.Data3 == guid2.Data3)
    {    while(guid1.Data4[j] == guid2.Data4[j] && j < 8)
            {j++;}
        if(j == 8)
            return TRUE;
    }
    return FALSE;
}