#ifndef _PRIMARY_LOADER_H_
#define _PRIMARY_LOADER_H_

#include <refi/refi.h>

UINT64 round_4k(UINT64 value);  // Returns no.of pages
EFI_STATUS pe_loadfile(EFI_HANDLE image_handle, CHAR16* file_path);

#endif