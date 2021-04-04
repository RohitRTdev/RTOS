#ifndef __BASIC_FONT_H__
#define __BASIC_FONT_H__


#include <refi.h>
#include <refilib.h>


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

UINT8* basic_font_load(EFI_HANDLE ImageHandle, CHAR16 *path);

#endif