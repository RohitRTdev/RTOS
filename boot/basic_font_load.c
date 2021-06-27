#include <boot/boot_structs.h>
#include <boot/basic_font.h>
#include <boot/primary_loader.h>

static VOID psf1_load(EFI_FILE_PROTOCOL *font_buf, basic_font_info *font_info)
{
    PSF1_header hdr;
    UINTN size_hdr = sizeof(PSF1_header);
    UINT8 *buffer = NULL;
    EFI_STATUS status = EFI_SUCCESS;

    font_buf->SetPosition(font_buf, 0);
    font_buf->Read(font_buf, &size_hdr, (void*)&hdr);

    UINT64 length = (hdr.mode == PSF1_MODE512)?512:256;
    UINT64 size = length * hdr.charsize;
    UINTN allocation_size = size + size_hdr;
    UINTN allocated_size = round_4k(allocation_size);

    status = BS->AllocatePages(AllocateAnyPages, EfiLoaderData, allocated_size, (EFI_PHYSICAL_ADDRESS*)&buffer);
    EFI_FATAL_REPORT(L"Memory allocation error for PSF", status);

    font_buf->SetPosition(font_buf, 0);
    font_buf->Read(font_buf, &allocation_size, (void*)buffer);

    font_info->basic_font_base = buffer;
    font_info->basic_font_size = allocated_size * PAGESIZE;
}
static VOID psf2_load(EFI_FILE_PROTOCOL *font_buf, basic_font_info *font_info)
{
    PSF2_header hdr;
    UINTN size_hdr = sizeof(PSF2_header);
    UINT8 *buffer = NULL;
    EFI_STATUS status = EFI_SUCCESS;

    font_buf->SetPosition(font_buf, 0);
    font_buf->Read(font_buf, &size_hdr, (void*)&hdr);

    UINT64 length = hdr.length;
    UINT64 size = length * hdr.charsize;
    UINTN allocation_size = size + size_hdr;
    UINTN allocated_size = round_4k(allocation_size);

    status = BS->AllocatePages(AllocateAnyPages, EfiLoaderData, allocated_size, (EFI_PHYSICAL_ADDRESS*)&buffer);
    EFI_FATAL_REPORT(L"Memory allocation error for PSF", status);

    font_buf->SetPosition(font_buf, 0);
    font_buf->Read(font_buf, &allocation_size, (void*)buffer);

    font_info->basic_font_base = buffer;
    font_info->basic_font_size = allocated_size * PAGESIZE;

}
static VOID psf_load(EFI_FILE_PROTOCOL *font_buf, basic_font_info *font_info)
{
    UINT8 magic[2];
    UINT8* font_base = NULL;
    UINTN size_magic = sizeof(magic);
    font_buf->Read(font_buf, &size_magic, (void*)magic);

    if(magic[0] == PSF1_MAGIC0 && magic[1] == PSF1_MAGIC1)
        psf1_load(font_buf, font_info);
    else
    {
        UINT8 magic_2[4];
        UINTN size_magic_2 = sizeof(magic_2);
        font_buf->SetPosition(font_buf, 0);
        font_buf->Read(font_buf, &size_magic_2, (void*)magic_2);

        if(magic_2[0] == PSF2_MAGIC0 && magic_2[1] == PSF2_MAGIC1 && magic_2[2] == PSF2_MAGIC2 && magic_2[3] == PSF2_MAGIC3)
        {
            psf2_load(font_buf, font_info);
        }
        else
        {
            font_info->basic_font_base = NULL;
            font_info->basic_font_size = 0;
        }
        
    }
}

VOID basic_font_load(EFI_HANDLE ImageHandle, CHAR16 *path, basic_font_info *font_info)
{
    EFI_HANDLE main_handle;
    EFI_FILE_PROTOCOL *font_buf = NULL;

    main_handle = file_init(ImageHandle);        //Get device handle

    font_buf = openfile(main_handle, path);      //Get file handle

    psf_load(font_buf, font_info);   //Load PSF into memory

    font_buf->Close(font_buf);
}
