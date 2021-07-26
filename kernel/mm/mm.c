#include <mm/mm.h>
#include <mm/phyMem.h>
#include <mm/gdt.h>
#include <rmemory.h>
#include <utils.h>
#include <logging/basic_print.h>

static meminfo MemInfo;

static uint64_t RAM_calc(Map_descriptor *map)
{
    uint64_t n_desc = map->MapSize/map->DescSize;
    uint64_t pages = 0;
    uint64_t i = 0;
    while(i < n_desc)
    {   
        pages += getMemMapDescriptor(map->Map, map->DescSize, i)->NumberOfPages;
        i++;
    }
    return pages * PAGESIZE;
}

static SYS_ERROR set_up_gdt()
{
    //Sets up a flat memory model
    segment_descriptor generic_user_descriptor;
    gdt_register gdt_reg;

    //Remove the old GDT set up by the firmware

    store_gdt(&gdt_reg);

    uint8_t *old_gdt_base_address = (uint8_t*)ralign_op(gdt_reg.base_address, 4096);

    old_gdt_base_address = ((uint64_t)old_gdt_base_address > gdt_reg.base_address)?old_gdt_base_address - 1: old_gdt_base_address;
    
    FreeMem((void*)old_gdt_base_address);

    rzeromem((void*)&generic_user_descriptor, sizeof(segment_descriptor)); //Zero the descriptor 

    size_t gdt_allocation_size = GDT_DEFAULT_SIZE;
    segment_descriptor *gdt_ptr = NULL; //GDT is aligned to 8 bytes by default

    SYS_ERROR gdt_alloc_error = AllocMem(&gdt_allocation_size, (void**)&gdt_ptr);
    RT_INFO(gdt_alloc_error)

    //NULL descriptor
    gdt_ptr[0] = generic_user_descriptor;


    //Kernel code segment
    generic_user_descriptor.des_type = USER_SEGMENT;
    generic_user_descriptor.def_op_size = normalopsize;
    generic_user_descriptor.code_seg_bit = sixtyfourbitmode;
    generic_user_descriptor.dpl = RING0;
    generic_user_descriptor.type = (CODE_SEG << 3 ) | (NONCONFORMINGCODESEG << 2);

    gdt_ptr[1] = generic_user_descriptor;

    //Kernel data segment
    generic_user_descriptor.type = (DATA_SEG << 3);
    generic_user_descriptor.seg_present = SEGMENTPRESENT;

    gdt_ptr[2] = generic_user_descriptor;

    //User code segment
    generic_user_descriptor.type = (CODE_SEG << 3) | (NONCONFORMINGCODESEG << 2);
    generic_user_descriptor.dpl = RING3;

    gdt_ptr[3] = generic_user_descriptor;

    //User data segment
    generic_user_descriptor.type = (DATA_SEG << 3);

    gdt_ptr[4] = generic_user_descriptor;

    MemInfo.GDT_descriptors = 5;

    //Update the location and size of new GDT
    gdt_reg.limit = MemInfo.GDT_descriptors * sizeof(segment_descriptor) - 1; 
    gdt_reg.base_address = (uint64_t)gdt_ptr;

    load_gdt(&gdt_reg);

    return NO_ERROR;    
}

SYS_ERROR mm_init(Map_descriptor *map)
{
    SYS_ERROR err_code = NO_ERROR;
    MemInfo.RAM = RAM_calc(map);
    basic_print("ram:%d\r\n", MemInfo.RAM);
    
    err_code = phyMem_init(map);  //Initialise physical memory
    RT_INFO(err_code)

    err_code = set_up_gdt();    //Set up a flat model


    return err_code;
}
