#ifndef _PHY_MEM_STRUCTS_H_
#define _PHY_MEM_STRUCTS_H_

#include <rtypes.h>
#include <kernel.h>

#define SIGNATURE 0x45455246 //"FREE"(In little endian)

#define FREE 1
#define NOT_FREE 0

#define MAXBLOCKSETUP 4

#define MAXBLOCKOVERFLOW 0x02
#define ROOT_MEMBER_NOT_FOUND 0x03

#define FIRST_FIT true
#define SMALLEST_FIT false

typedef struct _Free_block Free_block;
typedef struct _Free_Mem_desc Free_Mem_desc;

struct _Free_block{
    uint32_t signature;     //"FREE"
    uint8_t state;          //free/not
    uint64_t total_size;
    uint64_t size_used; 
};

struct _Free_Mem_desc{           
    Free_block *address;         //Address to the free block
    uint64_t pages;              //Number of continuous pages  
};

#define SIZE_OF_FREE_BLOCK ALIGN(sizeof(Free_Mem_desc), 16)
#define SIZE_OF_ALLOCATED_BLOCK ALIGN(sizeof(Free_block), 16)
#define MAXDESCRIPTORS (MAXBLOCKSETUP * PAGESIZE / SIZE_OF_FREE_BLOCK)

#define BLOCK_SIZE(size) (size - SIZE_OF_ALLOCATED_BLOCK)

//This is a global descriptor for all the above memory descriptors
typedef struct{
    uint8_t allocation_algorithm;
    Free_Mem_desc *free_desc;        
    uint64_t size_free;
    uint64_t no_of_free_desc;
    uint64_t no_of_alloc_desc;
    uint64_t maxblocksize;
    uint64_t maxdescriptors;   
    uint64_t free_space; 
}Super_Mem_desc;


#endif