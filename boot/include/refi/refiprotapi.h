#ifndef _REFI_PROT_API_H_
#define _REFI_PROT_API_H_

#include "refidefs.h"

struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
struct _EFI_SERIAL_IO_PROTOCOL;
struct _EFI_GRAPHICS_OUTPUT_PROTOCOL; 
struct _EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;
struct _EFI_GRAPHICS_OUTPUT_BLT_PIXEL;
struct _EFI_EDID_OVERRIDE_PROTOCOL;
struct _EFI_LOADED_IMAGE_PROTOCOL;
struct _EFI_DEVICE_PATH_PROTOCOL;
struct _EFI_LOAD_FILE_PROTOCOL;
struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;
struct  _EFI_FILE_PROTOCOL;
struct _EFI_FILE_IO_TOKEN;

#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000
#define EFI_FILE_READ_ONLY 0x0000000000000001
#define EFI_FILE_HIDDEN 0x0000000000000002
#define EFI_FILE_SYSTEM 0x0000000000000004
#define EFI_FILE_RESERVED 0x0000000000000008
#define EFI_FILE_DIRECTORY 0x0000000000000010
#define EFI_FILE_ARCHIVE 0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037

#define BOXDRAW_HORIZONTAL 0x2500
#define BOXDRAW_VERTICAL 0x2502
#define BOXDRAW_DOWN_RIGHT 0x250c
#define BOXDRAW_DOWN_LEFT 0x2510
#define BOXDRAW_UP_RIGHT 0x2514
#define BOXDRAW_UP_LEFT 0x2518
#define BOXDRAW_VERTICAL_RIGHT 0x251c
#define BOXDRAW_VERTICAL_LEFT  0x2524
#define BOXDRAW_DOWN_HORIZONTAL 0x252c
#define BOXDRAW_UP_HORIZONTAL 0x2534
#define BOXDRAW_VERTICAL_HORIZONTAL 0x253c
#define BOXDRAW_DOUBLE_HORIZONTAL 0x2550
#define BOXDRAW_DOUBLE_VERTICAL 0x2551
#define BOXDRAW_DOWN_RIGHT_DOUBLE 0x2552
#define BOXDRAW_DOWN_DOUBLE_RIGHT 0x2553
#define BOXDRAW_DOUBLE_DOWN_RIGHT 0x2554
#define BOXDRAW_DOWN_LEFT_DOUBLE 0x2555
#define BOXDRAW_DOWN_DOUBLE_LEFT 0x2556
#define BOXDRAW_DOUBLE_DOWN_LEFT 0x2557
#define BOXDRAW_UP_RIGHT_DOUBLE 0x2558
#define BOXDRAW_UP_DOUBLE_RIGHT 0x2559
#define BOXDRAW_DOUBLE_UP_RIGHT 0x255a
#define BOXDRAW_UP_LEFT_DOUBLE 0x255b
#define BOXDRAW_UP_DOUBLE_LEFT 0x255c
#define BOXDRAW_DOUBLE_UP_LEFT 0x255d
#define BOXDRAW_VERTICAL_RIGHT_DOUBLE 0x255e
#define BOXDRAW_VERTICAL_DOUBLE_RIGHT 0x255f
#define BOXDRAW_DOUBLE_VERTICAL_RIGHT 0x2560
#define BOXDRAW_VERTICAL_LEFT_DOUBLE 0x2561
#define BOXDRAW_VERTICAL_DOUBLE_LEFT 0x2562
#define BOXDRAW_DOUBLE_VERTICAL_LEFT 0x2563
#define BOXDRAW_DOWN_HORIZONTAL_DOUBLE 0x2564
#define BOXDRAW_DOWN_DOUBLE_HORIZONTAL 0x2565
#define BOXDRAW_DOUBLE_DOWN_HORIZONTAL 0x2566
#define BOXDRAW_UP_HORIZONTAL_DOUBLE 0x2567
#define BOXDRAW_UP_DOUBLE_HORIZONTAL 0x2568
#define BOXDRAW_DOUBLE_UP_HORIZONTAL 0x2569
#define BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE 0x256a
#define BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL 0x256b
#define BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL 0x256c
#define BLOCKELEMENT_FULL_BLOCK 0x2588
#define BLOCKELEMENT_LIGHT_SHADE 0x2591
#define GEOMETRICSHAPE_UP_TRIANGLE 0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE 0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE 0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE 0x25c4
#define ARROW_UP 0x2191
#define ARROW_DOWN 0x2193


#define EFI_BLACK 0x00
#define EFI_BLUE 0x01
#define EFI_GREEN 0x02
#define EFI_CYAN 0x03
#define EFI_RED 0x04
#define EFI_MAGENTA 0x05
#define EFI_BROWN 0x06
#define EFI_LIGHTGRAY 0x07
#define EFI_BRIGHT 0x08
#define EFI_DARKGRAY (EFI_BLACK | EFI_BRIGHT) 
#define EFI_LIGHTBLUE 0x09
#define EFI_LIGHTGREEN 0x0A
#define EFI_LIGHTCYAN 0x0B
#define EFI_LIGHTRED 0x0C
#define EFI_LIGHTMAGENTA 0x0D
#define EFI_YELLOW 0x0E
#define EFI_WHITE 0x0F
#define EFI_BACKGROUND_BLACK 0x00
#define EFI_BACKGROUND_BLUE 0x10
#define EFI_BACKGROUND_GREEN 0x20
#define EFI_BACKGROUND_CYAN 0x30
#define EFI_BACKGROUND_RED 0x40
#define EFI_BACKGROUND_MAGENTA 0x50
#define EFI_BACKGROUND_BROWN 0x60
#define EFI_BACKGROUND_LIGHTGRAY 0x70


#define EFI_SERIAL_CLEAR_TO_SEND 0x0010
#define EFI_SERIAL_DATA_SET_READY 0x0020
#define EFI_SERIAL_RING_INDICATE 0x0040
#define EFI_SERIAL_CARRIER_DETECT 0x0080
#define EFI_SERIAL_REQUEST_TO_SEND 0x0002
#define EFI_SERIAL_DATA_TERMINAL_READY 0x0001
#define EFI_SERIAL_INPUT_BUFFER_EMPTY 0x0100
#define EFI_SERIAL_OUTPUT_BUFFER_EMPTY 0x0200
#define EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE 0x1000
#define EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE 0x2000
#define EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE 0x4000

#define EFI_SERIAL_CLEAR_TO_SEND 0x0010
#define EFI_SERIAL_DATA_SET_READY 0x0020
#define EFI_SERIAL_RING_INDICATE 0x0040
#define EFI_SERIAL_CARRIER_DETECT 0x0080
#define EFI_SERIAL_REQUEST_TO_SEND 0x0002
#define EFI_SERIAL_DATA_TERMINAL_READY 0x0001
#define EFI_SERIAL_INPUT_BUFFER_EMPTY 0x0100
#define EFI_SERIAL_OUTPUT_BUFFER_EMPTY 0x0200
#define EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE 0x1000
#define EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE 0x2000
#define EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE 0x4000

#define EFI_EDID_OVERRIDE_DONT_OVERRIDE 0x01
#define EFI_EDID_OVERRIDE_ENABLE_HOT_PLUG 0x02


//Console Input
typedef EFI_STATUS (*EFI_INPUT_RESET) (IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, IN BOOLEAN ExtendedVerification);
typedef EFI_STATUS (*EFI_INPUT_READ_KEY) (IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, OUT EFI_INPUT_KEY *Key);

//Console Output
typedef EFI_STATUS (*EFI_TEXT_RESET) (IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN BOOLEAN ExtendedVerification);
typedef EFI_STATUS (*EFI_TEXT_STRING) (IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN CHAR16 *String);
typedef EFI_STATUS (*EFI_TEXT_TEST_STRING) (IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN CHAR16 *String);
typedef EFI_STATUS (*EFI_TEXT_QUERY_MODE) (IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN UINTN ModeNumber, OUT UINTN *Columns, OUT UINTN *Rows);
typedef EFI_STATUS (*EFI_TEXT_SET_MODE) (IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN UINTN ModeNumber);
typedef EFI_STATUS (*EFI_TEXT_SET_ATTRIBUTE) (IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN UINTN Attribute);
typedef EFI_STATUS (*EFI_TEXT_CLEAR_SCREEN) (IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
typedef EFI_STATUS (*EFI_TEXT_SET_CURSOR_POSITION) (IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN UINTN Column, IN UINTN Row);
typedef EFI_STATUS (*EFI_TEXT_ENABLE_CURSOR) (IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN BOOLEAN Visible);

//Loaded image

typedef EFI_STATUS (*EFI_IMAGE_UNLOAD) (IN EFI_HANDLE ImageHandle);

//Serial I/O

typedef EFI_STATUS (*EFI_SERIAL_RESET) (IN struct _EFI_SERIAL_IO_PROTOCOL *This);
typedef EFI_STATUS (*EFI_SERIAL_SET_ATTRIBUTES) (IN struct _EFI_SERIAL_IO_PROTOCOL *This, IN UINT64 BaudRate, IN UINT32 ReceiveFifoDepth, IN UINT32 Timeout, IN EFI_PARITY_TYPE Parity, IN UINT8 DataBits, IN EFI_STOP_BITS_TYPE StopBits);
typedef EFI_STATUS (*EFI_SERIAL_SET_CONTROL_BITS) (IN struct _EFI_SERIAL_IO_PROTOCOL *This, IN UINT32 Control);
typedef EFI_STATUS (*EFI_SERIAL_GET_CONTROL_BITS) (IN struct _EFI_SERIAL_IO_PROTOCOL *This, OUT UINT32 *Control);
typedef EFI_STATUS (*EFI_SERIAL_WRITE) (IN struct _EFI_SERIAL_IO_PROTOCOL *This, IN OUT UINTN *BufferSize, IN VOID *Buffer);
typedef EFI_STATUS (*EFI_SERIAL_READ) (IN struct _EFI_SERIAL_IO_PROTOCOL *This, IN OUT UINTN *BufferSize, OUT VOID *Buffer);

//Graphics Output Protocol

typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE) (IN struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *This, IN UINT32 ModeNumber, OUT UINTN *SizeOfInfo OUT, struct _EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);
typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE) (IN struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *This, IN UINT32 ModeNumber);
typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT) (IN struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *This, IN OUT struct _EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, OPTIONAL IN EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation, IN UINTN SourceX, IN UINTN SourceY, IN UINTN DestinationX, IN UINTN DestinationY, IN UINTN Width, IN UINTN Height, IN UINTN Delta OPTIONAL);

//EDID
typedef EFI_STATUS (*EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID) (IN struct _EFI_EDID_OVERRIDE_PROTOCOL *This, IN EFI_HANDLE *ChildHandle, OUT UINT32 *Attributes, IN OUT UINTN *EdidSize, IN OUT UINT8 **Edid);


//Device path utilities
typedef UINTN (*EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE) (IN CONST struct _EFI_DEVICE_PATH_PROTOCOL *DevicePath);
typedef struct _EFI_DEVICE_PATH_PROTOCOL* (*EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH) (IN CONST struct _EFI_DEVICE_PATH_PROTOCOL *DevicePath);
typedef struct _EFI_DEVICE_PATH_PROTOCOL* (*EFI_DEVICE_PATH_UTILS_APPEND_PATH) (IN CONST struct _EFI_DEVICE_PATH_PROTOCOL *Src1, IN CONST struct _EFI_DEVICE_PATH_PROTOCOL *Src2);
typedef struct _EFI_DEVICE_PATH_PROTOCOL* (*EFI_DEVICE_PATH_UTILS_APPEND_NODE) (IN CONST struct _EFI_DEVICE_PATH_PROTOCOL *DevicePath, IN CONST struct _EFI_DEVICE_PATH_PROTOCOL *DeviceNode);
typedef struct _EFI_DEVICE_PATH_PROTOCOL* (*EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE) (IN CONST struct _EFI_DEVICE_PATH_PROTOCOL *DevicePath, IN CONST struct _EFI_DEVICE_PATH_PROTOCOL *DevicePathInstance);
typedef struct _EFI_DEVICE_PATH_PROTOCOL* (*EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE) (IN OUT struct _EFI_DEVICE_PATH_PROTOCOL **DevicePathInstance, OUT UINTN *DevicePathInstanceSize OPTIONAL);
typedef struct _EFI_DEVICE_PATH_PROTOCOL* (*EFI_DEVICE_PATH_UTILS_CREATE_NODE) (IN UINT8 NodeType, IN UINT8 NodeSubType, IN UINT16 NodeLength);
typedef BOOLEAN (*EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE) (IN CONST struct _EFI_DEVICE_PATH_PROTOCOL *DevicePath);

//File utilities

typedef EFI_STATUS (*EFI_LOAD_FILE) (IN struct _EFI_LOAD_FILE_PROTOCOL *This, IN struct _EFI_DEVICE_PATH_PROTOCOL *FilePath, IN BOOLEAN BootPolicy, IN OUT UINTN *BufferSize, IN VOID *Buffer OPTIONAL);
typedef EFI_STATUS (*EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME) (IN struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This, OUT struct _EFI_FILE_PROTOCOL **Root);
typedef EFI_STATUS (*EFI_FILE_OPEN) (IN struct _EFI_FILE_PROTOCOL *This, OUT struct _EFI_FILE_PROTOCOL **NewHandle, IN CHAR16 *FileName, IN UINT64 OpenMode, IN UINT64 Attributes);
typedef EFI_STATUS (*EFI_FILE_CLOSE) (IN struct _EFI_FILE_PROTOCOL *This);
typedef EFI_STATUS (*EFI_FILE_DELETE) (IN struct _EFI_FILE_PROTOCOL *This);
typedef EFI_STATUS (*EFI_FILE_READ) (IN struct _EFI_FILE_PROTOCOL *This, IN OUT UINTN *BufferSize, OUT VOID *Buffer);
typedef EFI_STATUS (*EFI_FILE_WRITE) (IN struct _EFI_FILE_PROTOCOL *This, IN OUT UINTN *BufferSize, IN VOID *Buffer);
typedef EFI_STATUS (*EFI_FILE_OPEN_EX) (IN struct _EFI_FILE_PROTOCOL *This, OUT struct _EFI_FILE_PROTOCOL **NewHandle, IN CHAR16 *FileName, IN UINT64 OpenMode, IN UINT64 Attributes, IN OUT struct _EFI_FILE_IO_TOKEN *Token);
typedef EFI_STATUS (*EFI_FILE_READ_EX) (IN struct _EFI_FILE_PROTOCOL *This, IN OUT struct _EFI_FILE_IO_TOKEN *Token);
typedef EFI_STATUS (*EFI_FILE_WRITE_EX) (IN struct _EFI_FILE_PROTOCOL, IN OUT struct _EFI_FILE_IO_TOKEN);
typedef EFI_STATUS (*EFI_FILE_FLUSH_EX) (IN struct _EFI_FILE_PROTOCOL *This, IN OUT struct _EFI_FILE_IO_TOKEN *Token);
typedef EFI_STATUS (*EFI_FILE_SET_POSITION) (IN struct _EFI_FILE_PROTOCOL *This, IN UINT64 Position);
typedef EFI_STATUS (*EFI_FILE_GET_POSITION) (IN struct _EFI_FILE_PROTOCOL *This, OUT UINT64 *Position);
typedef EFI_STATUS (*EFI_FILE_GET_INFO) (IN struct _EFI_FILE_PROTOCOL *This, IN EFI_GUID *InformationType, IN OUT UINTN *BufferSize, OUT VOID *Buffer);
typedef EFI_STATUS (*EFI_FILE_SET_INFO) (IN struct _EFI_FILE_PROTOCOL *This, IN EFI_GUID *InformationType, IN UINTN BufferSize, IN VOID *Buffer);
typedef EFI_STATUS (*EFI_FILE_FLUSH) (IN struct _EFI_FILE_PROTOCOL *This);




#endif