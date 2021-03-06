#ifndef _GL_PSF_H_
#define _GL_PSF_H_

#include <rtos/rtypes.h>

//PSF_1
#define PSF1_MAGIC0     0x36
#define PSF1_MAGIC1     0x04

#define PSF1_MODE512    0x01
#define PSF1_MODEHASTAB 0x02
#define PSF1_MODEHASSEQ 0x04
#define PSF1_MAXMODE    0x05


typedef struct {
    uint8_t magic[2];
    uint8_t mode;
    uint8_t charsize;
}psf1_hdr;

//PSF_2

#define PSF2_MAGIC0     0x72
#define PSF2_MAGIC1     0xb5
#define PSF2_MAGIC2     0x4a
#define PSF2_MAGIC3     0x86

#define PSF2_MAXVERSION 0


typedef struct{
    uint8_t magic[4];
    uint32_t version;
    uint32_t headersize;    
    uint32_t flags;
    uint32_t length;        
    uint32_t charsize;      
    uint32_t height, width; 
}psf2_hdr;

#endif