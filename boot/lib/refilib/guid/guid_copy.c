#include <refilib/refilib.h>
#include <glib/rcommon.h>
#include <glib/rmemory.h>

void copy_guid(EFI_GUID* src_guid, EFI_GUID* dest_guid)
{
	void* copy_guid_params[2] = {src_guid, dest_guid};
	
	if(verify_function_pointers(copy_guid_params, 2))
	{
		dest_guid->Data1 = src_guid->Data1;
		dest_guid->Data2 = src_guid->Data2;
		dest_guid->Data3 = src_guid->Data3;

		rmemcpy(dest_guid->Data4, src_guid->Data4, 8);
	}

}