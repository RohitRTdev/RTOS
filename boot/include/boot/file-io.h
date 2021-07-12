#ifndef _FILE_IO_H_
#define _FILE_IO_H_
#include <refi/refi.h>

EFI_FILE_PROTOCOL* openfile(EFI_HANDLE deviceHandle, CHAR16 *filepath);
EFI_HANDLE file_init(EFI_HANDLE ImageHandle);

#endif