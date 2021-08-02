#include <rtos/handoff.h>
#include <refilib/refilib.h>
#include <boot/modules.h>

EFI_STATUS setup_gop()
{
    EFI_STATUS op_status = EFI_SUCCESS;

    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop_prot = NULL;

    op_status = BS->LocateProtocol(&gop_guid, NULL, (void**)&gop_prot);
    EFI_FATAL_REPORT(L"Could not locate GOP", op_status);


    /* Set the present graphics mode as the default mode */
    op_status = gop_prot->SetMode(gop_prot, gop_prot->Mode->Mode);
    EFI_FATAL_REPORT(L"Error in setting default graphics mode", op_status);

    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE* mode = gop_prot->Mode;


    gop display = {.framebuffer_base = mode->FrameBufferBase, .framebuffer_size = mode->FrameBufferSize, .h_res = mode->Info->HorizontalResolution,
                    .v_res = mode->Info->VerticalResolution, .pixel_format = mode->Info->PixelFormat, .pixels_per_scanline = mode->Info->PixelsPerScanLine};
  
    kernel_essentials->display = display;

    return op_status;
}