#include <refilib/refilib.h>
#include <boot/stack.h>
#include <boot/error.h>
#include <boot/modules.h>

EFI_STATUS init_kernel_stack(boot_time_modules* stack_description)
{
	EFI_PHYSICAL_ADDRESS* physical_stack_base = NULL;
	EFI_STATUS op_status = EFI_SUCCESS;

	op_status = BS->AllocatePages(AllocateAnyPages, EfiLoaderData, STACK_SIZE / PAGESIZE, &physical_stack_base);	

	RETURN_ON_ERROR(op_status)

	op_status = add_boot_module(stack_description->module_name, STACK, NULL, physical_stack_base, NULL, STACK_SIZE, NULL);
	
	return op_status;
}