#include <glib/rcommon.h>


void swap(st *address_1, st* address_2, st swap_size)
{
    st eight_byte_groups = swap_size / 8;
    st remaining_bytes = swap_size % 8 ;
    st *address_1_ptr = NULL, *address_2_ptr = NULL;

    for(i32 group = 0; group < eight_byte_groups; group++)
    {
        address_1_ptr = address_1 + group;
        address_2_ptr = address_2 + group;

        swap_op8(address_1_ptr, address_2_ptr);
    }

    address_1 += eight_byte_groups;
    address_2 += eight_byte_groups;

    for(i32 bytes = 0; bytes < remaining_bytes; bytes++)
    {
        address_1_ptr = (st*)((u8*)address_1 + bytes);
        address_2_ptr = (st*)((u8*)address_2 + bytes);

        swap_op(address_1_ptr, address_2_ptr);
    }
}