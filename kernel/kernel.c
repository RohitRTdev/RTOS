#include <fonts/psf.h>
#include <logging/basic_print.h>
#include <cpu/cpu.h>
#include <mm/mm.h>
#include <utils.h>


typedef struct{
    uint64_t module_id;
    uint64_t module_string;
    uint64_t module_entry;
    uint64_t module_interface;
}new_resc;

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
<<<<<<< HEAD

    basic_print("Loaded RTOS 1.0 ...\r\n");
    basic_print("Oops... RTOS seems to be in maintenance... Please wait until official RTOS 1.0 is released.\r\n");
    basic_print("To exit just click the shutdown button.\r\n");


=======
    
>>>>>>> ee600c6aefe4ed8a2cb61d59befc3b98f24e7dbd

    while(1){}
}

void kernel_entry(boot_info *boot)
{
    kernel_main(boot);    
}    
