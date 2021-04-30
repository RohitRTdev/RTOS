#include <cpu/cpu.h>
#include <rclib.h>


processor_info current_processor_info;

void feature_enumerate();
uint8_t sse_check();

static void cpu_get_manufacturer()
{
    cpuid_registers registers = {0, 0, 0, 0};
    cpuid(&registers);

    //Get the Vendor string in appropriate format
    rmemcpy((void*)current_processor_info.vendor_string, (void*)&registers.ebx, 4);
    rmemcpy((void*)(current_processor_info.vendor_string + 4), (void*)&registers.edx, 4);
    rmemcpy((void*)(current_processor_info.vendor_string + 8), (void*)&registers.ecx, 4);

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
    cpuid_registers registers = {0x80000008, 0, 0, 0};

    cpuid(&registers);
    current_processor_info.cpu_range.physical_range = (uint8_t)registers.eax;
    current_processor_info.cpu_range.virtual_range = (uint8_t)(registers.eax >> 8);
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

    feature_enumerate();


    return err_status;
}