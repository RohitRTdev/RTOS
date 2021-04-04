#include <module/modules.h>
#include <module/moduleutils.h>
#include <mm/mm.h>
#include <mm/phyMem.h>
#include <module/interfaces.h>

static module_buffers modules;
_core_interface *core_interface_ptr;


static uint64_t check_id_validity(uint64_t module_id)
{
    for (int list_index = 0; list_index < modules.max_id_index; )
}

SYS_ERROR module_init()
{
    //Allocate some memory for holding the module stuctures initially
    size_t module_name_buffer = MODULE_NAME_BUFFER_SIZE;
    size_t module_id_buffer = MODULE_ID_BUFFER_SIZE;
    size_t module_interface_buffer = MODULE_INTERFACE_BUFFER_SIZE;
    size_t core_interface_size = sizeof(_core_interface);


    SYS_ERROR err_code = AllocMem(module_name_buffer, (void**)modules.module_name_block);
    RT_INFO(err_code)
    err_code = AllocMem(module_id_buffer, (void**)modules.module_id_block);
    RT_INFO(err_code)
    err_code = AllocMem(module_id_buffer, (void**)modules.module_interface_block);
    RT_INFO(err_code)

    err_code = AllocMem(core_interface_size, (void**)core_interface_ptr);
    RT_INFO(err_code)

    err_code = RegisterModule(RT_CORE, (void*)core_interface);
    RT_INFO(err_code)

    err_code = NO_ERROR;
    return err_code;
}

SYS_ERROR RegisterModule(uint64_t module_id, void *module_interface)
{
    check_id_validity(module_id);
}

