#ifndef _REFI_TAB_H_
#define _REFI_TAB_H_

#include "refiapi.h"


/*  Use this macro to get the next memory map descriptor
    Ex: To get the PhysicalStart field of 5th descriptor>>

    getMapDescriptor(Map, DescSize, 5)->PhysicalStart; (This will return the correct value)
    
    Don't get descriptor directly or it will cause compatibility problems
    Ex: (Map + 5)->PhysicalStart (Don't use)

    In the above example, Map is of type EFI_MEMORY_DESCRIPTOR* and DescSize is 
    the size of a descriptor that is returned by GetMemoryMap function
*/
#define getMapDescriptor(ptr, size, pos) ((EFI_MEMORY_DESCRIPTOR*)((UINT8*)ptr + size*pos))  

typedef struct _EFI_TABLE_HEADER{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
}EFI_TABLE_HEADER;

struct _EFI_BOOT_SERVICES{
    EFI_TABLE_HEADER Hdr;
    EFI_RAISE_TPL   RaiseTPL;
    EFI_RESTORE_TPL RestoreTPL;
    EFI_ALLOCATE_PAGES AllocatePages;
    EFI_FREE_PAGES FreePages;
    EFI_GET_MEMORY_MAP GetMemoryMap; 
    EFI_ALLOCATE_POOL AllocatePool;
    EFI_FREE_POOL FreePool;
    EFI_CREATE_EVENT CreateEvent;
    EFI_SET_TIMER SetTimer;
    EFI_WAIT_FOR_EVENT WaitForEvent;
    EFI_SIGNAL_EVENT SignalEvent;
    EFI_CLOSE_EVENT CloseEvent;
    EFI_CHECK_EVENT CheckEvent;
    EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface; 
    EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface; 
    EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface; 
    EFI_HANDLE_PROTOCOL HandleProtocol; 
    VOID *Reserved ; 
    EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;
    EFI_LOCATE_HANDLE LocateHandle; 
    EFI_LOCATE_DEVICE_PATH LocateDevicePath; 
    EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;
    EFI_IMAGE_LOAD LoadImage;
    // EFI 1.0+
    EFI_IMAGE_START StartImage;
    // EFI 1.0+
    EFI_EXIT Exit;
    // EFI 1.0+
    EFI_IMAGE_UNLOAD UnloadImage;
    // EFI 1.0+
    EFI_EXIT_BOOT_SERVICES ExitBootServices; // EFI 1.0+
    //
    // Miscellaneous Services
    //
    EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount; // EFI 1.0+
    EFI_STALL Stall;
    EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;
    // EFI 1.0+
    //
    // DriverSupport Services
    //
    EFI_CONNECT_CONTROLLER ConnectController; // EFI 1.1
    EFI_DISCONNECT_CONTROLLER DisconnectController;// EFI 1.1+

    EFI_OPEN_PROTOCOL OpenProtocol;
    // EFI 1.1+
    EFI_CLOSE_PROTOCOL CloseProtocol;
    // EFI 1.1+
    EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation; // EFI 1.1+
    //
    // Library Services
    //
    EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle; // EFI 1.1+
    EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer; // EFI 1.1+
    EFI_LOCATE_PROTOCOL LocateProtocol;
    // EFI 1.1+
    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
    // EFI 1.1+
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;
     // EFI 1.1+
    //
    // 32-bit CRC Services
    //
    EFI_CALCULATE_CRC32 CalculateCrc32;
    // EFI 1.1+
    //
    // Miscellaneous Services
    //
    EFI_COPY_MEM CopyMem;
    // EFI 1.1+
    EFI_SET_MEM SetMem;
    // EFI 1.1+
    EFI_CREATE_EVENT_EX CreateEventEx;
};
typedef struct _EFI_BOOT_SERVICES EFI_BOOT_SERVICES;

struct _EFI_RUNTIME_SERVICES{
EFI_TABLE_HEADER Hdr;
//
// Time Services
//
EFI_GET_TIME GetTime;
EFI_SET_TIME SetTime;
EFI_GET_WAKEUP_TIME GetWakeupTime;
EFI_SET_WAKEUP_TIME SetWakeupTime;
//
// Virtual Memory Services
//
EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
EFI_CONVERT_POINTER ConvertPointer;
//
// Variable Services
//
EFI_GET_VARIABLE GetVariable;
EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
EFI_SET_VARIABLE SetVariable;
//
// Miscellaneous Services
//
EFI_GET_NEXT_HIGH_MONO_COUNT GetNextHighMonotonicCount;
EFI_RESET_SYSTEM ResetSystem;
//
// UEFI 2.0 Capsule Services
//
EFI_UPDATE_CAPSULE UpdateCapsule;
EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;
//
// Miscellaneous UEFI 2.0 Service
//
EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
};
typedef struct _EFI_RUNTIME_SERVICES EFI_RUNTIME_SERVICES;


struct _EFI_CONFIGURATION_TABLE{
    EFI_GUID VendorGuid;
    VOID* VendorTable;
};

typedef struct _EFI_CONFIGURATION_TABLE EFI_CONFIGURATION_TABLE;

struct _EFI_PROPERTIES_TABLE{
    UINT32 Version;
    UINT32 Length;
    UINT64 MemoryProtectionAttribute;
};

typedef struct _EFI_PROPERTIES_TABLE EFI_PROPERTIES_TABLE;

typedef struct _EFI_MEMORY_ATTRIBUTES_TABLE{
UINT32 Version ;
UINT32 NumberOfEntries ;
UINT32 DescriptorSize ;
UINT32 Reserved;
// EFI_MEMORY_DESCRIPTOR Entry [1];
}EFI_MEMORY_ATTRIBUTES_TABLE;


typedef struct _EFI_SYSTEM_TABLE{
    EFI_TABLE_HEADER Hdr;
    CHAR16 *FirmwareVendor;
    UINT32 FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    EFI_RUNTIME_SERVICES *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    UINTN NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE *ConfigurationTable;
}EFI_SYSTEM_TABLE;

//Entry point
typedef EFI_STATUS (*EFI_IMAGE_ENTRY_POINT) (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);


#endif