#ifndef _BOOT_STACK_H_
#define _BOOT_STACK_H_

#include <refi/refi.h>
#include <boot/modules.h>

#define STACK_SIZE 10 * PAGESIZE

EFI_STATUS init_kernel_stack(const boot_time_modules* stack_description);

#endif