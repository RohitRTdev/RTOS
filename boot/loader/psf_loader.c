#include <boot/boot_structs.h>
#include <boot/modules.h>
#include <io/file.h>


//PSF_1
#define PSF1_MAGIC0     0x36
#define PSF1_MAGIC1     0x04

#define PSF1_MODE512    0x01
#define PSF1_MODEHASTAB 0x02
#define PSF1_MODEHASSEQ 0x04
#define PSF1_MAXMODE    0x05


typedef struct {
    UINT8 magic[2];
    UINT8 mode;
    UINT8 charsize;
}PSF1_header;

//PSF_2

#define PSF2_MAGIC0     0x72
#define PSF2_MAGIC1     0xb5
#define PSF2_MAGIC2     0x4a
#define PSF2_MAGIC3     0x86

#define PSF2_MAXVERSION 0


typedef struct{
    UINT8 magic[4];
    UINT32 version;
    UINT32 headersize;    
    UINT32 flags;
    UINT32 length;        
    UINT32 charsize;      
    UINT32 height, width; 
}PSF2_header;

static VOID read_psf_font_header(EFI_FILE_PROTOCOL* font_file_handle, UINTN hdr_size, void* hdr)
{
    read_simple_file(font_file_handle, 0, &hdr_size, hdr);
}

static EFI_STATUS psf1_load(EFI_FILE_PROTOCOL *font_file_handle, boot_time_modules* font_module)
{
    PSF1_header hdr;
    UINTN psf_hdr_size = sizeof(PSF1_header);
    EFI_STATUS status = EFI_SUCCESS;

    read_psf_font_header(font_file_handle, psf_hdr_size, &hdr);

    UINT64 psf_characters = (hdr.mode == PSF1_MODE512) ? 512 : 256;
    UINT64 psf_character_buffer_size = psf_characters * hdr.charsize;
    UINTN psf_buffer_size = psf_character_buffer_size + psf_hdr_size;
    UINTN psf_buffer_size_rounded = ALIGN(psf_buffer_size, PAGESIZE);

    void *font_buffer = NULL;

    status = allocate_loader_pages(psf_buffer_size_rounded, (EFI_PHYSICAL_ADDRESS*)&font_buffer);
    EFI_FATAL_REPORT(L"Memory allocation error for PSF", status);

    read_simple_file(font_file_handle, 0, &psf_buffer_size, font_buffer);

    add_boot_module(font_module->module_name, FONT, font_module->module_path, font_buffer, NULL, psf_buffer_size_rounded, NULL);

    return EFI_SUCCESS;

}
static EFI_STATUS psf2_load(EFI_FILE_PROTOCOL *font_file_handle, boot_time_modules* font_module)
{
    PSF2_header psf_hdr;
    UINTN psf_hdr_size = sizeof(PSF2_header);
    EFI_STATUS status = EFI_SUCCESS;


    read_psf_font_header(font_file_handle, psf_hdr_size, &psf_hdr);

    UINT64 psf_characters = psf_hdr.length;
    UINT64 psf_characters_buffer_size = psf_characters * psf_hdr.charsize;
    UINTN psf_buffer_size = psf_characters_buffer_size + psf_hdr_size;
    UINTN psf_buffer_size_rounded = ALIGN(psf_buffer_size, PAGESIZE);

    VOID* font_buffer = NULL;

    status = allocate_loader_pages(psf_buffer_size_rounded, &font_buffer);
    EFI_FATAL_REPORT(L"Memory allocation error for PSF", status);


    read_simple_file(font_file_handle, 0, &psf_buffer_size, font_buffer);

    add_boot_module(font_module->module_name, FONT, font_module->module_path, font_buffer, NULL, psf_buffer_size_rounded, NULL);

    return EFI_SUCCESS;

}
static EFI_STATUS psf_load(EFI_FILE_PROTOCOL* font_file_handle, boot_time_modules* font_module)
{
    UINT8 magic_constant_buffer[2];
    UINT8* font_base = NULL;
    UINTN size_magic = sizeof(magic_constant_buffer);
    EFI_STATUS font_load_status = EFI_SUCCESS;

    font_file_handle->Read(font_file_handle, &size_magic, (void*)magic_constant_buffer);

    if(magic_constant_buffer[0] == PSF1_MAGIC0 && magic_constant_buffer[1] == PSF1_MAGIC1)
        font_load_status = psf1_load(font_file_handle, font_module);
    else
    {
        UINT8 magic_constant_buffer[4];
        UINTN magic_constant_size_2 = sizeof(magic_constant_buffer);

        read_simple_file(font_file_handle, 0, &magic_constant_size_2, magic_constant_buffer);

        if(magic_constant_buffer[0] == PSF2_MAGIC0 && magic_constant_buffer[1] == PSF2_MAGIC1 && magic_constant_buffer[2] == PSF2_MAGIC2 && magic_constant_buffer[3] == PSF2_MAGIC3)
        {
            font_load_status = psf2_load(font_file_handle, font_module);
        }
        else
        {
            return FONT_NOT_SUPPORTED;
        }
        
    }
    return font_load_status;
}

VOID basic_font_load(EFI_HANDLE device_handle, boot_time_modules* font_module)
{
    EFI_FILE_PROTOCOL *font_buf = NULL;
    EFI_STATUS font_load_status = EFI_SUCCESS;
    CHAR16* font_path = font_module->module_path;

    font_buf = openfile(device_handle, font_path);      //Get file handle

    font_load_status = psf_load(font_buf, font_module);   //Load PSF into memory

    font_buf->Close(font_buf);

    return font_load_status;
}
