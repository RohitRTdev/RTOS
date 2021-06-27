#include <refi/refilib.h>
EFI_SYSTEM_TABLE *ST;
EFI_BOOT_SERVICES *BS;
EFI_RUNTIME_SERVICES *RT;

void InitLib(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    ST = SystemTable;
    BS = SystemTable->BootServices;
    RT = SystemTable->RuntimeServices;
}