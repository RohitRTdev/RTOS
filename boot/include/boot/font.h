#ifndef __BASIC_FONT_H__
#define __BASIC_FONT_H__


#include <refi/refi.h>
#include <refilib/refilib.h>
#include <boot/boot_structs.h>
#include <boot/modules.h>


EFI_STATUS psf_font_load(EFI_HANDLE image_handle, boot_time_modules* font_module);

#endif