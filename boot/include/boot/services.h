#ifndef _BOOT_SERVICES_H_
#define _BOOT_SERVICES_H_

#include <refi/refi.h>

EFI_STATUS inline get_protocol_service(EFI_HANDLE image_handle, EFI_GUID* protocol_guid, void** interface);


#endif