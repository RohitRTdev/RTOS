#include <mm/phyMem.h>
#include <mm/phyMemtools.h>
#include <rclib.h>
#include <logging/basic_print.h>

static Super_Mem_desc global_desc;
static uint64_t iter;

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
    iter = 1;

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
/* Allocates a pool of resources which can have sizes which 
   are not multiples of a PAGESIZE. This is the recommended 
   function over AllocMem if you're allocating memory for 
   datastructures to be memory efficient 
*/ 

SYS_ERROR AllocPool(size_t resc_size, void **buffer, uint64_t *pool_id)
{
    size_t aligned_size = ralign_op(resc_size, 4);
    size_t resc_normalised = aligned_size / 4;
    AllocPoolHeader *header = NULL;
    uint32_t *resc_ptr = NULL;
    SYS_ERROR err_code = NO_ERROR;
    boolean new_block_setup = true;

    if(*pool_id != 0 )
    {
        header = (AllocPoolHeader*)*pool_id;
        if(header->sign == ALLC && header->no_of_resources > 0)
        {
            if(header->resc_size != resc_size)
                return INVALID_PARAMETERS;
            size_t size_req = RESC_SIZE(aligned_size);
            AllocPoolHeader *block_ptr = header;
            //Search for an empty subblock
            while(block_ptr->list_mem.next != NULL && block_ptr->no_of_resources == block_ptr->max_resources)
            {
                block_ptr = block_ptr->list_mem.next->This;
            }
            
        
            if(block_ptr->no_of_resources == block_ptr->max_resources)
            {
                err_code = AllocMem(&size_req, (void**)&resc_ptr);
                RT_INFO(err_code)

                setup_AllocPool((AllocPoolHeader*)resc_ptr, aligned_size, SUB_NODE, block_ptr);

                *buffer = (uint8_t*)resc_ptr + SIZE_OF_ALLOC_HEADER;
            } 
            else
            {
                resc_ptr = (uint32_t*)((uint8_t*)block_ptr + SIZE_OF_ALLOC_HEADER);
                while(*resc_ptr != REMD) //Empty slots will have this particular signature
                {
                    resc_ptr += resc_normalised;
                }
                *resc_ptr = FLAG;
                block_ptr->no_of_resources += 1;
                *buffer = resc_ptr;
    
            }
            new_block_setup = false;
        
        }
        else
        {
            new_block_setup = true;
        }
        

    }    
    if(new_block_setup)
    {
        size_t size_used = RESC_SIZE(aligned_size);
        uint8_t *buf = NULL;
        err_code = AllocMem(&size_used, (void**)&buf);

        RT_INFO(err_code)

        setup_AllocPool((AllocPoolHeader*)buf, aligned_size, MAIN_NODE, NULL);
        *pool_id = (uint64_t)buf;
        *buffer = buf + SIZE_OF_ALLOC_HEADER;
    }    

    return err_code;
    
}

SYS_ERROR FreePool(void *buffer, uint64_t *pool_id)
{
    SYS_ERROR err_code = NO_ERROR;

    if(*pool_id == 0)
        return INVALID_PARAMETERS;

    AllocPoolHeader *header = (AllocPoolHeader*)*pool_id;
    AllocPoolHeader *block_ptr = header;
    uint32_t *resc_ptr = buffer;

    //Validate the pool id

    if(header->sign == ALLC && header->no_of_resources >= 1 && *resc_ptr != REMD)
    {
        *resc_ptr = REMD;
        header->no_of_resources -= 1;
        if(header->no_of_resources == 0)
        {
            if(header->type == MAIN_NODE)
            {
                if(header->list_mem.next == NULL && header->list_mem.prev == NULL) //This is the only node
                {
                    //Delete the whole pool
                    *pool_id = 0;
                }
                else
                {
                    //Goto next block and make it the main node
                    block_ptr = block_ptr->list_mem.next->This;
                    block_ptr->type = MAIN_NODE;
                    *pool_id = (uint64_t)block_ptr;
                    remove_list_node(&header->list_mem);
                }
            }
            else
            {
                remove_list_node(&header->list_mem);
            } 
            err_code = FreeMem(header);
        }
    }
    else
    {
        basic_print("header sign is %d and buffer sign is %d\r\n", header->sign, *resc_ptr);
        return INVALID_PARAMETERS;
    }

    return err_code;
}


//Allows one to change allocation algorithm from first-fit to small-fit and vice versa
void allocation_algorithm(boolean allocation_algorithm)
{
    global_desc.allocation_algorithm = allocation_algorithm;   
}