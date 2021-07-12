#include "arraybytemethods.h"

boolean _check_1_byte_member_equality(void* member_key_address, void* member_key_value)
{
	uint8_t src = *(uint8_t*)member_key_address;
	uint8_t dest = *(uint8_t*)member_key_value;

	if(src == dest)
		return true;
	else
		return false;
}
boolean _check_2_byte_member_equality(void* member_key_address, void* member_key_value)
{
	uint16_t src = *(uint16_t*)member_key_address;
	uint16_t dest = *(uint16_t*)member_key_value;

	if(src == dest)
		return true;
	else
		return false;
}

boolean _check_4_byte_member_equality(void* member_key_address, void* member_key_value)
{
	uint32_t src = *(uint32_t*)member_key_address;
	uint32_t dest = *(uint32_t*)member_key_value;

	if(src == dest)
		return true;
	else
		return false;
}
boolean _check_8_byte_member_equality(void* member_key_address, void* member_key_value)
{
	uint64_t src = *(uint64_t*)member_key_address;
	uint64_t dest = *(uint64_t*)member_key_value;

	if(src == dest)
		return true;
	else
		return false;
}
boolean _check_member_equality(void* member_key_address, void* member_key_value, size_t member_size)
{
	int8_t compare_result = rmemcmp(member_key_address, member_key_value, member_size);
	
	if(compare_result == 0)
		return true;
	else
		return false;
}
