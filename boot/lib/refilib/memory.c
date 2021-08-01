#include <refi/refi.h>
#include <refilib/refilib.h>

EFI_STATUS allocate_loader_pages(UINTN size, EFI_PHYSICAL_ADDRESS* buffer_address)
{
    BS->AllocatePages(AllocateAnyPages, EfiLoaderData, size / PAGESIZE, buffer_address);
}