#include <boot.h>
#include <fonts/generic.h>
#include <rcommon.h>
#include <logging/logger.h>


extern font_header generic_psf_info;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE framebuffer; 
extern EFI_GRAPHICS_OUTPUT_MODE_INFORMATION frameInfo;

static struct logger_props{
    uint32_t *cursor_location;
    uint32_t *frameBase;
    uint32_t pseudo_hor_res;
    uint64_t width_font;
    boolean edge_case; //This variable makes sure that "endline" condition is not re-triggered after processing a '/n' or '/r' condition
}logger;

 


void basic_print_init()
{
    //Load defaults
    generic_psf_info.b_color = 0x00000000UL;
    generic_psf_info.f_color = 0x00FFFFFFUL;

    logger.frameBase = (uint32_t*)framebuffer.FrameBufferBase;

    logger.width_font = ralign(generic_psf_info.width,8)/8;
    logger.cursor_location = logger.frameBase;
    logger.pseudo_hor_res = frameInfo.HorizontalResolution - frameInfo.HorizontalResolution % generic_psf_info.width;
    logger.edge_case = false;
}

static void basic_print_char(char ch, uint32_t *base_pixel)
{
    uint8_t *char_base = (uint8_t*)((uint64_t)generic_psf_info.base + ch*generic_psf_info.charsize);
    uint64_t i = 0, j = 0, k = 0;
    uint64_t width = generic_psf_info.width;
    uint64_t height = generic_psf_info.height;
    uint64_t width_font = logger.width_font;
    uint32_t f_color = generic_psf_info.f_color;
    uint32_t b_color = generic_psf_info.b_color;
    uint32_t PixelsPerScanLine = frameInfo.PixelsPerScanLine;

    while(i < height)
    {
        while(j < width_font)
        {
            while(k < 8)
            {
                if(j * 8 + k == width)
                    break;
                if(*(char_base + width_font*i + j) & (0x80 >> k))
                    *(base_pixel + j * 8 + k) = f_color;
                else
                {
                    *(base_pixel + j * 8 + k) = b_color;
                }
                k++;
                
            }
            j++;
            if(k != 8)
            {
                k = 0;
                break;
            }
            k = 0;   
        }
        i++;
        j = 0;
        base_pixel += PixelsPerScanLine;
    }
}

void basic_print_str(char *str)
{
    uint64_t conv_factor = generic_psf_info.width;
    uint64_t i = 0;
    uint64_t height = generic_psf_info.height;
    uint32_t *frameBase = logger.frameBase;
    uint32_t pseudo_hor_res = logger.pseudo_hor_res;
    uint32_t PixelsPerScanLine = frameInfo.PixelsPerScanLine;

    while(str[i] != '\0')
    {
        if((logger.cursor_location - frameBase) % pseudo_hor_res == 0 && logger.cursor_location != frameBase && !logger.edge_case)  //End of a line
        {
            logger.cursor_location += PixelsPerScanLine - pseudo_hor_res + PixelsPerScanLine * (height - 1);
        }
        if(str[i] == '\n')
        {
            logger.cursor_location += PixelsPerScanLine * height;
            i++;
            logger.edge_case = true;
            continue;
        }
        else if(str[i] == '\r')
        {
            logger.cursor_location = logger.cursor_location - ((logger.cursor_location - frameBase) % PixelsPerScanLine);
            i++;
            logger.edge_case = true;
            continue;
        }

        basic_print_char(str[i], logger.cursor_location);
        i++;
        logger.cursor_location += conv_factor;
        logger.edge_case = false;
    }    
    
}