#include <fonts/psf.h>
#include <logging/basic_print.h>
#include <cpu/cpu.h>
#include <mm/mm.h>
#include <utils.h>

static void kernel_main(boot_info *boot)
{
    _cli();   //Disable all interrupts

    SYS_ERROR err_status = NO_ERROR;
    //For basic debugging    
    err_status = basic_PSF_renderer(boot->basic_font.basic_font_base, *boot->framebuffer, *boot->framebuffer->Info);
   
    if(RT_ERROR(err_status))
    {
        report_error(err_status);   
        while(1){}
    }

    basic_print("hello\r\n");
    halt_system();

    uint64_t iterator = 0;
    uint64_t maxdes = boot->Map->MapSize/boot->Map->DescSize;
    EFI_MEMORY_DESCRIPTOR *map = boot->Map->Map;
    EFI_MEMORY_DESCRIPTOR *map_it = NULL;

    quick_sort((void*)map, boot->Map->MapSize, (void*)&map->PhysicalStart, boot->Map->DescSize);
    basic_print("address:%d %d %d\r\n", boot->framebuffer->FrameBufferBase, boot->framebuffer->FrameBufferSize, boot->acpi);
    while(iterator < maxdes - 10)
    {
        map_it = getMemMapDescriptor(map, boot->Map->DescSize, iterator);
        basic_print("%d %d %d\r\n", map_it->Type, map_it->PhysicalStart, map_it->NumberOfPages);
        iterator++;
    }


    //Note that UEFI already sets up double extended precision SSE for the system   
    //Errors that happen during initialisation of core modules cannot be resolved and will make system unresponsive 

    //Set up kernel modules
    err_status = CPU_init();
    RT_ERROR_REPORT("Cpu not supported", err_status);

    err_status = mm_init(boot->Map);
    RT_ERROR_REPORT("Failed to initialise Memory Manager", err_status);
    
    halt_system(); 
}

void kernel_entry(boot_info *boot)
{
    kernel_main(boot);    
}    

