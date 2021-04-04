#ifndef _PRIMARY_LOADER_H_
#define _PRIMARY_LOADER_H_

#include "refi.h"

typedef struct{
    UINT8 *entry_point;
    UINT8 *base;
    UINT64 pages;
}Image_data;


UINT64 round_4k(UINT64 value);  // Returns no.of pages
UINT8* pe_loadfile(EFI_HANDLE ImageHandle, CHAR16* filepath, Image_data *image);
EFI_FILE_PROTOCOL* openfile(EFI_HANDLE deviceHandle, CHAR16 *filepath);
EFI_HANDLE file_init(EFI_HANDLE ImageHandle);

#endif