#include <refilib/refilib.h>

void EFI_FATAL_REPORT(IN CHAR16 *ErrorMessage, IN EFI_STATUS status_code)
{

    if(EFI_ERROR(status_code))
    {    
        print_efi(L"FATAL ERROR:%s\r\n", ErrorMessage);
        print_efi(L"Status code:%d\r\n", stat_check(status_code));
        print_efi(L"Cannot continue execution\r\n");
        while(1)
        {}
    }
}