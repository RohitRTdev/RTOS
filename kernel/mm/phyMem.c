#include <mm/mm.h>
#include <mm/phyMem.h>
#include <mm/phyMemtools.h>
#include <rclib.h>

static Super_Mem_desc global_desc;
static boolean destroy_data;

//TODO: Add suitable code to most functions to handle condition where we run out of descriptor space

SYS_ERROR phyMem_init(Map_descriptor *MemMap)
{
    SYS_ERROR err_code = NO_ERROR;

    //Set up Free blocks memory structures at low memory 

    size_t *RT_block_addr = phy_block_finder(MemMap);

    if((size_t)RT_block_addr == ADDRESS_NOT_FOUND)
        return PHY_INSUFFICIENT_MEM;
    
    global_desc.free_desc = (free_mem_desc*)RT_block_addr;
    global_desc.alloc_desc = (alloc_mem_desc*)((uint8_t*)RT_block_addr + SIZE_OF_FREE_DESCRIPTOR * MAXFREEDESCRIPTORS);
    global_desc.no_of_alloc_desc = 0;
    global_desc.free_space = 0;

    //Set up free section

    global_desc.maxblocksize = MAXBLOCKSETUP;
    global_desc.maxdescriptors_free = MAXFREEDESCRIPTORS;
    global_desc.maxdescriptors_alloc = MAXALLOCDESCRIPTORS;

    init_free_blocks(&global_desc);   

    err_code = phy_set_blocks(MemMap, &global_desc);
    RT_INFO(err_code)
    
    phy_defrag(&global_desc);

    destroy_data = false;

    return err_code;
}



static alloc_mem_desc* get_free_alloc_descriptor()
{
    size_t iterator = 0;
    alloc_mem_desc *iterator_block = global_desc.alloc_desc;
    while(iterator < global_desc.maxdescriptors_alloc)
    {
        //TODO: Handle the condition where there is no free alloc descriptors left
        if(iterator_block[iterator++].total_pages == 0)
            return iterator_block + iterator - 1;
    }
    return NULL;
}

static alloc_mem_desc* get_allocated_block(void *block_address)
{
    alloc_mem_desc *iterator_block = global_desc.alloc_desc;
    size_t iterator = 0;
    while(iterator < global_desc.maxdescriptors_alloc)
    {
        if(iterator_block[iterator].address == block_address)
            return iterator_block + iterator;
        iterator++;
    }
    return NULL;
}

/* 
   AllocMem takes a size parameter and tries it's best to give 
   a continuous physical range of pages. In the event it can't,
   it will return a NOT_REQUESTED_SIZE error and the amount of 
   size it could get in size_ptr. Note that it always returns 
   a multiple of PAGESIZE, which means even if you allocate 
   less than PAGESIZE, it still takes up one PAGESIZE
*/

SYS_ERROR AllocMem(size_t *size_ptr, void **buffer)
{
    if(*size_ptr == 0)
        return INVALID_PARAMETERS;

    if(*size_ptr > global_desc.free_space || global_desc.no_of_alloc_desc == MAXALLOCDESCRIPTORS)
        return PHY_INSUFFICIENT_MEM;

    SYS_ERROR err_code = NO_ERROR;
    size_t sizeToAllocate = *size_ptr;
    size_t roundedSize = ralign_op(sizeToAllocate, PAGESIZE);

    free_mem_desc *free_block = NULL;
    
    err_code = smallest_fit(&roundedSize, &global_desc, (void**)&free_block);
    if(err_code != NOT_REQUESTED_SIZE)
    {
        RT_INFO(err_code)
    }
    else
    {
        *size_ptr = roundedSize; //This indicates the amount of space we were able to afford
        sizeToAllocate = roundedSize;
    }

    // We update the alloc descriptor region with our new block

    alloc_mem_desc *allocated_block = NULL;

    allocated_block = get_free_alloc_descriptor();
    if(allocated_block == NULL)
        return PHY_INSUFFICIENT_MEM;

    allocated_block->address = free_block->address;
    allocated_block->size_used = sizeToAllocate;
    allocated_block->total_pages = roundedSize / PAGESIZE;

    global_desc.no_of_alloc_desc++;

    //We update the free block descriptor

    free_block->pages -= roundedSize / PAGESIZE;
    if(free_block->pages == 0)
    {
        global_desc.no_of_free_desc--;

        if(destroy_data)
            free_block->address = NULL;
    }
         
    //Update how much free space is remaining

    global_desc.free_space -= roundedSize;

    //Give the caller the requested buffer address
    *buffer = free_block->address;

    return err_code;

}

SYS_ERROR FreeMem(void *buffer)
{
    SYS_ERROR err_code = NO_ERROR;

    alloc_mem_desc *allocated_block = NULL;

    allocated_block = get_allocated_block(buffer);
    if(allocated_block == NULL)
        return INVALID_PARAMETERS;             
    
    //Create and update the free block descriptor
    free_mem_desc free_block = {allocated_block->address, allocated_block->total_pages};
     
    //Free the allocated block
    allocated_block->total_pages = 0;

    //For additional protection
    if(destroy_data)
    {
        allocated_block->size_used = 0;
        allocated_block->address = NULL;
    }
        
    global_desc.no_of_alloc_desc--;

    err_code = defrag_at_free(&free_block, &global_desc);
    if(err_code == MAXBLOCKOVERFLOW)
        err_code = PHY_INSUFFICIENT_MEM;

    global_desc.free_space += free_block.pages * PAGESIZE;

    //TODO: Handle condition where there is no space in the free block descriptor region
            
    return err_code;
}
/* 
   ReAllocMem takes in an old buffer and reinitialises it to a newer size,
   possibly copying all of the contents in the old buffer to the new buffer 
   if necessary.
*/

SYS_ERROR ReAllocMem(size_t* size, void **buffer)
{
    SYS_ERROR error_code = NO_ERROR;

    destroy_data = false;
    
    void *buffer_start_old = *buffer;
    alloc_mem_desc* old_block = get_allocated_block(buffer);

    size_t size_to_copy = old_block->size_used;

    error_code = FreeMem(*buffer);

    destroy_data = true;

    if(RT_ERROR(error_code))
    {
        *buffer = NULL;
        return INVALID_PARAMETERS;
    }    
    
    
    error_code = AllocMem(size, buffer);
    //TODO: Handle condition where we don't get requested size of continuous pages
    if(RT_ERROR(error_code))
    {
        *buffer = NULL;
        return PHY_INSUFFICIENT_MEM;
    }
    //Copy all data from old to new buffer if new address is different

    if(buffer_start_old != *buffer)
        rmemcpy((void*)*buffer, buffer_start_old, size_to_copy);

    return error_code;

} 
/*
* This allows us to bypass the memory protocols and directly
* add a free member to the free list 
*/
void add_free_mem_entry(size_t size, size_t address)  
{                                                     
    size_t roundedSize = ralign_op(size, PAGESIZE);  
    free_mem_desc root = {(void*)address, roundedSize / PAGESIZE};

    defrag_at_free(&root, &global_desc);

    global_desc.free_space += roundedSize;
    
}

void add_allocated_mem_entry(size_t size, size_t address)
{
    size_t roundedSize = ralign_op(size, PAGESIZE);
    alloc_mem_desc *allocated_block = NULL;

    allocated_block = get_free_alloc_descriptor();

    allocated_block->address = (void*)address;
    allocated_block->size_used = size;
    allocated_block->total_pages = roundedSize / PAGESIZE;

    global_desc.no_of_alloc_desc++;
    global_desc.free_space -= roundedSize;
}


