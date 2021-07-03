#ifndef _BOOT_SETUP_H_
#define _BOOT_SETUP_H_

#include <refi/refi.h>
#include <boot/boot_structs.h>

VOID* getACPI2_0table();
EFI_STATUS getMemMap(Map_descriptor *MemMap);



#endif