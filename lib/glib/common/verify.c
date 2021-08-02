#include <rtos/rtypes.h>

boolean verify_function_pointers(const void** param_array, size_t number_of_params)
{

	while(number_of_params--)
	{
		if(*param_array == NULL)
			return false;
		param_array++;
	}
	return true;
}