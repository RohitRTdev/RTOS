#include <refi/refi.h>
#include <refilib/refilib.h>

EFI_STATUS allocate_loader_pages(UINTN size, EFI_PHYSICAL_ADDRESS* buffer_address)
{
    return BS->AllocatePages(AllocateAnyPages, EfiLoaderData, size / PAGESIZE, buffer_address);
}

EFI_STATUS allocate_loader_pool(UINTN size, VOID** buffer)
{
    return BS->AllocatePool(AllocateAnyPages, size, buffer);
}