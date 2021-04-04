#ifndef _MODULE_H_
#define _MODULE_H_
#include <rtypes.h>
#include <error/syserror.h>

SYS_ERROR module_init();
uint64_t RegisterModule(uint64_t module_id, void *module_interface);
void* QueryModule(uint64_t module_id);
SYS_ERROR UnRegisterModule(uint64_t module_id);


#endif
