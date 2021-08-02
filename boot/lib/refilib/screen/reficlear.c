#include <refilib/refilib.h>

EFI_STATUS efi_clearscreen()
{
    EFI_STATUS status;
    status = ST->ConOut->ClearScreen(ST->ConOut);
    return status;
}