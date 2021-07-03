#include <boot/boot_setup.h>

VOID* getACPI2_0table()
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
    
    MemMap->MapSize = round_4k(MemMap->MapSize) * PAGESIZE; //Align on a page boundary

      
    
    status = BS->AllocatePages(AllocateAnyPages, EfiLoaderData, MemMap->MapSize / PAGESIZE, (EFI_PHYSICAL_ADDRESS*)&(MemMap->Map));
    EFI_FATAL_REPORT(L"Memory allocation failed for holding memory map", status);

    status = BS->GetMemoryMap(&(MemMap->MapSize), MemMap->Map,&(MemMap->MapKey),&(MemMap->DescSize),&(MemMap->DescVer));
    
    /* In RTOS, error checking is caller's responsibility */

    return status;
}


