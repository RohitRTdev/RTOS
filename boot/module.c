#include <rtos/handoff.h>
#include <boot/modules.h>
#include <boot/stack.h>
#include <boot/error.h>
#include <boot/file.h>
#include <boot/loader.h>
#include <refilib/refilib.h>
#include <glib/array.h>
#include <glib/rcommon.h>


boot_module boot_modules[MAX_BOOT_MODULES];
primitive_array boot_modules_descriptor; 

EFI_STATUS init_boot_module(const boot_time_modules* bootloader_description, EFI_HANDLE image_handle, void* boot_module_entry)
{
	EFI_STATUS op_status = EFI_SUCCESS;

	if(!init_static_array(&boot_modules_descriptor, boot_modules, &boot_modules[0].module_type, MAX_BOOT_MODULES, sizeof(boot_module), 0))
		return KERNEL_LOAD_ERROR;

	EFI_LOADED_IMAGE_PROTOCOL* boot_module_interface = NULL;

	op_status = BS->HandleProtocol(image_handle, &(EFI_GUID)EFI_LOADED_IMAGE_PROTOCOL_GUID, &boot_module_interface);

	RETURN_ON_ERROR(op_status);

	op_status = add_boot_module(bootloader_description->module_name, BOOTLOADER, bootloader_description->module_path, boot_module_interface->ImageBase, boot_module_entry, boot_module_interface->ImageSize, NULL);


}

EFI_STATUS load_boot_modules(const boot_time_modules* boot_time_loaded_modules, UINTN number_of_modules, EFI_HANDLE image_handle)
{
	if(verify_function_pointers((void* []){boot_time_loaded_modules, image_handle}, 2))
		return EFI_INVALID_PARAMETER;

	EFI_STATUS load_time_error = EFI_SUCCESS;

	EFI_HANDLE device_handle = get_device_handle(image_handle);

	if(device_handle == NULL)
	{
		EFI_FATAL_REPORT("Unable to open device handle", KERNEL_LOAD_ERROR);
	}

	for(boot_time_modules* list_module = boot_time_loaded_modules; number_of_modules--; list_module++)
	{
		switch(list_module->module_type)
		{
			case STACK:
			{
				load_time_error = init_kernel_stack(&list_module);
				EFI_FATAL_REPORT("Error while allocating kernel stack", load_time_error);
				break;
			}
			case KERNEL:
			{
				load_time_error = rt_loadfile(device_handle, &list_module);
				EFI_FATAL_REPORT("Error while reading kernel modules", load_time_error);

				break;
			}
			case FONT:
			{
				load_time_error = load_kernel_font(device_handle, &list_module);
				EFI_FATAL_REPORT("Error while loading default system font", load_time_error);
			}
		}
	}

	return load_time_error;
	
}

EFI_STATUS add_boot_module(const CHAR8* module_name, UINT8 module_type, const CHAR16* module_path, VOID* module_start, VOID* module_entry, UINT64 module_size, VOID* reloc_section)
{

	if(verify_function_pointers((void* []){module_name, module_path, module_start}, 3) || module_type == 0)
		return EFI_INVALID_PARAMETER;

	
	if((module_type == KERNEL && (reloc_section == NULL || module_entry == NULL)) || module_type == BOOTLOADER && module_entry == NULL)
		return EFI_INVALID_PARAMETER;

	boot_module new_boot_module;
	EFI_STATUS op_status = EFI_SUCCESS;

	/* Common params for all types of modules */
	new_boot_module.module_name = module_name;
	new_boot_module.module_type = module_type;
	new_boot_module.module_start = module_start;
	new_boot_module.module_size = module_size;

	switch(module_type)
	{
		case BOOTLOADER:{
			new_boot_module.module_entry = module_entry;
			break;
		}
		case KERNEL:{
			new_boot_module.kernel.module_entry = module_entry;
			new_boot_module.kernel.reloc_section = reloc_section;
		}
	}

	if(!add_array_member(&boot_modules_descriptor, &new_boot_module))
	 	return op_status;
	else
		return KERNEL_LOAD_ERROR;

}