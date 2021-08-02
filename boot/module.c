#include <rtos/handoff.h>
#include <boot/modules.h>
#include <boot/stack.h>
#include <boot/error.h>
#include <boot/file.h>
#include <boot/loader.h>
#include <refilib/refilib.h>
#include <glib/array.h>
#include <glib/rcommon.h>


boot_handoff* kernel_essentials;

EFI_STATUS init_boot_module(const boot_time_modules* bootloader_description, EFI_HANDLE image_handle, void* boot_module_entry)
{
	EFI_STATUS op_status = EFI_SUCCESS;

	EFI_LOADED_IMAGE_PROTOCOL* boot_module_interface = NULL;

	op_status = BS->HandleProtocol(image_handle, &(EFI_GUID)EFI_LOADED_IMAGE_PROTOCOL_GUID, (void**)&boot_module_interface);

	RETURN_ON_ERROR(op_status);

	op_status = allocate_loader_pool(sizeof(boot_handoff) + sizeof(boot_module) * MAX_BOOT_MODULES, (void**)&kernel_essentials); /* Allocate space for 10 modules for now */

	RETURN_ON_ERROR(op_status);

	op_status = add_boot_module(bootloader_description->module_name, BOOTLOADER, bootloader_description->module_path, boot_module_interface->ImageBase, boot_module_entry, boot_module_interface->ImageSize, NULL, NULL);

	return op_status;
}

EFI_STATUS load_boot_modules(const boot_time_modules* boot_time_loaded_modules, UINTN number_of_modules, EFI_HANDLE image_handle)
{
	if(!verify_function_pointers((const void* []){boot_time_loaded_modules, image_handle}, 2))
		return EFI_INVALID_PARAMETER;

	EFI_STATUS load_time_error = EFI_SUCCESS;

	EFI_HANDLE device_handle = get_device_handle(image_handle);

	if(device_handle == NULL)
	{
		EFI_FATAL_REPORT(L"Unable to open device handle", KERNEL_LOAD_ERROR);
	}

	for(const boot_time_modules* list_module = boot_time_loaded_modules; number_of_modules; list_module++)
	{
		switch(list_module->module_type)
		{
			case STACK:
			{
				load_time_error = init_kernel_stack(list_module);
				EFI_FATAL_REPORT(L"Error while allocating kernel stack", load_time_error);
				break;
			}
			case KERNEL:
			{
				load_time_error = rt_loadfile(device_handle, list_module);
				EFI_FATAL_REPORT(L"Error while reading kernel modules", load_time_error);

				break;
			}
			case FONT:
			{
				load_time_error = load_kernel_font(list_module, device_handle);
				EFI_FATAL_REPORT(L"Error while loading default system font", load_time_error);
			}
		}
		number_of_modules--;
	}

	return load_time_error;
	
}

EFI_STATUS add_boot_module(const char* module_name, module_types module_type, const CHAR16* module_path, VOID* module_start, VOID* module_entry, UINT64 module_size, VOID* reloc_section, map_descriptor* map)
{

	if(!verify_function_pointers((const void* []){module_name, module_start}, 2) || module_type == 0)
		return EFI_INVALID_PARAMETER;

	if((module_type == KERNEL && (reloc_section == NULL || module_entry == NULL)) || (module_type == BOOTLOADER && module_entry == NULL))
		return EFI_INVALID_PARAMETER;

	static size_t next_free_boot_module = 0;

	boot_module new_boot_module = {.module_name = module_name, .module_type = module_type, .module_start = module_start,
									.module_size = module_size };
	EFI_STATUS op_status = EFI_SUCCESS;

	switch(module_type)
	{
		case BOOTLOADER:{
			new_boot_module.rtmod.module_entry = module_entry;
			new_boot_module.rtmod.module_path = module_path;
			break;
		}
		case KERNEL:{
			new_boot_module.rtmod.module_entry = module_entry;
			new_boot_module.rtmod.reloc_section = reloc_section;
			new_boot_module.rtmod.module_path = module_path;
			break;
		}
		case MAP: {
			new_boot_module.map.desc_size = map->DescSize;
			new_boot_module.map.desc_ver = map->DescVer;
			new_boot_module.map.map_key = map->MapKey;
			new_boot_module.map.system_memory_map = map->Map;
		}
	}

	kernel_essentials->loaded_modules[next_free_boot_module++] = new_boot_module;
	kernel_essentials->number_of_modules++;

	return op_status;
}