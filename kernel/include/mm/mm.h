#ifndef _MM_H_
#define _MM_H_

#include <error/syserror.h>
#include <kernel.h>
#include <mm/phyMem.h>

typedef struct {
    size_t RAM;
    size_t GDT_descriptors;
}meminfo;

SYS_ERROR mm_init(Map_descriptor *map);

#endif