#include <rtos/rtypes.h>

boolean verify_function_pointers(void** param_array, size_t number_of_params)
{
	size_t** param_ptr = param_array;

	while(number_of_params--)
	{
		if(*param_ptr == NULL)
			return false;
		param_ptr++;
	}
	return true;
}