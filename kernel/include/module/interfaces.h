#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <mm/phyMem.h>

typedef SYS_ERROR (*AllocMem)(size_t*, void**);
typedef SYS_ERROR (*FreeMem)(void*);
typedef SYS_ERROR (*ReAllocMem)(size_t*, void**);

#define RT_CORE 1

typedef struct{
    //Memory services
    AllocMem AllocMem;
    FreeMem FreeMem;
    ReAllocMem ReAllocMem;    
}_core_interface;

#endif