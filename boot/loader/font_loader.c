#include <boot/loader.h>
#include <boot/font.h>


EFI_STATUS load_kernel_font(const boot_time_modules* kernel_font, EFI_HANDLE device_handle)
{
	/* Call each of the font loaders available to see who supports this font */
	EFI_STATUS font_load_status = EFI_SUCCESS;

	font_load_status = psf_font_load(device_handle, kernel_font);

	return font_load_status;
}

