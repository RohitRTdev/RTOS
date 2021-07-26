#ifndef _BOOT_ERROR_H_
#define _BOOT_ERROR_H_

#include <refi/refi.h>

#define RETURN_ON_ERROR(error) { if(EFI_ERROR(error)) return error; }

#endif