#include <rcommon.h>


void swap(size_t *address_1, size_t* address_2, size_t swap_size)
{
    size_t eight_byte_groups = swap_size / 8;
    size_t remaining_bytes = swap_size % 8 ;
    size_t *address_1_ptr = NULL, *address_2_ptr = NULL;

    for(int group = 0; group < eight_byte_groups; group++)
    {
        address_1_ptr = address_1 + group;
        address_2_ptr = address_2 + group;

        swap_op8(address_1_ptr, address_2_ptr);
    }

    address_1 += eight_byte_groups;
    address_2 += eight_byte_groups;

    for(int bytes = 0; bytes < remaining_bytes; bytes++)
    {
        address_1_ptr = (size_t*)((uint8_t*)address_1 + bytes);
        address_2_ptr = (size_t*)((uint8_t*)address_2 + bytes);

        swap_op(address_1_ptr, address_2_ptr);
    }
}