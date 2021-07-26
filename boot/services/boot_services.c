#include <boot/services.h>
#include <refilib/refilib.h>

EFI_STATUS get_protocol_service(EFI_HANDLE image_handle, EFI_GUID* protocol_guid, void** interface)
{
	EFI_STATUS op_status = EFI_SUCCESS;

	op_status = BS->HandleProtocol(image_handle, protocol_guid, interface);

	return op_status;
}