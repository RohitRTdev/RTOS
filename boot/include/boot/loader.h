#ifndef _LOADER_H_
#define _LOADER_H_

#include <refi/refi.h>
#include <boot/modules.h>

EFI_STATUS load_kernel_module(boot_time_modules* kernel_module, EFI_HANDLE image_handle);
EFI_STATUS rt_loadfile(EFI_HANDLE device_handle, boot_time_modules* kernel_font);


#endif