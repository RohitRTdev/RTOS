#include <mm/virtualMemStructs.h>

static virtual_mem_info virtualMemInfo;



static SYS_ERROR virtualMapl4(void *Physical_address, void *Virtual_address, size_t pagesToMap)
{

    return NO_ERROR;

}


static SYS_ERROR virtualMapl5(void *Physical_address, void *Virtual_address, size_t pagesToMap)
{
    return NO_ERROR; 
}

SYS_ERROR virtualMap(void *Physical_address, void *Virtual_address, size_t pagesToMap)
{
    SYS_ERROR errcode = NO_ERROR;

    //Check whether paging is 4 or 5 level

    if(virtualMemInfo.page_level_5)
        errcode = virtualMapl5(Physical_address, Virtual_address, pagesToMap);
    else
        errcode = virtualMapl4(Physical_address, Virtual_address, pagesToMap);


    return errcode;
}

SYS_ERROR virtualUnMap(void *VirtualAddress, size_t pagesMapped)
{
    SYS_ERROR errcode = NO_ERROR;

    return errcode;
}

SYS_ERROR virtualAllocKernel(size_t bufSize, void **VirtualAddress)
{
    SYS_ERROR errcode = NO_ERROR;

    return errcode;
}