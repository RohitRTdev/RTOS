#include <refilib/refilib.h>

void EFI_FATAL_REPORT(IN CHAR16 *ErrorMessage, IN EFI_STATUS status_code)
{
    if(EFI_ERROR(status_code))
    {    
        printEFI(L"FATAL ERROR:%s\r\n", ErrorMessage);
        printEFI(L"Status code:%d\r\n", stat_check(status_code));
        printEFI(L"Cannot continue execution\r\n");
        while(1)
        {}
    }
}