#ifndef _MM_H_
#define _MM_H_

#include <error/syserror.h>
#include <rtos/handoff.h>

typedef struct {
    size_t RAM;
    size_t GDT_descriptors;
}meminfo;


SYS_ERROR mm_init(map_descriptor *map);

#endif