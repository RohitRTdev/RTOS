#include <cpu/cpu.h>
#include <rclib.h>


processor_info current_processor_info;
uint8_t sse_check();
static void cpu_get_manufacturer()
{
    uint32_t eax = 0;
    uint32_t ebx, ecx, edx;
    
    cpuid(&eax, &ebx, &ecx, &edx);

    //Get the Vendor string in appropriate format
    rmemcpy((void*)current_processor_info.vendor_string, (void*)&ebx, 4);
    rmemcpy((void*)(current_processor_info.vendor_string + 4), (void*)&edx, 4);
    rmemcpy((void*)(current_processor_info.vendor_string + 8), (void*)&ecx, 4);

    current_processor_info.vendor_string[12] = '\0';
    
    if(!rstrcmp(current_processor_info.vendor_string, AMD_VENDOR))
    {
        current_processor_info.CPU = AMD;
    }       
    else if(!rstrcmp(current_processor_info.vendor_string, INTEL_VENDOR))
    {
        current_processor_info.CPU = INTEL;
    }
        
    
}
static void cpu_address_range()
{
    uint32_t eax = 0x80000008;
    uint32_t ebx, ecx, edx;

    cpuid(&eax, &ebx, &ecx, &edx);
    current_processor_info.cpu_range.physical_range = (uint8_t)eax;
    current_processor_info.cpu_range.virtual_range = (uint8_t)(eax >> 8);
}

SYS_ERROR CPU_init()
{
    SYS_ERROR err_status = NO_ERROR;

    current_processor_info.sse_version = sse_check();
    if(current_processor_info.sse_version == 0)
        return NO_SSE;

    cpu_get_manufacturer();
    if(!(current_processor_info.CPU == AMD || current_processor_info.CPU == INTEL))
        return CPU_NOT_SUPPORTED;

    cpu_address_range();


    return err_status;
}