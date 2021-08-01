#include <glib/array.h>
#include <glib/rmemory.h>
#include <glib/rcommon.h>
#include "arraybytemethods.h"

#define ARRAY_EMPTY_KEY(array_member) ((size_t*)((uint8_t*)array_member + array_descriptor->empty_key_offset))
#define ARRAY_EMPTY_KEY_POSITION(array_member) (*ARRAY_EMPTY_KEY(array_member))
#define ARRAY_EMPTY_CONDITION(array_member) (ARRAY_EMPTY_KEY_POSITION(array_member) == array_descriptor->empty_key_value)

#define ARRAY_MEMBER_KEY(array_member, member_key_offset) ((void*)((uint8_t*)array_member + member_key_offset))

primitive_array* init_static_array(primitive_array* array_descriptor, void* list_base_address, void* empty_key_address, size_t list_capacity, size_t list_struct_size, size_t empty_key_value)
{
	if(!verify_function_pointers((void* []){array_descriptor, list_base_address, empty_key_address}, 3) || list_capacity == 0 )
		return NULL;

	array_descriptor->list_base_address = list_base_address;
	array_descriptor->empty_key_offset = (size_t)list_base_address - (size_t)empty_key_address;
	array_descriptor->empty_key_value = empty_key_value;
	array_descriptor->list_member_size = list_struct_size;
	array_descriptor->number_of_array_members = 0;
	array_descriptor->total_array_capacity = list_capacity;
	array_descriptor->last_accessed_element = NULL;

	/* Initialise the array with empty key values */
	uint8_t* array_entry = array_descriptor->list_base_address;
	for(size_t i = 0 ; i < array_descriptor->total_array_capacity; i++)
	{
		ARRAY_EMPTY_KEY_POSITION(array_entry) = array_descriptor->empty_key_value;

		array_entry += array_descriptor->list_member_size;
	}


	/* Returns a non NULL address if passed successful allocation */
	return array_descriptor;
}

primitive_array* add_array_member(primitive_array* array_descriptor, void* new_array_member)
{
	if(!verify_function_pointers((void* []){array_descriptor, array_descriptor->list_base_address}, 2) || array_descriptor->number_of_array_members == array_descriptor->total_array_capacity || new_array_member == NULL)
		return NULL;
	
	size_t total_array_capacity = array_descriptor->total_array_capacity;
	uint8_t* array_ptr = array_descriptor->list_base_address;
	size_t member_size = array_descriptor->list_member_size;
	size_t empty_key_offset = array_descriptor->empty_key_offset;
	size_t empty_key_value = array_descriptor->empty_key_value;

	/* Search for an empty spot */
	while(!ARRAY_EMPTY_CONDITION(array_ptr))
	{
		array_ptr += member_size;
	}

	rmemcpy(array_ptr, new_array_member, member_size);

	array_descriptor->number_of_array_members++;

	return array_descriptor;
}

primitive_array* remove_array_member(primitive_array* array_descriptor, void* array_member)
{
	if(!verify_function_pointers((void* []){array_descriptor, array_descriptor->list_base_address}, 2) || array_descriptor->number_of_array_members == 0 || array_member == NULL)
		return NULL;

	/* Note that we're implicitly assuming here that our empty_key_value is of 8 bytes */
	ARRAY_EMPTY_KEY_POSITION(array_member) = array_descriptor->empty_key_value;
	
	array_descriptor->number_of_array_members--;
	return array_descriptor;

}

void* get_array_member_by_id(primitive_array* array_descriptor, void* member_key_address, void* member_key_value, size_t key_value_size)
{
	if(!verify_function_pointers((void* []){array_descriptor, array_descriptor->list_base_address}, 2) || member_key_address == NULL || member_key_value == NULL || key_value_size == 0)
		return NULL;

	uint8_t* array_ptr = array_descriptor->list_base_address;
	uint64_t index = 0;
	size_t empty_key_offset = array_descriptor->empty_key_offset;
	size_t empty_key_value  = array_descriptor->empty_key_value;
	size_t member_size = array_descriptor->list_member_size;
	boolean op_status = false;
	size_t member_key_offset = (size_t)array_descriptor->list_base_address - (size_t)member_key_address;

	for(index = 0; index < array_descriptor->total_array_capacity; index++)
	{
		if(ARRAY_EMPTY_CONDITION(array_ptr))
		{
			array_ptr += member_size;
			continue;
		}
			
		switch(key_value_size)
		{
			case 1:{
				op_status = _check_1_byte_member_equality(ARRAY_MEMBER_KEY(array_ptr, member_key_offset), member_key_value);
				break;
			}
			case 2:{
				op_status = _check_2_byte_member_equality(ARRAY_MEMBER_KEY(array_ptr, member_key_offset), member_key_value);
				break;
			}
			case 4:{
				op_status = _check_4_byte_member_equality(ARRAY_MEMBER_KEY(array_ptr, member_key_offset), member_key_value);
				break;
			}
			case 8:{
				op_status = _check_8_byte_member_equality(ARRAY_MEMBER_KEY(array_ptr, member_key_offset), member_key_value);
				break;
			}
			default:{
				op_status = _check_member_equality(ARRAY_MEMBER_KEY(array_ptr, member_key_offset), member_key_value, key_value_size);
			}
		}
		if(op_status)
		{
			return (void*)array_ptr;
			break;
		}
			
	}
	
	if(!op_status)
		return NULL;

}

void* get_array_member_by_callback(primitive_array* array_descriptor, boolean (*check_array_member)(void*), void* check_param)
{
	if(verify_function_pointers((void* []){array_descriptor, array_descriptor->list_base_address}, 2)|| check_array_member == NULL)
		return NULL;

	uint8_t* array_ptr = array_descriptor->list_base_address;
	uint64_t index = 0;
	size_t empty_key_offset = array_descriptor->empty_key_offset;
	size_t empty_key_value  = array_descriptor->empty_key_value;
	size_t member_size = array_descriptor->list_member_size;
	boolean op_status = false;

	for(index = 0; index < array_descriptor->total_array_capacity; index++)
	{
		if(ARRAY_EMPTY_CONDITION(array_ptr))
		{
			array_ptr += member_size;
			continue;
		}
		op_status = check_array_member(check_param);
		
		if(op_status)
		{
			return array_ptr;
			break;
		}
	}
	if(!op_status)
		return NULL;
}


primitive_array* fill_array(primitive_array* array_descriptor, void* fill_struct)
{
	if(!verify_function_pointers((void* []){array_descriptor, array_descriptor->list_base_address}, 2))
		return NULL;
	
	if(fill_struct == NULL)
	{
		rzeromem(array_descriptor->list_base_address, array_descriptor->list_member_size * array_descriptor->total_array_capacity);
	}
	else
	{
		uint8_t* array_ptr = array_descriptor->list_base_address;
		for(size_t index = 0; index < array_descriptor->total_array_capacity; index++)
		{
			rmemcpy(fill_struct, array_ptr, array_descriptor->list_member_size);
			array_ptr += array_descriptor->list_member_size;
		}	
	}
	return array_descriptor;
}

/* static array iterators */

void* iter_array_init(primitive_array* array_descriptor)
{
	if(array_descriptor == NULL)
		return NULL;
	
	array_descriptor->last_accessed_element = array_descriptor->list_base_address;
	return array_descriptor->list_base_address;
}

void* iter_array_next(primitive_array* array_descriptor)
{
	if(array_descriptor == NULL)
		return NULL;

	for(uint8_t* array_entry = (size_t)array_descriptor->last_accessed_element + array_descriptor->list_member_size; array_entry <= (size_t)array_descriptor->list_base_address + array_descriptor->number_of_array_members * ( array_descriptor->list_member_size - 1); array_entry += array_descriptor->list_member_size)
	{
		if(*(size_t*)((uint8_t*)array_entry+array_descriptor->empty_key_offset) != array_descriptor->empty_key_value)
		{
			array_descriptor->last_accessed_element = array_entry;
			return array_entry;
		}
	}
	return NULL;
}
