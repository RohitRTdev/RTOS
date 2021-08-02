#include <error/syserror.h>
#include <rtos/handoff.h>
#include <kernel/utils.h>
#include <cpu/system.h>

static void kernel_main(boot_handoff *kernel_essentials)
{
    _cli();   //Disable all interrupts

    //SYS_ERROR err_status = NO_ERROR;
    //For basic debugging    
    // err_status = basic_PSF_renderer(boot->basic_font.basic_font_base, *boot->framebuffer, *boot->framebuffer->Info);
   
    // if(RT_ERROR(err_status))
    // {
    //     report_error(err_status);   
    //     while(1){}
    // }

    // basic_print("hello\r\n");
    // halt_system();

    // uint64_t iterator = 0;
    // uint64_t maxdes = boot->Map->MapSize/boot->Map->DescSize;
    // EFI_MEMORY_DESCRIPTOR *map = boot->Map->Map;
    // EFI_MEMORY_DESCRIPTOR *map_it = NULL;

    // quick_sort((void*)map, boot->Map->MapSize, (void*)&map->PhysicalStart, boot->Map->DescSize);
    // basic_print("address:%d %d %d\r\n", boot->framebuffer->FrameBufferBase, boot->framebuffer->FrameBufferSize, boot->acpi);
    // while(iterator < maxdes - 10)
    // {
    //     map_it = getMemMapDescriptor(map, boot->Map->DescSize, iterator);
    //     basic_print("%d %d %d\r\n", map_it->Type, map_it->PhysicalStart, map_it->NumberOfPages);
    //     iterator++;
    // }


    //Note that UEFI already sets up double extended precision SSE for the system   
    //Errors that happen during initialisation of core modules cannot be resolved and will make system unresponsive 
    //Set up kernel modules

    halt_system();

}

void kernel_entry(boot_handoff *kernel_essentials, EFI_SYSTEM_TABLE* system_table)
{

    system_table->ConOut->OutputString(system_table->ConOut, L"Hello from RT kernel");
    halt_system();
    //kernel_main(kernel_essentials);    
}    

