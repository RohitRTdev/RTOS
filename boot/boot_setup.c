#include <boot/boot_setup.h>
#include <boot/modules.h>

boot_module modules[MODULE_MAX] = {0};

static boot_module* set_new_module()
{   
    UINT8 module_index = 0;
    for(module_index = 0; module_index < MODULE_MAX; module_index++)
    {
        if(modules[module_index].module_type == 0)
            break;
    }

    if(module_index == MODULE_MAX)
        return NULL;

    modules[module_index].module_id = module_index;

    return &modules[module_index];
    
}

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

EFI_STATUS getMemMap(Map_descriptor *MemMap)
{
    EFI_STATUS status;

    BS->GetMemoryMap(&(MemMap->MapSize), MemMap->Map, &(MemMap->MapKey), &(MemMap->DescSize), &(MemMap->DescVer));
    MemMap->MapSize += MemMap->DescSize; //Add extra size to accomodate the newly allocated pool
    
    MemMap->MapSize = round_4k(MemMap->MapSize) * PAGESIZE; //Align on a page boundary

      
    
    status = BS->AllocatePages(AllocateAnyPages, EfiLoaderData, MemMap->MapSize / PAGESIZE, (EFI_PHYSICAL_ADDRESS*)&(MemMap->Map));
    EFI_FATAL_REPORT(L"Memory allocation failed for holding memory map", status);

    status = BS->GetMemoryMap(&(MemMap->MapSize), MemMap->Map,&(MemMap->MapKey),&(MemMap->DescSize),&(MemMap->DescVer));
    

    return status;
}

UINT8 create_boot_module(CHAR8* ModuleName, UINT8 ModuleType, VOID* ModuleEntry, UINT64 ModuleSize, VOID* ModuleStart, VOID* ModuleReloc)
{
    boot_module* new_module = set_new_module();

    if(new_module == NULL)
    {
        return 0;
    }

    rstrcpy(new_module->module_name, ModuleName);

    new_module->module_size = ModuleSize;
    new_module->module_start = ModuleStart;
    new_module->module_type = ModuleType;

    if(ModuleType == KERNEL)
    {
        new_module->kernel.module_entry = ModuleEntry;
        new_module->kernel.reloc_section = ModuleReloc;
    }

    return new_module->module_id;

}


