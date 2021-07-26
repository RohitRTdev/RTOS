#ifndef __GLIB_ARRAY_H__
#define __GLIB_ARRAY_H__

#include <rtos/rtypes.h>

typedef struct{
	void* list_base_address;
	size_t empty_key_offset;
	size_t number_of_array_members;
	size_t total_array_capacity;
	size_t list_member_size;
	size_t empty_key_value;
}primitive_array;


/* Use this structure to manage a static array. */
primitive_array* init_static_array(primitive_array* array_descriptor, void* list_base_address, void* empty_key_address, size_t list_capacity, size_t list_struct_size, size_t empty_key_value);

primitive_array* add_array_member(primitive_array* array_descriptor, void* new_array_member);

primitive_array* remove_array_member(primitive_array* array_descriptor, void* array_member);

void* get_array_member_by_id(primitive_array* array_descriptor, void* member_key_address, void* member_key_value, size_t key_value_size);

void* get_array_member_by_callback(primitive_array* array_descriptor, boolean (*check_array_member)(void*), void* check_param);

primitive_array* fill_array(primitive_array* array_descriptor, void* fill_struct);

#endif