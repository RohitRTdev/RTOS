#include <refi/refi.h>
#include <refi/refilib.h>
#include <boot/primary_loader.h>
#include <boot/basic_font.h>
#include <boot/boot_structs.h>
#include <boot/boot_virtual_setup.h>

typedef void (*kernel)(boot_info*);

static void* getACPI2_0table()
{
    UINTN size = ST->NumberOfTableEntries;
    UINTN i = 0;
    EFI_GUID acpi_2_0 = EFI_ACPI_20_TABLE_GUID;
    while(i < size)
    {
        if(guid_check((ST->ConfigurationTable + i)->VendorGuid, acpi_2_0))
        {  
            return (ST->ConfigurationTable + i)->VendorTable;
        }
        i++;
    }
    if(i == size)
        return NULL;
}

boot_info boot_info_send;
Map_descriptor MemMap;

static EFI_STATUS getMemMap(Map_descriptor *MemMap)
{
    EFI_STATUS status;

    BS->GetMemoryMap(&(MemMap->MapSize), MemMap->Map, &(MemMap->MapKey), &(MemMap->DescSize), &(MemMap->DescVer));
    MemMap->MapSize += MemMap->DescSize; //Add extra size to accomodate the newly allocated pool
    
    MemMap->MapSize = round_4k(MemMap->MapSize) * PAGESIZE; //Align on a page boundary

      
    
    status = BS->AllocatePages(AllocateAnyPages, EfiLoaderData, MemMap->MapSize / PAGESIZE, (EFI_PHYSICAL_ADDRESS*)&(MemMap->Map));
    EFI_FATAL_REPORT(L"Memory allocation failed for holding memory map", status);

    status = BS->GetMemoryMap(&(MemMap->MapSize), MemMap->Map,&(MemMap->MapKey),&(MemMap->DescSize),&(MemMap->DescVer));
    
    /* In RTOS, error checking is caller's responsibility */

    return status;
}

static EFI_STATUS EFI_clearscreen()
{
    EFI_STATUS status;
    status = ST->ConOut->ClearScreen(ST->ConOut);
    return status;
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS status = EFI_SUCCESS;
    UINT8 *entry = NULL;
    
    CHAR16 *image_path = L"\\Modules\\RTcore.rm";
    CHAR16 *basic_font_path = L"\\Fonts\\zap-light18.psf";

    InitLib(ImageHandle, SystemTable);  //Initialise REFI library

    EFI_clearscreen();

    //Load kernel into physical address space
    entry = pe_loadfile(ImageHandle, image_path, boot_info_send.image);
    if(!entry)
    {
        EFI_FATAL_REPORT(L"Kernel load error", KERNEL_EFI_ERROR);
    }

    kernel kernel_entry = (kernel)entry;    

    //Get basic font for low level print functionality

    basic_font_load(ImageHandle, basic_font_path, &boot_info_send.basic_font_base);
    if(!boot_info_send.basic_font_base.basic_font_base)
    {
        EFI_FATAL_REPORT(L"Basic PSF load error", KERNEL_EFI_ERROR);
    }

    //Allocate new stack for kernel at highest memory location
    status = BS->AllocatePages(AllocateAnyPages, EfiLoaderData, STACK_SIZE / PAGESIZE, (EFI_PHYSICAL_ADDRESS*)&boot_info_send.stack.stack_top);
    EFI_FATAL_REPORT(L"Stack buffer allocation failed!", status);

    boot_info_send.stack.stack_size = STACK_SIZE;

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