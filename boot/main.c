#include <rtos/handoff.h>
#include <refi/refi.h>
#include <refilib/refilib.h>
#include <boot/modules.h>
#include <boot/setup.h>

boot_time_modules boot_time_loaded_modules[] = {{BOOTLOADER, L"\\EFI\\BOOT\\BOOTx64.EFI","RTboot"},
                                                {STACK, NULL, "kernel_stack"},
                                                {KERNEL,L"\\Modules\\RTcore.rm","RTcore"},
                                                {FONT,L"\\Fonts\\zap-light18.psf","DefaultPSFfont"},
                                                {MAP, NULL, "SystemMemoryMap"}};


#define MODULE_LIST_MEMBERS (sizeof(boot_time_loaded_modules) / sizeof(boot_time_modules))

/* The UEFI boot manager calls this function */
EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
    EFI_STATUS op_status = EFI_SUCCESS;
    
    init_lib(image_handle, system_table);  /* Initialise REFI library */

    efi_clearscreen();

    op_status = init_boot_module(&boot_time_loaded_modules[0], image_handle, efi_main); /* Initialise the bootloader itself */
    EFI_FATAL_REPORT(L"Boot module initialisation failure!", op_status);


    /* Load kernel components into physical address space */
    op_status = load_boot_modules(boot_time_loaded_modules, MODULE_LIST_MEMBERS, image_handle);
    EFI_FATAL_REPORT(L"Kernel components loading failed!", op_status);


    //Get GOP framebuffer

    op_status = setup_gop();
    EFI_FATAL_REPORT(L"Unable to initialise graphics hardware", op_status);

    //Get ACPI table 
    kernel_essentials->rsdp_table = get_ACPI2_0_table();
    if(!kernel_essentials->rsdp_table)
        EFI_FATAL_REPORT(L"Could not locate ACPI table version 2.0", ACPI_ERROR);

    //Get memory map
    op_status = get_mem_map(&boot_time_loaded_modules[4]);
    EFI_FATAL_REPORT(L"Error in acquiring memory map", op_status);    


    //op_status = BS->ExitBootServices(image_handle, mapkey);
    //EFI_FATAL_REPORT(L"Could not exit boot services", op_status);
    
    //Transfer control to kernel

    kernel_entry(kernel_essentials, system_table);
        
    return op_status;
    
}