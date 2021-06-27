#include <rcommon.h>

//Note that the given functions assume that the member within the struct which it is to be sorted by is of 8 bytes

static void quick_sort_int(void *start, void* end, size_t offset, size_t start_offset)
{
    size_t *piv_addr = end;
    uint8_t *iter_ptr = start;
    size_t *last_saved = NULL;

    size_t *struct_address = NULL, *struct_address_pivot = NULL;

    for(iter_ptr = start; (void*)iter_ptr <= end; iter_ptr += offset)
    {
        if((size_t*)iter_ptr != piv_addr)
        {
            struct_address = (size_t*)(iter_ptr - start_offset);
            struct_address_pivot = (size_t*)((uint8_t*)piv_addr - start_offset);
            if(*(size_t*)iter_ptr > *piv_addr && (size_t*)iter_ptr < piv_addr)
            {
                swap(struct_address, struct_address_pivot, offset);
                piv_addr = (size_t*)iter_ptr;
                if(last_saved != NULL)
                {
                    iter_ptr = ((uint8_t*)last_saved - offset);
                    last_saved = NULL;
                }
            }
            else if(*(size_t*)iter_ptr < *piv_addr && (size_t*)iter_ptr > piv_addr)
            {
                swap(struct_address, struct_address_pivot, offset);
                piv_addr = (size_t*)iter_ptr;
                if(last_saved != NULL)
                {
                    iter_ptr = ((uint8_t*)last_saved - offset);
                    last_saved = NULL;
                }
            }
            else
            {
                if(last_saved == NULL)
                {
                    last_saved = (size_t*)iter_ptr;
                }
            }
        }
    }

    if(piv_addr != start)
    {
        quick_sort_int(start, (void*)((uint8_t*)piv_addr - offset), offset, start_offset);
    }
    if(piv_addr != end)
    {
        quick_sort_int((void*)((uint8_t*)piv_addr + offset), end, offset, start_offset);
    }
}


void quick_sort(void *list, size_t list_size, void *mem_address, size_t struct_size)
{
    size_t offset = (size_t)mem_address - (size_t)list;

    size_t descriptors = list_size / struct_size;

    void *start = mem_address;
    void *end = (uint8_t*)list + struct_size * (descriptors - 1) + offset;

    quick_sort_int(start, end, struct_size, offset);
}