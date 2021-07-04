#include <refilib.h>

EFI_STATUS EFI_clearscreen()
{
    EFI_STATUS status;
    status = ST->ConOut->ClearScreen(ST->ConOut);
    return status;
}