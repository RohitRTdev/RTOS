#ifndef _REFI_PROT_H_
#define _REFI_PROT_H_

#include "refiprotapi.h"

struct _EFI_SYSTEM_TABLE;
struct _EFI_DEVICE_PATH_PROTOCOL;
struct _EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL{
    EFI_INPUT_RESET Reset;
    EFI_INPUT_READ_KEY ReadKeyStroke;
    EFI_EVENT WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL{
    EFI_TEXT_RESET Reset;
    EFI_TEXT_STRING OutputString;
    EFI_TEXT_TEST_STRING TestString;
    EFI_TEXT_QUERY_MODE QueryMode;
    EFI_TEXT_SET_MODE SetMode;
    EFI_TEXT_SET_ATTRIBUTE SetAttribute;
    EFI_TEXT_CLEAR_SCREEN ClearScreen;
    EFI_TEXT_SET_CURSOR_POSITION SetCursorPosition;
    EFI_TEXT_ENABLE_CURSOR EnableCursor;
    SIMPLE_TEXT_OUTPUT_MODE *Mode;
}EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;


typedef struct _EFI_LOADED_IMAGE_PROTOCOL{
    UINT32 Revision;
    EFI_HANDLE ParentHandle;
    struct _EFI_SYSTEM_TABLE *SystemTable;
    // Source location of the image
    EFI_HANDLE DeviceHandle;
    struct _EFI_DEVICE_PATH_PROTOCOL *FilePath;
    VOID *Reserved;
    // Image’s load options
    UINT32 LoadOptionsSize;
    VOID *LoadOptions;
    // Location where image was loaded
    VOID *ImageBase;
    UINT64 ImageSize;
    EFI_MEMORY_TYPE ImageCodeType;
    EFI_MEMORY_TYPE ImageDataType;
    EFI_IMAGE_UNLOAD Unload;
} EFI_LOADED_IMAGE_PROTOCOL;

typedef struct _EFI_DEVICE_PATH_PROTOCOL {
    UINT8 Type;
    UINT8 SubType;
    UINT8 Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef struct {
    UINT32 ControlMask;
    // current Attributes
    UINT32 Timeout;
    UINT64 BaudRate;
    UINT32 ReceiveFifoDepth;
    UINT32 DataBits;
    UINT32 Parity;
    UINT32 StopBits;
} SERIAL_IO_MODE;

typedef struct _EFI_SERIAL_IO_PROTOCOL{
    UINT32 Revision;
    EFI_SERIAL_RESET Reset;
    EFI_SERIAL_SET_ATTRIBUTES SetAttributes;
    EFI_SERIAL_SET_CONTROL_BITS SetControl;
    EFI_SERIAL_GET_CONTROL_BITS GetControl;
    EFI_SERIAL_WRITE Write;
    EFI_SERIAL_READ Read;
    SERIAL_IO_MODE *Mode;
} EFI_SERIAL_IO_PROTOCOL;

typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE QueryMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE SetMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT Blt;
    struct _EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

typedef struct {
    UINT32 RedMask;
    UINT32 GreenMask;
    UINT32 BlueMask;
    UINT32 ReservedMask;
} EFI_PIXEL_BITMASK;

typedef struct _EFI_GRAPHICS_OUTPUT_MODE_INFORMATION{
UINT32 Version;
UINT32 HorizontalResolution;
UINT32 VerticalResolution;
EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
EFI_PIXEL_BITMASK PixelInformation;
UINT32 PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE{
UINT32 MaxMode;
UINT32 Mode;
EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
UINTN SizeOfInfo;
EFI_PHYSICAL_ADDRESS FrameBufferBase;
UINTN FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct _EFI_GRAPHICS_OUTPUT_BLT_PIXEL{
    UINT8 Blue;
    UINT8 Green;
    UINT8 Red;
    UINT8 Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef struct {
    UINT32 SizeOfEdid;
    UINT8 *Edid;
} EFI_EDID_DISCOVERED_PROTOCOL;

typedef struct {
    UINT32 SizeOfEdid;
    UINT8 *Edid;
} EFI_EDID_ACTIVE_PROTOCOL;

typedef struct _EFI_EDID_OVERRIDE_PROTOCOL {
    EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID GetEdid;
} EFI_EDID_OVERRIDE_PROTOCOL;


typedef struct _HARDDRIVE_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT32                          PartitionNumber;
        UINT64                          PartitionStart;
        UINT64                          PartitionSize;
        UINT8                           Signature[16];
        UINT8                           MBRType;
        UINT8                           SignatureType;
} HARDDRIVE_DEVICE_PATH;

typedef struct _CDROM_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT32                          BootEntry;
        UINT64                          PartitionStart;
        UINT64                          PartitionSize;
} CDROM_DEVICE_PATH;

typedef struct _FILEPATH_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        CHAR16                          PathName[1];
} FILEPATH_DEVICE_PATH;

typedef struct _MEDIA_PROTOCOL_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        EFI_GUID                        Protocol;
} MEDIA_PROTOCOL_DEVICE_PATH;

typedef struct _EFI_DEVICE_PATH_UTILITIES_PROTOCOL {
    EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE GetDevicePathSize;
    EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH DuplicateDevicePath;
    EFI_DEVICE_PATH_UTILS_APPEND_PATH AppendDevicePath;
    EFI_DEVICE_PATH_UTILS_APPEND_NODE AppendDeviceNode;
    EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE AppendDevicePathInstance;
    EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE GetNextDevicePathInstance;
    EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE IsDevicePathMultiInstance;
    EFI_DEVICE_PATH_UTILS_CREATE_NODE CreateDeviceNode;
} EFI_DEVICE_PATH_UTILITIES_PROTOCOL;


typedef struct _EFI_LOAD_FILE_PROTOCOL {
    EFI_LOAD_FILE LoadFile;
} EFI_LOAD_FILE_PROTOCOL;


typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
    UINT64 Revision;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

typedef struct _EFI_FILE_PROTOCOL {
    UINT64 Revision;
    EFI_FILE_OPEN Open;
    EFI_FILE_CLOSE Close;
    EFI_FILE_DELETE Delete;
    EFI_FILE_READ Read;
    EFI_FILE_WRITE Write;
    EFI_FILE_GET_POSITION GetPosition;
    EFI_FILE_SET_POSITION SetPosition;
    EFI_FILE_GET_INFO GetInfo;
    EFI_FILE_SET_INFO SetInfo;
    EFI_FILE_FLUSH Flush;
    EFI_FILE_OPEN_EX OpenEx; // Added for revision 2
    EFI_FILE_READ_EX ReadEx; // Added for revision 2
    EFI_FILE_WRITE_EX WriteEx; // Added for revision 2
    EFI_FILE_FLUSH_EX FlushEx; // Added for revision 2
} EFI_FILE_PROTOCOL;

typedef struct _EFI_FILE_IO_TOKEN{
    EFI_EVENT Event;
    EFI_STATUS Status;
    UINTN BufferSize;
    VOID *Buffer;
} EFI_FILE_IO_TOKEN;

#endif