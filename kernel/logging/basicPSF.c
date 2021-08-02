#include <font/psf.h>
#include <error/syserror.h>
#include <kernel/generic.h>
#include <logging/logger.h>
#include <rtos/handoff.h>


font_header generic_psf_info;
EFI_GRAPHICS_OUTPUT_MODE_INFORMATION frameInfo;
EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE framebuffer;

static SYS_ERROR PSF_1(uint8_t *base);
static SYS_ERROR PSF_2(uint8_t *base);


SYS_ERROR basic_PSF_renderer(uint8_t *base, EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE framebuf, EFI_GRAPHICS_OUTPUT_MODE_INFORMATION frameinfo)
{
    uint8_t magic[4] = {*base, *(base + 1), *(base + 2), *(base + 3)};
    boolean psf_1 = false;
    boolean psf_2 = false;
    SYS_ERROR err_status = NO_ERROR;


    if(magic[0] == PSF1_MAGIC0 && magic[1] == PSF1_MAGIC1) 
        psf_1 = true;       
    else if(magic[0] == PSF2_MAGIC0 && magic[1] == PSF2_MAGIC1 && magic[2] == PSF2_MAGIC2 && magic[3] == PSF2_MAGIC3)
        psf_2 = true;
    else
    {
        return INVALID_PSF_FORMAT;
    }
    
    if(psf_1)
        err_status = PSF_1(base);
    else if(psf_2)
    {
        err_status = PSF_2(base);
    }

    frameInfo = frameinfo;
    framebuffer = framebuf;

    if(!RT_ERROR(err_status))
        basic_print_init();
    
    return err_status;

}

static SYS_ERROR PSF_1(uint8_t *base)
{
    psf1_hdr hdr = { {*(base), *(base + 1) }, *(base + 2), *(base + 3) };
    uint64_t length = (hdr.mode == PSF1_MODE512)?512:256;


    generic_psf_info.base = (uint8_t*)((uint64_t)base + sizeof(psf1_hdr));
    generic_psf_info.height = hdr.charsize;
    generic_psf_info.glyphs = length;
    generic_psf_info.width = 8;
    generic_psf_info.charsize = hdr.charsize;

    //Error code is always success for now, but error checking code can be included in future

    return NO_ERROR;
    
}
static SYS_ERROR PSF_2(uint8_t *base)
{   
    psf2_hdr *psf2_base_ptr = (psf2_hdr*)base; 

    generic_psf_info.glyphs = psf2_base_ptr->length;
    generic_psf_info.height = psf2_base_ptr->height;
    generic_psf_info.width = psf2_base_ptr->width;
    generic_psf_info.base = (uint8_t*)(psf2_base_ptr->headersize + (uint64_t)base);
    generic_psf_info.charsize = psf2_base_ptr->charsize;


    return NO_ERROR;

}