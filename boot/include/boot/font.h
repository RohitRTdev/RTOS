#ifndef __BASIC_FONT_H__
#define __BASIC_FONT_H__


#include <refi/refi.h>
#include <refilib/refilib.h>
#include <boot/modules.h>


EFI_STATUS psf_font_load(EFI_HANDLE image_handle, const boot_time_modules* font_module);

#endif