#include <boot/modules.h>


EFI_STATUS load_boot_modules(boot_time_modules* boot_time_loaded_modules, UINT64 number_of_modules, EFI_HANDLE image_handle)
{
	if(boot_time_loaded_modules == NULL)
		return EFI_INVALID_PARAMETER;

	boot_time_modules* list_module = boot_time_loaded_modules; 

	EFI_STATUS load_time_error = EFI_SUCCESS;

	while(number_of_modules--)
	{
		switch(list_module->module_type)
		{
			case STACK:
			{
				load_time_error = init_kernel_stack();
				break;
			}
			case KERNEL:
			{
				load_time_error = load_kernel_module(&list_module, image_handle);
				break;
			}
			case FONT:
			{
				load_time_error = load_kernel_font(&list_module, image_handle);
			}
		}
		list_module++;
	}

	return load_time_error;
	
}