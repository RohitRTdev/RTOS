#ifndef _BOOT_H_
#define _BOOT_H_
#include <rtypes.h>

typedef enum {
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBltOnly,
    PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct {
    uint32_t RedMask;
    uint32_t GreenMask;
    uint32_t BlueMask;
    uint32_t ReservedMask;
} EFI_PIXEL_BITMASK;

typedef struct {
    uint32_t Type;
    uint64_t PhysicalStart;
    uint64_t VirtualStart; 
    uint64_t NumberOfPages;
    uint64_t Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef struct{
    uint64_t MapSize;
    uint64_t DescSize;
    uint64_t MapKey;
    uint32_t DescVer;
    EFI_MEMORY_DESCRIPTOR *Map;
}Map_descriptor;

typedef struct{
    uint32_t Version;
    uint32_t HorizontalResolution;
    uint32_t VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
    EFI_PIXEL_BITMASK PixelInformation;
    uint32_t PixelsPerScanLine;
}EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct{
    uint32_t MaxMode;
    uint32_t Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    uint32_t SizeOfInfo;
    uint64_t FrameBufferBase;
    uint64_t FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct{
    uint8_t *entry_point;
    uint8_t *base;
    uint64_t pages;
}Image_data;


typedef struct{
    Map_descriptor* Map;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *framebuffer;
    Image_data *image;
    void *acpi;
    uint8_t *basic_font_base;
}boot_info;


#endif