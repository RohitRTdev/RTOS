#ifndef _REFILIB_H_
#define _REFILIB_H_


#include <refi/refi.h>

extern EFI_SYSTEM_TABLE *ST;
extern EFI_BOOT_SERVICES *BS;
extern EFI_RUNTIME_SERVICES *RT;

/*Call this function before using any REFI library functions and also to have ST(Sytem Table), 
BS(Boot Services) and RT(Runtime Services) defined */
void init_lib(IN EFI_HANDLE image_handle,IN EFI_SYSTEM_TABLE* system_table);

//Print function accepts two tokens as of now, %s(string) and %d(64 bit unsigned integer)
EFI_STATUS print_efi(IN CHAR16 *string, ...);
EFI_STATUS efi_clearscreen();

//Function to report fatal EFI errors
void EFI_FATAL_REPORT(IN CHAR16 *ErrorMessage, IN EFI_STATUS status_code);

//Miscellaneous
BOOLEAN guid_check(EFI_GUID guid1, EFI_GUID guid2);
VOID copy_guid(EFI_GUID* src_guid, EFI_GUID* dest_guid)

#endif