#include <mm/phyMem.h>
#include <mm/phyMemtools.h>
#include <rcommon.h>

static Super_Mem_desc global_desc;

SYS_ERROR phyMem_init(Map_descriptor *MemMap)
{
    SYS_ERROR err_code = NO_ERROR;

    //Set up Free blocks memory structures at low memory 

    uint64_t RT_block_addr = phy_block_finder(MemMap);
    if(RT_block_addr == ADDRESS_NOT_FOUND)
        return PHY_INSUFFICIENT_MEM;
    
    global_desc.free_desc = (Free_Mem_desc*)RT_block_addr;
    global_desc.size_free = SIZE_OF_FREE_BLOCK;
    global_desc.no_of_alloc_desc = 0;
    global_desc.free_space = 0;

    //Set up free section
   
    Free_Mem_desc *mem = global_desc.free_desc;

    global_desc.maxblocksize = MAXBLOCKSETUP;
    global_desc.maxdescriptors = MAXDESCRIPTORS;

    init_free_blocks(mem, &global_desc);   

    err_code = phy_set_blocks(MemMap, (Free_Mem_desc*)RT_block_addr, &global_desc.no_of_free_desc, &global_desc);
    RT_INFO(err_code)
    
    phy_defrag(&global_desc, mem);

    /* We set up allocation algorithm to first fit as we want allocator to provide us with lower 
       memory addresses during early initialisation. This is implemented to avoid heap and stack
       collisions as stack is normally placed in higher addresses. 
    */

    global_desc.allocation_algorithm = FIRST_FIT;

    return err_code;
}

SYS_ERROR AllocMem(size_t *size_ptr, void **buffer)
{
    SYS_ERROR err_code = NO_ERROR;
    size_t size = *size_ptr;

    if(size == 0)
        return INVALID_PARAMETERS;
    
    if(size > global_desc.free_space)
        return PHY_INSUFFICIENT_MEM;

    size += SIZE_OF_ALLOCATED_BLOCK;  //Include the size of the free block header we're using

    size_t size_rounded = ralign_op(size, PAGESIZE); //Size aligned to a page in bytes
    Free_Mem_desc *free_block_desc = NULL;
    Free_block *free_block = NULL;

    err_code = smallest_fit(&size_rounded, &global_desc, (void**)&free_block_desc);
    if(err_code != NOT_REQUESTED_SIZE)    
    {
        RT_INFO(err_code)
    }        
    else
    {
        *size_ptr = size_rounded - SIZE_OF_ALLOCATED_BLOCK; //This indicates the amount of space we were able to afford
        size = size_rounded;
    }    

    //Update the free block descriptor and get free block address
    free_block_desc->pages -= size_rounded / PAGESIZE;
    free_block = free_block_desc->address;
    free_block_desc->address = (Free_block*)((uint64_t)free_block_desc->address + size_rounded);
    if(free_block_desc->pages == 0)
        global_desc.no_of_free_desc--;

    //Set up free block header
    free_block->signature = SIGNATURE;
    free_block->size_used = size - SIZE_OF_ALLOCATED_BLOCK;
    free_block->total_size = size_rounded;
    free_block->state = NOT_FREE;

    global_desc.no_of_alloc_desc++;
    
    global_desc.free_space -= size_rounded;

    *buffer = (void*)((uint64_t)free_block + SIZE_OF_ALLOCATED_BLOCK);
    
    return err_code;
}

SYS_ERROR FreeMem(void *buffer)
{
    SYS_ERROR err_code = NO_ERROR;

    Free_block *free_block = (Free_block*)((uint64_t)buffer - SIZE_OF_ALLOCATED_BLOCK);
    if(free_block->signature != SIGNATURE || free_block->state == FREE)
    {
        return INVALID_PARAMETERS;
    }
    
    size_t block_address;
    size_t pages;

    //Free the free_block_header
 
    free_block->state = FREE;
    free_block->size_used = 0;
    block_address = (size_t)free_block;
    pages = free_block->total_size / PAGESIZE; 
    free_block->total_size = 0;
    global_desc.no_of_alloc_desc--;

    defrag_at_free(block_address, pages, &global_desc);

    global_desc.free_space += pages * PAGESIZE;

    //Relocate the entire memory block if the descriptors take up all the space
    

    if(global_desc.no_of_free_desc == global_desc.maxdescriptors)
    {
        err_code = relocate_main_block(&global_desc);
    }           
    
    return err_code;
}


SYS_ERROR ReAllocMem(size_t* size, void **buffer)
{
    SYS_ERROR error_code = NO_ERROR;
    error_code = FreeMem(*buffer);
    if(RT_ERROR(error_code))
    {
        *buffer = NULL;
        return INVALID_PARAMETERS;
    }    
    
    error_code = AllocMem(size, buffer);
    if(RT_ERROR(error_code))
    {
        *buffer = NULL;
        return PHY_INSUFFICIENT_MEM;
    }
    return error_code;

} 
/*
* This allows us to bypass the memory protocols and directly
* add a free member to the free list 
*/
void add_free_mem_entry(size_t size, void *address)  
{                                                       
    Free_Mem_desc *root = global_desc.free_desc;

    while(root->pages != 0)
        root += 1;

    root->address = address;
    root->pages = size / PAGESIZE;
    
}


//Allows one to change allocation algorithm from first-fit to small-fit and vice versa
void allocation_algorithm(boolean allocation_algorithm)
{
    global_desc.allocation_algorithm = allocation_algorithm;   
}