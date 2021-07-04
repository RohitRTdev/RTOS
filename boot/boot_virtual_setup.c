#include <boot/boot_virtual_setup.h>
#include <refilib.h>

static UINT8 max_virtual_address_width;

static void get_max_virtual_addr_width()
{
    UINT32 address_code = 0;
    //cpuid code for getting max virtual_address
    asm ("movl $0x80000008, %%eax\t\n"
         "movl $0, %%ebx\t\n"
         "movl $0, %%ecx\t\n"
         "movl $0, %%edx\t\n"
         "cpuid\t\n"
         :"=a"(address_code));

    max_virtual_address_width = (address_code & 0xff00) >> 8; //Get the 2nd byte  

}

VOID setup_boot_virtual_memory(boot_info* boot_info_send)
{
    //Gather all modules that we want
    UINTN stack_top = (UINTN)boot_info_send->stack.stack_top;
    UINTN stack_size = boot_info_send->stack.stack_size;

    get_max_virtual_addr_width();
    
    //Start of half of the memory
    UINTN virtual_pointer = ((UINT64)1 << (max_virtual_address_width - 1)) - 1;
    UINTN virtual_stack = ((UINT64)1 << max_virtual_address_width) - stack_size;
    UINTN max_virtual_address = ((UINT64)1 << max_virtual_address_width) - 1;

    boot_info_send->max_virtual_address = max_virtual_address;
    //Setup the virtual relocations

    EFI_MEMORY_DESCRIPTOR *map_iterator = NULL;
    EFI_MEMORY_DESCRIPTOR *map_root = boot_info_send->Map->Map;
    UINTN max_descriptors = boot_info_send->Map->MapSize / boot_info_send->Map->DescSize;
    UINT32 desc_size = boot_info_send->Map->DescSize;

    UINTN iterator = 0;

    while(iterator < max_descriptors)
    {
        //Get the current descriptor 
        map_iterator = getMapDescriptor(map_root, desc_size, iterator);

        switch(map_iterator->Type)
        {
            case RT_STACK: {
                              map_iterator->VirtualStart = virtual_stack;
                              break;
                           }
            case RT_RCS:
            case RT_MODULE:
            case EfiRuntimeServicesCode:
            case EfiRuntimeServicesData:
            case EfiMemoryMappedIO:
            case EfiMemoryMappedIOPortSpace:
            case EfiACPIReclaimMemory:
            case EfiACPIMemoryNVS:
            case EfiUnusableMemory:
            case EfiPalCode: {
                               map_iterator->VirtualStart = virtual_pointer;
                               virtual_pointer += map_iterator->NumberOfPages * PAGESIZE;
                               break;
                             }
            default:        {
                               map_iterator->VirtualStart = map_iterator->PhysicalStart;
                            }
        }
        iterator++;
    }

    iterator = 24;
    while(iterator < 35)
    {
        map_iterator = getMapDescriptor(map_root, desc_size, iterator);
        printEFI(L"%d %d %d %d\r\n", map_iterator->Type, map_iterator->PhysicalStart, map_iterator->VirtualStart, map_iterator->NumberOfPages);
       
        iterator++;
    }
    while(1){}

}