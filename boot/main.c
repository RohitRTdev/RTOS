#include <refi/refi.h>
#include <refilib/refilib.h>
#include <boot/modules.h>

#define MODULE_LIST_MEMBERS 4
boot_time_modules boot_time_loaded_modules[] = {{BOOTLOADER, L"\\EFI\\BOOT\\BOOTx64.EFI","RTboot"},
                                                {STACK, NULL, "kernel_stack"},
                                                {KERNEL,L"\\Modules\\RTcore.rm","RTcore"},
                                                {FONT,L"\\Fonts\\zap-light18.psf","DefaultPSFfont"}};

boot_info boot_info_send;
Map_descriptor MemMap;


/* The UEFI boot manager calls this function */
EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
    EFI_STATUS op_status = EFI_SUCCESS;
    
    InitLib(image_handle, system_table);  /* Initialise REFI library */

    EFI_clearscreen();

    init_boot_module(&boot_time_loaded_modules[0], image_handle, efi_main); /* Initialise the bootloader itself */

    /* Load kernel components into physical address space */
    op_status = load_boot_modules(boot_time_loaded_modules, MODULE_LIST_MEMBERS, image_handle);
    EFI_FATAL_REPORT(L"Kernel components loading failed!", op_status);

    //Get GOP framebuffer

    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop_prot = NULL;

    status = BS->LocateProtocol(&gop_guid, NULL, (void**)&gop_prot);
    EFI_FATAL_REPORT(L"Could not locate GOP", status);

    status = gop_prot->SetMode(gop_prot, gop_prot->Mode->Mode);
    EFI_FATAL_REPORT(L"Error in setting default graphics mode", status);
    
    //Get ACPI table 
    boot_info_send.acpi = getACPI2_0table();
    if(!boot_info_send.acpi)
        EFI_FATAL_REPORT(L"Could not locate ACPI table version 2.0", KERNEL_EFI_ERROR);


    //Get memory map
    status = getMemMap(&MemMap);
    EFI_FATAL_REPORT(L"Error in acquiring memory map", status);
    
    //Ready the information to be sent to the kernel
    boot_info_send.Map = &MemMap;
    boot_info_send.framebuffer = gop_prot->Mode;

    //setup_boot_virtual_memory(&boot_info_send);

    status = BS->ExitBootServices(ImageHandle, boot_info_send.Map->MapKey);
    EFI_FATAL_REPORT(L"Could not exit boot services", status);
    
    //Transfer control to kernel
    kernel_entry(&boot_info_send);
          

    return status;

    
    
}