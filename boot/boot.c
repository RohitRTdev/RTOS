#include <refi.h>
#include <refilib.h>
#include <primary_loader.h>
#include <basic_font.h>


typedef struct {
    UINTN MapSize;
    UINTN DescSize;
    UINTN MapKey;
    UINT32 DescVer;
    EFI_MEMORY_DESCRIPTOR *Map;
}Map_descriptor;

typedef struct{
    Map_descriptor* Map;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *framebuffer;
    Image_data *image;
    void *acpi;
    uint8_t *basic_font_base;
}boot_info;

typedef void (*kernel)(boot_info*);
static BOOLEAN guid_check(EFI_GUID guid1, EFI_GUID guid2)
{
    UINTN j = 0;
    if(guid1.Data1 == guid2.Data1 && guid1.Data2 == guid2.Data2 && guid1.Data3 == guid2.Data3)
    {    while(guid1.Data4[j] == guid2.Data4[j] && j < 8)
            {j++;}
        if(j == 8)
            return TRUE;
    }
    return FALSE;
}

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

static EFI_STATUS getMemMap(Map_descriptor *MemMap)
{
    EFI_STATUS status;

    BS->GetMemoryMap(&(MemMap->MapSize), MemMap->Map, &(MemMap->MapKey), &(MemMap->DescSize), &(MemMap->DescVer));
    MemMap->MapSize += MemMap->DescSize; //Add extra size to accomodate the newly allocated pool
    
    MemMap->MapSize = round_4k(MemMap->MapSize)*PAGESIZE; //Align on a page boundary
    
    status = BS->AllocatePool(EfiLoaderData, MemMap->MapSize, (void**)&(MemMap->Map));
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
    Image_data image;
    Map_descriptor MemMap = {0,0,0,0,NULL}; 
    boot_info boot_info_send;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION graph_info;
    VOID *acpi = NULL;
    CHAR16 *image_path = L"\\Modules\\RTcore.rm";
    CHAR16 *basic_font_path = L"\\Fonts\\zap-light18.psf";

   

    InitLib(ImageHandle, SystemTable);  //Initialise REFI library

    EFI_clearscreen();

    //Load kernel into physical address space
    entry = pe_loadfile(ImageHandle, image_path, &image);
    if(!entry)
    {
        EFI_FATAL_REPORT(L"Kernel load error", KERNEL_EFI_ERROR);
    }

    kernel kernel_entry = (kernel)entry;    

    //Get basic font for low level print functionality

    boot_info_send.basic_font_base = basic_font_load(ImageHandle, basic_font_path);
    if(!boot_info_send.basic_font_base)
    {
        EFI_FATAL_REPORT(L"Basic PSF load error", KERNEL_EFI_ERROR);
    }

    //Get GOP framebuffer

    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop_prot = NULL;

    status = BS->LocateProtocol(&gop_guid, NULL, (void**)&gop_prot);
    EFI_FATAL_REPORT(L"Could not locate GOP", status);

    status = gop_prot->SetMode(gop_prot, gop_prot->Mode->Mode);
    EFI_FATAL_REPORT(L"Error in setting default graphics mode", status);
    
    //Get ACPI table 

    acpi = getACPI2_0table();
    if(!acpi)
        EFI_FATAL_REPORT(L"Could not locate ACPI table version 2.0", KERNEL_EFI_ERROR);
    
    boot_info_send.acpi = acpi;

    //Get memory map
    status = getMemMap(&MemMap);
    EFI_FATAL_REPORT(L"Error in acquiring memory map", status);

    //Ready the information to be sent to the kernel
    boot_info_send.Map = &MemMap;
    boot_info_send.image = &image;
    boot_info_send.framebuffer = gop_prot->Mode;

    status = BS->ExitBootServices(ImageHandle, MemMap.MapKey);
    EFI_FATAL_REPORT(L"Could not exit boot services", status);
    
    //Transfer control to kernel
    kernel_entry(&boot_info_send);
          

    return status;

    
    
}