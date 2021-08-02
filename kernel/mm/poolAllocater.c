#include <mm/phyMem.h>
#include <mm/phyMemstructs.h>
#include <mm/phyMemtools.h>
#include <rclib/rclib.h>

/*
   Allocates a pool of resources which can have sizes which 
   are not multiples of a PAGESIZE. This is the recommended 
   function over AllocMem if you're allocating memory for 
   datastructures to be memory efficient 
*/ 

SYS_ERROR AllocPool(size_t resc_size, void **buffer, size_t *pool_id)
{
    size_t aligned_size = ALIGN(resc_size, 4);
    size_t resc_normalised = aligned_size / 4;
    AllocPoolHeader *header = NULL;
    uint32_t *resc_ptr = NULL;
    SYS_ERROR err_code = NO_ERROR;
    boolean new_block_setup = true;

    if(*pool_id != 0 )
    {
        header = (AllocPoolHeader*)(*pool_id - 1);
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

                *buffer = (uint8_t*)resc_ptr + SIZE_OF_POOL_HEADER;
            } 
            else
            {
                resc_ptr = (uint32_t*)((uint8_t*)block_ptr + SIZE_OF_POOL_HEADER);
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
        *pool_id = (uint64_t)buf + 1;
        *buffer = buf + SIZE_OF_POOL_HEADER;
    }    

    return err_code;
    
}

SYS_ERROR FreePool(void *buffer, size_t *pool_id)
{
    SYS_ERROR err_code = NO_ERROR;

    if(*pool_id == 0)
        return INVALID_PARAMETERS;

    AllocPoolHeader *header = (AllocPoolHeader*)(*pool_id - 1);
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
                    *pool_id = (uint64_t)block_ptr + 1;
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


