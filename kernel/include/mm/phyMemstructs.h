#ifndef _PHY_MEM_STRUCTS_H_
#define _PHY_MEM_STRUCTS_H_

#include <kernel.h>
#include <rclib.h>

#define ALLC 0x434c4c41 
#define REMD 0x444d4552
#define FLAG 0x47414c46

#define MAXBLOCKSETUP 4

#define MAXBLOCKOVERFLOW 0x02
#define ROOT_MEMBER_NOT_FOUND 0x03

#define MAIN_NODE true
#define SUB_NODE false

#define DEFAULT_MAX_RESOURCES 10

typedef struct{           
    size_t *address;       //Address to the free block
    size_t pages;              //Number of continuous pages  
}free_mem_desc;

typedef struct{
    size_t *address;
    size_t total_pages;
    size_t size_used;
}alloc_mem_desc;

typedef struct{
    uint32_t sign;
    uint64_t no_of_resources;
    uint64_t resc_size;
    uint64_t max_resources;
    List list_mem;
    boolean type;
}AllocPoolHeader;

#define SIZE_OF_FREE_DESCRIPTOR sizeof(free_mem_desc)
#define SIZE_OF_ALLOC_DESCRIPTOR sizeof(alloc_mem_desc)
#define MAXFREEDESCRIPTORS (((MAXBLOCKSETUP / 2) * PAGESIZE) / SIZE_OF_FREE_DESCRIPTOR)
#define MAXALLOCDESCRIPTORS (((MAXBLOCKSETUP / 2)* PAGESIZE) / SIZE_OF_ALLOC_DESCRIPTOR)

#define SIZE_OF_POOL_HEADER ALIGN(sizeof(AllocPoolHeader), 16)
#define RESC_SIZE(resc_size) (resc_size * DEFAULT_MAX_RESOURCES + SIZE_OF_POOL_HEADER)

//This is a global descriptor for all the above memory descriptors
typedef struct{
    free_mem_desc *free_desc;
    alloc_mem_desc *alloc_desc;        
    size_t no_of_free_desc;
    size_t no_of_alloc_desc;
    size_t maxblocksize;
    size_t maxdescriptors_free;
    size_t maxdescriptors_alloc;   
    size_t free_space; 
}Super_Mem_desc;


#endif