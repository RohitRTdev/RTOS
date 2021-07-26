#ifndef _VIRTUAL_MEM_STRUCTS_H_
#define _VIRTUAL_MEM_STRUCTS_H_

#include <cpu/cpu.h>
#include <mm/mm.h>
#include <mm/phyMem.h>

typedef struct{
    boolean page_level_5;
}virtual_mem_info;

#endif