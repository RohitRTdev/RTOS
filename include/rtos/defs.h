#ifndef _RT_DEFS_H_
#define _RT_DEFS_H_

#include <refi/refi.h>

/*  Use this macro to get the next memory map descriptor
    Ex: To get the PhysicalStart field of 5th descriptor>>

    getMapDescriptor(Map, DescSize, 5)->PhysicalStart; (This will return the correct value)
    
    Don't get descriptor directly or it will cause compatibility problems
    Ex: (Map + 5)->PhysicalStart (Don't use)

    In the above example, Map is of type EFI_MEMORY_DESCRIPTOR* and DescSize is 
    the size of a descriptor that is returned by GetMemoryMap function
*/
#define GET_MEM_MAP_DESCRIPTOR(ptr, size, pos) ((EFI_MEMORY_DESCRIPTOR*)((uint8_t*)ptr + size * pos))

#define PAGESIZE 4096 
#define ALIGN(val, alignment) ((val + alignment - 1) & ~(alignment - 1))
#define page(num) PAGESIZE*4096

#define MAXCHARCOUNT 100

/* Common address access operation */
#define GET_1_BYTE(address) ((uint8_t*)(address))
#define GET_2_BYTES(address) ((uint16_t*)(address))
#define GET_4_BYTES(address) ((uint32_t*)(address))
#define GET_8_BYTES(address) ((uint64_t*)(address))


#define SET_1_BYTE(address) (*GET_1_BYTE(address))
#define SET_2_BYTES(address) (*GET_2_BYTES(address))
#define SET_4_BYTES(address) (*GET_4_BYTES(address))
#define SET_8_BYTES(address) (*GET_8_BYTES(address))



#endif