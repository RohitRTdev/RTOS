#include <boot.h>
#include <fonts/generic.h>
#include <rcommon.h>
#include <logging/logger.h>


extern font_header generic_psf_info;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE framebuffer; 
extern EFI_GRAPHICS_OUTPUT_MODE_INFORMATION frameInfo;

static uint32_t *cursor_location;
static uint32_t *frameBase;

static uint64_t width_font;
static uint32_t pseudo_hor_res;

static boolean edge_case; //This variable makes sure that "endline" condition is not triggered after '/n' or '/r' condition


void basic_print_init()
{
    //Load defaults
    generic_psf_info.b_color = 0x00000000UL;
    generic_psf_info.f_color = 0x00FFFFFFUL;

    frameBase = (uint32_t*)framebuffer.FrameBufferBase;

    width_font = ralign(generic_psf_info.width,8)/8;
    cursor_location = frameBase;

    pseudo_hor_res = frameInfo.HorizontalResolution - frameInfo.HorizontalResolution % generic_psf_info.width;
    edge_case = false;
}

static void basic_print_char(char ch, uint32_t *base_pixel)
{
    uint8_t *char_base = (uint8_t*)((uint64_t)generic_psf_info.base + ch*generic_psf_info.charsize);
    uint64_t i = 0, j = 0, k = 0;
    while(i < generic_psf_info.height)
    {
        while(j < width_font)
        {
            while(k < 8)
            {
                if(j * 8 + k == generic_psf_info.width)
                    break;
                if(*(char_base + width_font*i + j) & (0x80 >> k))
                    *(base_pixel + j * 8 + k) = generic_psf_info.f_color;
                else
                {
                    *(base_pixel + j * 8 + k) = generic_psf_info.b_color;
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
        base_pixel += frameInfo.PixelsPerScanLine;
    }
}

void basic_print_str(char *str)
{
    uint64_t conv_factor = generic_psf_info.width;
    uint64_t i = 0;
    while(str[i] != '\0')
    {
        if((cursor_location - frameBase) % pseudo_hor_res == 0 && cursor_location != frameBase && !edge_case)  //End of a line
        {
            cursor_location += frameInfo.PixelsPerScanLine - pseudo_hor_res + frameInfo.PixelsPerScanLine * (generic_psf_info.height - 1);
        }
        if(str[i] == '\n')
        {
            cursor_location += frameInfo.PixelsPerScanLine * generic_psf_info.height;
            i++;
            edge_case = true;
            continue;
        }
        else if(str[i] == '\r')
        {
            cursor_location = cursor_location - ((cursor_location - frameBase) % frameInfo.PixelsPerScanLine);
            i++;
            edge_case = true;
            continue;
        }

        basic_print_char(str[i], cursor_location);
        i++;
        cursor_location += conv_factor;
        edge_case = false;
    }    
    
}