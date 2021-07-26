#ifndef __ARRAY_ARRAYBYTES_H__
#define __ARRAY_ARRAYBYTES_H__

#include <rtos/rtypes.h>
#include <glib/rmemory.h>

boolean _check_1_byte_member_equality(void* member_key_address, void* member_key_value);
boolean _check_2_byte_member_equality(void* member_key_address, void* member_key_value);
boolean _check_4_byte_member_equality(void* member_key_address, void* member_key_value);
boolean _check_8_byte_member_equality(void* member_key_address, void* member_key_value);
boolean _check_member_equality(void* member_key_address, void* member_key_value, size_t member_size);


#endif