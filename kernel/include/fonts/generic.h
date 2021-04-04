#ifndef _GENERIC_H_
#define _GENERIC_H_

//Generic header for PSF

typedef struct{
    uint64_t glyphs;  //Total number of glyphs
    uint64_t height;  
    uint64_t width;
    uint8_t *base;  //base memory location of font   
    uint64_t charsize;
    uint32_t f_color;
    uint32_t b_color;
}font_header;


#endif 