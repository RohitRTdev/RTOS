#include <mm/phyMemtools.h>
#include <logging/basic_print.h>
#include <rmemory.h>

static uint64_t n_desc;

//Finds the suitable block for initial memory setup
uint64_t phy_block_finder(Map_descriptor *map)
{
    uint64_t i = 0;
    uint64_t address = ADDRESS_NOT_FOUND;
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
    return address;
}

//Sets up the physical memory system
SYS_ERROR phy_set_blocks(Map_descriptor *map, Free_Mem_desc* base_address, uint64_t *no_of_desc, Super_Mem_desc *desc)
{
    uint64_t i = 0;
    EFI_MEMORY_DESCRIPTOR *memmap = NULL;
    Free_Mem_desc mem_desc;
    uint64_t type = 0;
    SYS_ERROR err_code = NO_ERROR;
    uint64_t allocated_size = 0;

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
                    mem_desc.address = (Free_block*)memmap->PhysicalStart;
                    mem_desc.pages = memmap->NumberOfPages;
                    *(base_address) = mem_desc;
                    base_address += 1;
                    allocated_size += 1;
                    desc->free_space += mem_desc.pages * PAGESIZE;
            }

        }
        i++;
    }
    if(allocated_size > MAXDESCRIPTORS)
        err_code = MAXBLOCKOVERFLOW;
    *no_of_desc = allocated_size;

    return err_code;
}

void phy_defrag(Super_Mem_desc *desc, Free_Mem_desc *block_address)
{
    uint64_t i = 1;
    Free_Mem_desc *root_block = block_address;
    uint64_t no_of_blocks = desc->no_of_free_desc;
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
    Free_Mem_desc *root = desc->free_desc;
    Free_Mem_desc *good_enough = root;

    SYS_ERROR err_code = NO_ERROR;

    size_t block_no = 0;
    Free_Mem_desc *best_block = root;

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
            if(desc->allocation_algorithm == FIRST_FIT)
            {
                best_block = root + i;
                break;
            }
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
        even if it is less than the requested size and hence doesn't 
        return an error. This is useful to the virtual memory allocator. 
    */ 

    if(best_block == root && root->pages < size / PAGESIZE)
    { 
        *block_address = good_enough; 
        *size_tmp = best_block->pages * PAGESIZE;
        err_code = NOT_REQUESTED_SIZE;  
    }
    return err_code;
}


SYS_ERROR defrag_at_free(size_t block_address, size_t pages, Super_Mem_desc *global_desc)
{
    size_t i = 0;
    size_t no_of_desc = global_desc->no_of_free_desc;
    Free_Mem_desc *root = global_desc->free_desc;
    Free_Mem_desc *free_root_block = NULL;
    Free_Mem_desc *current_block = NULL;
    boolean virtual_block = true; 

    /*
      * Virtual block represents a block that is not physically present in memory.
      * This is to allow defragmentation of a block that has just been freed as
      * that block is not on the free block list
    */

    uint64_t allocated_blocks = 0;
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
                if(block_address + pages * PAGESIZE == (size_t)root[i].address)
                {
                    root[i].address = (Free_block*)block_address;
                    root[i].pages += pages;
                    virtual_block = false;    //Once we get a matching block, we merge it
                    current_block = root + i; //to the member which makes it a physical block
                    break;
                }    
                else if((size_t)root[i].address + root[i].pages * PAGESIZE == block_address)
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
                if((size_t)current_block->address + current_block->pages * PAGESIZE == (size_t)root[i].address)
                {
                    root[i].address = current_block->address;
                    root[i].pages += current_block->pages;
                    current_block->address = 0;
                    current_block->pages = 0;
                    current_block = root + i;
                    global_desc->no_of_free_desc--;
                    break;
                }
                else if((size_t)root[i].address + root[i].pages * PAGESIZE == (size_t)current_block->address)
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
        root = global_desc->free_desc;
        while(root->pages != 0)
        {
            root += 1;
            allocated_blocks++;
            if(allocated_blocks == global_desc->maxdescriptors)
            {
                return MAXBLOCKOVERFLOW;
            }
        }
        free_root_block = root;

        //We couldn't find any blocks to defrag 
    
        global_desc->no_of_free_desc++;
        free_root_block->address = (Free_block*)block_address;
        free_root_block->pages = pages;
    
    }
         
    return err_code;
    
}

void init_free_blocks(Free_Mem_desc *mem, Super_Mem_desc *desc)
{
    size_t i = 0;

    while(i < desc->maxdescriptors)
    {
        mem[i++].pages = 0;
    }

}

SYS_ERROR relocate_main_block(Super_Mem_desc *desc)
{
    SYS_ERROR err_code = NO_ERROR;
    uint64_t new_address;

    Free_Mem_desc *root = desc->free_desc;

    while(true)
    {
        if(root->pages >= desc->maxblocksize + 2)
        {
            new_address = (uint64_t)root->address;
            break;
        }
        root += 1;
    }

    desc->maxblocksize += 2;
    desc->maxdescriptors = (desc->maxblocksize * PAGESIZE) / SIZE_OF_FREE_BLOCK;

    init_free_blocks((Free_Mem_desc*)root->address, desc);

    uint64_t desc_offset = (uint64_t)root - (uint64_t)desc->free_desc;
    
    rmemcpy((void*)new_address, (void*)desc->free_desc, (desc->maxblocksize - 2) * PAGESIZE);
    
    size_t old_address = (size_t)desc->free_desc;
    size_t pages = (size_t)(desc->maxblocksize - 2);

    desc->free_desc = (Free_Mem_desc*)new_address;

    root = desc->free_desc;

    Free_Mem_desc *root_offset = (Free_Mem_desc*)((uint64_t)root + desc_offset);
    root_offset->address += desc->maxblocksize * PAGESIZE;
    root_offset->pages -= desc->maxblocksize;


    if(root_offset->pages == 0)
        desc->no_of_free_desc--;
    
    err_code = defrag_at_free(old_address, pages, desc);
    
    desc->free_space -= PAGESIZE * 2;
    return err_code;

}