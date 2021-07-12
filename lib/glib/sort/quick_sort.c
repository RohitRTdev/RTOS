#include <glib/rcommon.h>

//Note that the given functions assume that the member within the struct which it is to be sorted by is of 8 bytes

static void quick_sort_int(void *start, void* end, st offset, st start_offset)
{
    st *piv_addr = end;
    u8 *iter_ptr = start;
    st *last_saved = NULL;

    st *struct_address = NULL, *struct_address_pivot = NULL;

    for(iter_ptr = start; (void*)iter_ptr <= end; iter_ptr += offset)
    {
        if((st*)iter_ptr != piv_addr)
        {
            struct_address = (st*)(iter_ptr - start_offset);
            struct_address_pivot = (st*)((u8*)piv_addr - start_offset);
            if(*(st*)iter_ptr > *piv_addr && (st*)iter_ptr < piv_addr)
            {
                swap(struct_address, struct_address_pivot, offset);
                piv_addr = (st*)iter_ptr;
                if(last_saved != NULL)
                {
                    iter_ptr = ((u8*)last_saved - offset);
                    last_saved = NULL;
                }
            }
            else if(*(st*)iter_ptr < *piv_addr && (st*)iter_ptr > piv_addr)
            {
                swap(struct_address, struct_address_pivot, offset);
                piv_addr = (st*)iter_ptr;
                if(last_saved != NULL)
                {
                    iter_ptr = ((u8*)last_saved - offset);
                    last_saved = NULL;
                }
            }
            else
            {
                if(last_saved == NULL)
                {
                    last_saved = (st*)iter_ptr;
                }
            }
        }
    }

    if(piv_addr != start)
    {
        quick_sort_int(start, (void*)((u8*)piv_addr - offset), offset, start_offset);
    }
    if(piv_addr != end)
    {
        quick_sort_int((void*)((u8*)piv_addr + offset), end, offset, start_offset);
    }
}


void quick_sort(void *list, st list_size, void *mem_address, st struct_size)
{
    st offset = (st)mem_address - (st)list;

    st descriptors = list_size / struct_size;

    void *start = mem_address;
    void *end = (u8*)list + struct_size * (descriptors - 1) + offset;

    quick_sort_int(start, end, struct_size, offset);
}