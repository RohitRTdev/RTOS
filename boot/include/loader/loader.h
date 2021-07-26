#ifndef _LOADER_H_
#define _LOADER_H_

#include <refi/refi.h>
#include <boot/modules.h>

EFI_STATUS load_kernel_module(boot_time_modules* kernel_module, EFI_HANDLE image_handle);
EFI_STATUS load_kernel_font(boot_time_modules* kernel_font, EFI_HANDLE image_handle);


#endif