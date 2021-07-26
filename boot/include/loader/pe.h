#ifndef _PE_H_
#define _PE_H_
#include <refi/refi.h>
#include <refilib/refilib.h>

#define pe_signature 0x00004550  //PE/0/0 (In little endian)
#define signature_offset 0x3c //Location of file offset to PE signature
#define dos_signature 0x5a4d // MZ(In little endian)

typedef struct{
    UINT16 machine;
    UINT16 NumberOfSections;
    UINT32 TimeDateStamp;
    UINT32 PointerToSymbolTable;
    UINT32 NumberOfSymbols;
    UINT16 SizeOfOptionalHeader;
    UINT16 Characteristics;
}COFF_header;

#define IMAGE_FILE_MACHINE_AMD64 0x8664

#define magic_PE 0x10b
#define magic_PE32 0x20b

#define EXPORT_TABLE 0
#define IMPORT_TABLE 1
#define RESOURCE_TABLE 2
#define EXCEPTION_TABLE 3
#define CERTIFICATE_TABLE 4
#define BASE_RELOCATION_TABLE 5
#define DEBUG_TABLE 6
#define ARCHITECTURE_TABLE 7
#define GLOBAL_PTR_TABLE 8
#define TLS_TABLE 9
#define LOAD_CONFIG_TABLE 10
#define BOUND_IMPORT_TABLE 11
#define IAT 12
#define DELAY_IMPORT_DESCRIPTOR 13
#define CLR_RUNTIME_HEADER 14
#define RESERVED_TABLE 15
#define DATA_DIRECTORY_SIZE 16

typedef struct {
    UINT32 VirtualAddress;
    UINT32 Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

typedef struct{
    UINT16 magic;
    UINT8 MajorLinkerVersion;
    UINT8 MinorLinkerVersion;
    UINT32 SizeOfCode;
    UINT32 SizeOfInitializedData;
    UINT32 SizeOfUninitializedData;
    UINT32 AddressOfEntryPoint;
    UINT32 BaseOfCode;
    UINT64 ImageBase;
    UINT32 SectionAlignment;
    UINT32 FileAlignment;
    UINT16 MajorOperatingSystemVersion;
    UINT16 MinorOperatingSystemVersion;
    UINT16 MajorImageVersion;
    UINT16 MinorImageVersion;
    UINT16 MajorSubsystemVersion;
    UINT16 MinorSubsystemVersion;
    UINT32 Win32VersionValue;
    UINT32 SizeOfImage;
    UINT32 SizeOfHeader;
    UINT32 CheckSum;
    UINT16 Subsystem;
    UINT16 DllCharacteristics;
    UINT64 SizeOfStackReserve;
    UINT64 SizeOfStackCommit;
    UINT64 SizeOfHeapReserve;
    UINT64 SizeOfHeapCommit;
    UINT32 LoaderFlags;
    UINT32 NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[DATA_DIRECTORY_SIZE];
}Opt_COFF_header;


typedef struct{
    char name[8];
    UINT32 VirtualSize;
    UINT32 VirtualAddress;
    UINT32 SizeOfRawData;
    UINT32 PointerToRawData;
    UINT32 PointerToRelocations;
    UINT32 PointerToLineNumbers;
    UINT16 NumberOfRelocations;
    UINT16 NumberOfLinenumbers;
    UINT32 Characteristics;
}Section_header;

#define IMAGE_REL_BASED_ABSOLUTE 0
#define IMAGE_REL_BASED_HIGH 1
#define IMAGE_REL_BASED_LOW 2
#define IMAGE_REL_BASED_DIR64 10


#endif