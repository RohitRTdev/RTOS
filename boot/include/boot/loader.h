#ifndef _LOADER_H_
#define _LOADER_H_

#include <refi/refi.h>
#include <boot/modules.h>

EFI_STATUS load_kernel_font(const boot_time_modules* font, EFI_HANDLE device_handle);
EFI_STATUS rt_loadfile(EFI_HANDLE device_handle, const boot_time_modules* kernel_font);


#endif