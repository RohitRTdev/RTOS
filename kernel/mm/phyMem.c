#include <mm/mm.h>
#include <mm/phyMem.h>
#include <mm/phyMemtools.h>
#include <rclib.h>

static Super_Mem_desc global_desc;
static boolean destroy_data;

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
    destroy_data = false;

    return err_code;
}

SYS_ERROR AllocMem(size_t *size_ptr, void **buffer, size_t alignment)
{
    SYS_ERROR err_code = NO_ERROR;
    size_t size = *size_ptr;
    size_t size_aligned = size;
    boolean aligned = alignmentcheck(alignment) && (alignment <= PAGESIZE);

    if(size == 0 || !aligned)
        return INVALID_PARAMETERS;
    
    if(size > global_desc.free_space)
        return PHY_INSUFFICIENT_MEM;

    size_t alloc_header = (alignment >= DEFAULT_ALIGNMENT)?ralign_op(SIZE_OF_ALLOCATED_BLOCK, alignment):SIZE_OF_ALLOCATED_BLOCK;    

    size += SIZE_OF_ALLOCATED_BLOCK; //Includes the size of the free block header we're using
    size_aligned += alloc_header;    //Includes the size of the aligned free block header


    size_t size_rounded = ralign_op(size, PAGESIZE); //Size aligned to a page in bytes
    size_t size_rounded_aligned = ralign_op(size_aligned, PAGESIZE);

    Free_Mem_desc *free_block_desc = NULL;
    Free_block *free_block = NULL;

    boolean alignment_success = false;
    
    if(alloc_header != SIZE_OF_ALLOCATED_BLOCK)
    {
        err_code = smallest_fit(&size_rounded_aligned, &global_desc, (void**)&free_block_desc);
        if(RT_ERROR(err_code))
        {
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
        }
        else
        {
            size_rounded = size_rounded_aligned;
            size = size_aligned;
        }
        alignment_success = true;
    }
    else
    {
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
    }
   
   

    //Update the free block descriptor and get free block address
    free_block_desc->pages -= size_rounded / PAGESIZE;
    free_block = free_block_desc->address;
    free_block_desc->address = (Free_block*)((uint64_t)free_block_desc->address + size_rounded);
    if(free_block_desc->pages == 0)
        global_desc.no_of_free_desc--;

    //Set up free block header
    free_block->signature = SIGNATURE;
    free_block->size_used = size - alloc_header;
    free_block->total_size = size_rounded;
    free_block->state = NOT_FREE;

    if(alignment_success)
        free_block->alignment = alignment;
    else
        free_block->alignment = DEFAULT_ALIGNMENT;

    global_desc.no_of_alloc_desc++;
    
    global_desc.free_space -= size_rounded;

    *buffer = (void*)((uint64_t)free_block + alloc_header);
    *(size_t*)((uint8_t*)buffer - 8) = (size_t)free_block;
    
    return err_code;
}

SYS_ERROR FreeMem(void *buffer)
{
    SYS_ERROR err_code = NO_ERROR;

    Free_block *free_block = (Free_block*)*(size_t*)((uint8_t*)buffer - 8); 

    if(free_block->signature != SIGNATURE || free_block->state == FREE)
    {
        return INVALID_PARAMETERS;
    }
    
    size_t block_address;
    size_t pages;

    //Free the free_block_header
 
    free_block->state = FREE;
    block_address = (size_t)free_block;
    pages = free_block->total_size / PAGESIZE; 

    if(destroy_data)
    {
        free_block->size_used = 0;
        free_block->total_size = 0;
    }
        
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


SYS_ERROR ReAllocMem(size_t* size, void **buffer, size_t alignment)
{
    SYS_ERROR error_code = NO_ERROR;

    destroy_data = false;

    error_code = FreeMem(*buffer);

    destroy_data = true;
    if(RT_ERROR(error_code))
    {
        *buffer = NULL;
        return INVALID_PARAMETERS;
    }    
    Free_block *old_block = (Free_block*)*(size_t*)((uint8_t*)buffer - 8);
    size_t size_to_copy = old_block->size_used;
    size_t alignment_performed = old_block->alignment;

    void *buffer_start = ((uint8_t*)old_block + ralign_op(SIZE_OF_ALLOCATED_BLOCK, alignment_performed));
    
    error_code = AllocMem(size, buffer, alignment);
    if(RT_ERROR(error_code))
    {
        *buffer = NULL;
        return PHY_INSUFFICIENT_MEM;
    }
    Free_block *new_block = (Free_block*)*(size_t*)((uint8_t*)buffer - 8);
    //Copy all data from old to new buffer if new address is different

    if(old_block != new_block)
        rmemcpy((void*)*buffer, buffer_start, size_to_copy);


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
                err_code = AllocMem(&size_req, (void**)&resc_ptr, DEFAULT_ALIGNMENT);
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
        err_code = AllocMem(&size_used, (void**)&buf, DEFAULT_ALIGNMENT);

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
        return INVALID_PARAMETERS;
    }

    return err_code;
}


//Allows one to change allocation algorithm from first-fit to small-fit and vice versa
void allocation_algorithm(boolean allocation_algorithm)
{
    global_desc.allocation_algorithm = allocation_algorithm;   
}
