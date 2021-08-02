/* RT module loader */

#include <boot/file.h>
#include <boot/modules.h>
#include <boot/setup.h>
#include <rtos/rt-mod.h>
#include <rtos/defs.h>
#include <refilib/refilib.h>
#include <glib/rmemory.h>
#include <glib/rstrings.h>

entry_point kernel_entry;

static VOID read_rt_hdr(EFI_FILE_PROTOCOL* module_file_handle, VOID* hdr)
{
    UINTN rt_hdr_size = sizeof(rt_hdr);
    read_simple_file(module_file_handle, 0, &rt_hdr_size, hdr);
}

static VOID read_rt_section(EFI_FILE_PROTOCOL* module_file_handle, rt_sect_info* rt_sect, EFI_PHYSICAL_ADDRESS module_base_address)
{
    if(!(rt_sect->size_of_sect == 0 && rt_sect->virtual_address == 0 && rt_sect->ptr_to_sect == 0)) /* NULL section */
        read_simple_file(module_file_handle, rt_sect->ptr_to_sect, &rt_sect->size_of_sect, (void*)(module_base_address + rt_sect->virtual_address));
}

static VOID apply_rt_relocation(EFI_PHYSICAL_ADDRESS module_load_address, UINTN reloc_virtual_address)
{

#define SIZEOFRELOCENTRY 2 
    if(reloc_virtual_address != 0)
    {
        UINT32* absolute_reloc_base = GET_4_BYTES(module_load_address + reloc_virtual_address);

        UINT32 page_rva = *absolute_reloc_base;
        UINT32 block_size = *(absolute_reloc_base + 1);

        UINT32 remaining_block_size = block_size - sizeof(UINT64);
        UINT16* reloc_entry_pointer = GET_2_BYTES(absolute_reloc_base + 2);

        
        while(remaining_block_size > 0)
        {
            UINT16 reloc_offset = 0;
            UINT64 direct_value = 0;
            
            if(((*reloc_entry_pointer & 0xf000) >> 12) == IMAGE_REL_BASED_DIR64)
            {
                reloc_offset = *reloc_entry_pointer & 0x0fff;
                direct_value = *GET_8_BYTES(module_load_address + page_rva + reloc_offset);
                direct_value += module_load_address; 

                SET_8_BYTES(module_load_address + page_rva + reloc_offset) = direct_value;
            }
            remaining_block_size -= SIZEOFRELOCENTRY; /* Each reloc entry is 2 bytes */
            reloc_entry_pointer++;
        }
    }
}

static EFI_STATUS rt_load(EFI_FILE_PROTOCOL* module_file_handle, const boot_time_modules* kernel_module)
{
    rt_hdr rt_hdr_buffer;
    read_rt_hdr(module_file_handle, &rt_hdr_buffer);

    if(rstrcmp(rt_hdr_buffer.rt_sign, RT_SIGN) != 0 || rt_hdr_buffer.image_size == 0) /* Not a valid RT file */
    {
        return UNSUPPORTED_EXECUTABLE_FORMAT;
    }

    EFI_PHYSICAL_ADDRESS rt_module_load_base;
    UINTN module_image_entry = rt_hdr_buffer.image_entry;

    EFI_STATUS op_status = allocate_loader_pages(rt_hdr_buffer.image_size, &rt_module_load_base);
    EFI_FATAL_REPORT(L"Unable to allocate memory for RT module", op_status);

    rzeromem((void*)rt_module_load_base, rt_hdr_buffer.image_size); 

    UINTN reloc_virtual_address = 0;

    /* Load sections */
    for(int i = 0; i < TOTAL_SECTIONS; i++)
    {
        if(rstrcmp(rt_hdr_buffer.rt_sections[i].sect_name, ".bss") != 0) /* .bss is non-loadable section */
        {
            read_rt_section(module_file_handle, &rt_hdr_buffer.rt_sections[i], rt_module_load_base);
        }

        if(!rstrcmp(rt_hdr_buffer.rt_sections[i].sect_name, ".reloc"))
        {
            reloc_virtual_address = rt_hdr_buffer.rt_sections[i].virtual_address;
        }

    }

    apply_rt_relocation(rt_module_load_base, reloc_virtual_address);


    if(!rstrcmp(kernel_module->module_name, "RTcore"))
    {
        kernel_entry = (entry_point)(module_image_entry + rt_module_load_base);
    }

    add_boot_module(kernel_module->module_name, KERNEL, kernel_module->module_path, (VOID*)rt_module_load_base, (VOID*)(module_image_entry + rt_module_load_base), rt_hdr_buffer.image_size, (VOID*)(reloc_virtual_address + rt_module_load_base), NULL);
    

    return EFI_SUCCESS;
}



EFI_STATUS rt_loadfile(EFI_HANDLE device_handle, const boot_time_modules* kernel_module)
{
    EFI_FILE_PROTOCOL *module_file_handle = NULL;
    EFI_STATUS kernel_module_load_status = EFI_SUCCESS;
    CHAR16* file_path = kernel_module->module_path;

    module_file_handle = openfile(device_handle, file_path);  //Get file handle to kernel 
    
    kernel_module_load_status = rt_load(module_file_handle, kernel_module);   //Load kernel module

    module_file_handle->Close(module_file_handle); //Close kernel file handle

    return kernel_module_load_status;
}
