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
    err_status = basic_PSF_renderer(boot->basic_font_base, *boot->framebuffer, *boot->framebuffer->Info);
   
    if(RT_ERROR(err_status))
    {
        report_error(err_status);   
        while(1){}
    }
    //Note that UEFI already sets up double extended precision SSE for the system   
    //Errors that happen during initialisation of core modules cannot be resolved and will make system unresponsive 

    //Set up kernel modules
    err_status = CPU_init();
    RT_ERROR_REPORT("Cpu not supported", err_status);

    err_status = mm_init(boot->Map);
    RT_ERROR_REPORT("Failed to initialise Memory Manager", err_status); 

    basic_print("RTOS 1.0 has successfully loaded!\r\n");
    basic_print("To exit, just press the shutdown button");
    

    while(1){}
}

void kernel_entry(boot_info *boot)
{
    kernel_main(boot);    
}    

