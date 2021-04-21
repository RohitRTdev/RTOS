#include <mm/phyMemtools.h>
#include <rclib.h>

static size_t n_desc;

//Finds the suitable block for initial memory setup
size_t* phy_block_finder(Map_descriptor *map)
{
    size_t i = 0;
    size_t address = ADDRESS_NOT_FOUND;
    n_desc = map->MapSize/map->DescSize;
    uint32_t type = 0;
    EFI_MEMORY_DESCRIPTOR *memmap = NULL;

    while(i < n_desc)
    {
        memmap = getMemMapDescriptor(map->Map, map->DescSize, i);
        type = memmap->Type;
        switch(type)
        {
            case EfiPersistentMemory:
            case EfiConventionalMemory:
            case EfiLoaderCode:
            case EfiBootServicesCode:
            case EfiBootServicesData:{
                if(memmap->NumberOfPages >= MAXBLOCKSETUP)
                {
                    address = memmap->PhysicalStart;
                    memmap->PhysicalStart = address + MAXBLOCKSETUP * PAGESIZE;
                    memmap->NumberOfPages -= MAXBLOCKSETUP;
                    break; 
                }
            }
        }
        i++;
    }
    return (size_t*)address;
}

//Sets up the physical memory system
SYS_ERROR phy_set_blocks(Map_descriptor *map, Super_Mem_desc *desc)
{
    size_t i = 0;
    EFI_MEMORY_DESCRIPTOR *memmap = NULL;
    free_mem_desc mem_desc;
    free_mem_desc *base_address = desc->free_desc;
    size_t type = 0;
    SYS_ERROR err_code = NO_ERROR;
    size_t allocated_size = 0;

    while(i < n_desc)
    {
        memmap = getMemMapDescriptor(map->Map, map->DescSize, i);
        type = memmap->Type;
        switch(type)
        {
            case EfiPersistentMemory:
            case EfiConventionalMemory:
            case EfiLoaderCode:
            case EfiBootServicesCode:
            case EfiBootServicesData:{
                    mem_desc.address = (size_t*)memmap->PhysicalStart;
                    mem_desc.pages = memmap->NumberOfPages;
                    *(base_address) = mem_desc;
                    base_address += 1;
                    allocated_size += 1;
                    desc->free_space += mem_desc.pages * PAGESIZE;
            }

        }
        i++;
    }
    if(allocated_size > MAXFREEDESCRIPTORS)
        err_code = MAXBLOCKOVERFLOW;
    desc->no_of_free_desc = allocated_size;

    return err_code;
}

void phy_defrag(Super_Mem_desc *desc)
{
    size_t i = 1;
    free_mem_desc *root_block = desc->free_desc;
    free_mem_desc *block_address = root_block;
    size_t no_of_blocks = desc->no_of_free_desc;
    while(i < no_of_blocks)
    {
        if((uint64_t)block_address[i].address == (uint64_t)root_block->address + root_block->pages * PAGESIZE)
        {
            root_block->pages += block_address[i].pages;
            block_address[i].pages = 0;
            desc->no_of_free_desc--;
        }
        else
        {   
            root_block = block_address + i;            
        }
        i++;

    }
}

SYS_ERROR smallest_fit(size_t* size_tmp, Super_Mem_desc *desc, void **block_address)
{
    size_t size = *size_tmp;
    size_t i = 0;
    size_t no_of_desc = desc->no_of_free_desc;
    free_mem_desc *root = desc->free_desc;
    free_mem_desc *good_enough = root;

    SYS_ERROR err_code = NO_ERROR;

    size_t block_no = 0;
    free_mem_desc *best_block = root;

    //Search for smallest block
    while(block_no < no_of_desc)
    {
        
        if(root[i].pages == 0)
        {
            i++;
            continue;
        }    
        if(size == root[i].pages * PAGESIZE)
        {
            best_block = root + i;
            break;
        }       
        else if(size < root[i].pages * PAGESIZE)
        {
            if(best_block->pages < size / PAGESIZE || best_block->pages > root[i].pages) 
                best_block = root + i;
        }
        else if(good_enough->pages < root[i].pages)
            good_enough = root + i;
        block_no++;
        i++;
        
    }
    *block_address = best_block;

    /*  AllocMem gives the biggest continuous block it can find 
        even if it is less than the requested size and hence  
        returns only a silent error. This is useful to the virtual memory allocator. 
    */ 

    if(best_block == root && root->pages < size / PAGESIZE)
    { 
        *block_address = good_enough; 
        *size_tmp = best_block->pages * PAGESIZE;
        err_code = NOT_REQUESTED_SIZE;  
    }
    return err_code;
}

static free_mem_desc* get_free_descriptor(Super_Mem_desc *desc)
{
    free_mem_desc *iterator_block = desc->free_desc;
    size_t iterator = 0;
    while(iterator < desc->maxdescriptors_free)
    {
        if(iterator_block[iterator].pages == 0)
            return iterator_block + iterator;
        iterator++;
    }
    return NULL;
}


SYS_ERROR defrag_at_free(free_mem_desc *free_block, Super_Mem_desc *global_desc)
{
    size_t i = 0;
    size_t no_of_desc = global_desc->no_of_free_desc;
    free_mem_desc *root = global_desc->free_desc;
    free_mem_desc *free_root_block = NULL;
    free_mem_desc *current_block = NULL;
    boolean virtual_block = true; 
    size_t *block_address = free_block->address;
    size_t pages = free_block->pages;

    /*
      * Virtual block represents a block that is not physically present in memory.
      * This is to allow defragmentation of a block that has just been freed as
      * that block is not on the free block list
    */
    SYS_ERROR err_code = NO_ERROR;

    uint64_t block_no = 0;
    while(true)
    {
        while(block_no < no_of_desc)
        {
            if(root[i].pages == 0)
            {
                i++;
                continue;
            }
            if(virtual_block)
            {
                if((size_t*)((uint8_t*)block_address + pages * PAGESIZE) == root[i].address)
                {
                    root[i].address = block_address;
                    root[i].pages += pages;
                    virtual_block = false;    //Once we get a matching block, we merge it
                    current_block = root + i; //to the member which makes it a physical block
                    break;
                }    
                else if((size_t*)((uint8_t*)root[i].address + root[i].pages * PAGESIZE) == block_address)
                {
                    root[i].pages += pages;
                    virtual_block = false;
                    current_block = root + i;
                    break;
                }
            }
            else
            {
                //This loop represents the defragmentation of physical blocks
                if((size_t*)((uint8_t*)current_block->address + current_block->pages * PAGESIZE) == root[i].address)
                {
                    root[i].address = current_block->address;
                    root[i].pages += current_block->pages;
                    current_block->address = 0;
                    current_block->pages = 0;
                    current_block = root + i;
                    global_desc->no_of_free_desc--;
                    break;
                }
                else if((size_t*)((uint8_t*)root[i].address + root[i].pages * PAGESIZE) == current_block->address)
                {
                    current_block->address = root[i].address;
                    current_block->pages += root[i].pages;
                    root[i].pages = 0;
                    root[i].address = 0;
                    global_desc->no_of_free_desc--;
                    break;
                }
            }
                        
            i++;
            block_no++;

        }
        if(no_of_desc == block_no)
            break;
        i = 0;
        block_no = 0;
        no_of_desc = global_desc->no_of_free_desc;

    }
    
    
    if(virtual_block)
    {
        //Get an empty block
        free_root_block = get_free_descriptor(global_desc);

        //We couldn't find any blocks to defrag 
    
        global_desc->no_of_free_desc++;
        free_root_block->address = block_address;
        free_root_block->pages = pages;
    
    }
         
    return err_code;
    
}

void init_free_blocks(Super_Mem_desc *desc)
{
    size_t i = 0;
    free_mem_desc *root_block = desc->free_desc;

    // Zero out all the free descriptors
    while(i < desc->maxdescriptors_free)
    {
        root_block[i++].pages = 0;
    }
    alloc_mem_desc *alloc_root_block = desc->alloc_desc;
    i = 0; 
    //Zero out all the alloc descriptors
    while(i < desc->maxdescriptors_alloc)
    {
        alloc_root_block[i++].total_pages = 0;
    }

}

void setup_AllocPool(AllocPoolHeader *block_ptr, uint64_t resc_size, boolean type, AllocPoolHeader *prev_node)
{
    block_ptr->sign = ALLC;
    block_ptr->max_resources = DEFAULT_MAX_RESOURCES;
    block_ptr->no_of_resources = 1;
    block_ptr->type = type;
    block_ptr->resc_size = resc_size;
    block_ptr->list_mem.This = block_ptr;
    if(type == SUB_NODE)
    {
        add_list_node(&prev_node->list_mem, &block_ptr->list_mem);
    }
    else
    {
        block_ptr->list_mem.next = NULL;
        block_ptr->list_mem.prev = NULL;
    }
    

    uint64_t resc_normalised = resc_size / 4;

    uint32_t *resc_ptr = (uint32_t*)((uint8_t*)block_ptr + SIZE_OF_POOL_HEADER);
    *resc_ptr = FLAG;
    resc_ptr += resc_normalised;

    uint64_t resc_count = 1;
    while(resc_count < block_ptr->max_resources)
    {
        *resc_ptr = REMD;
        resc_ptr += resc_normalised;
        resc_count++;
    }

}
