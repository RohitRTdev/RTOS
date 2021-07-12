#include <boot/loader.h>

EFI_STATUS load_kernel_font(boot_time_modules* kernel_font, EFI_HANDLE image_handle)
{
	/* Call each of the font loaders available to see who supports this font */
	EFI_STATUS font_load_status = EFI_SUCCESS;

	font_load_status = basic_font_load(image_handle, kernel_font->module_path);

	return font_load_status;
}

EFI_STATUS load_kernel_module(boot_time_modules* kernel_module, EFI_HANDLE image_handle)
{
	
}