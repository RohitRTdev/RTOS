#ifndef _FILE_IO_H_
#define _FILE_IO_H_
#include <refi/refi.h>

EFI_FILE_PROTOCOL* openfile(EFI_HANDLE deviceHandle, CHAR16 *filepath);
EFI_HANDLE get_device_handle(EFI_HANDLE ImageHandle);
VOID read_simple_file(EFI_FILE_PROTOCOL* file_handle, UINTN read_offset, UINTN read_size, VOID* read_buffer);

#endif