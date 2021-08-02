#include <refilib/refilib.h>
#include <rtos/handoff.h>
#include <boot/modules.h>

UINTN mapkey;

VOID* get_ACPI2_0_table()
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
    

    return NULL;
}

EFI_STATUS get_mem_map(const boot_time_modules* system_map_descriptor)
{
    EFI_STATUS status;
    map_descriptor map = {0};

    BS->GetMemoryMap(&map.MapSize, map.Map, &map.MapKey, &map.DescSize, &map.DescVer);
    map.MapSize += map.DescSize; //Add extra size to accomodate the newly allocated pool
    
    map.MapSize = ALIGN(map.MapSize, PAGESIZE); //Align on a page boundary

      
    
    status = allocate_loader_pages(map.MapSize, (EFI_PHYSICAL_ADDRESS*)&map.Map);
    EFI_FATAL_REPORT(L"Memory allocation failed for holding memory map", status);

    status = BS->GetMemoryMap(&map.MapSize, map.Map, &map.MapKey, &map.DescSize, &map.DescVer);    
    EFI_FATAL_REPORT(L"Unable to acquire system memory map", status);

    add_boot_module(system_map_descriptor->module_name, MAP, NULL, map.Map, NULL, map.MapSize, NULL, &map);

    /* Mapkey is required for ExitBootServices */
    mapkey = map.MapKey;

    return status;
}



