#include <refilib/refilib.h>

EFI_SYSTEM_TABLE *ST;
EFI_BOOT_SERVICES *BS;
EFI_RUNTIME_SERVICES *RT;

void init_lib(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
    ST = system_table;
    BS = system_table->BootServices;
    RT = system_table->RuntimeServices;
}