/* Lightweight PE_loader(Portable executable) for RTOS */

/* Loads .text, .data and .bss sections
   without much checking involved(Feel free to load more sections and to include more checks if you're interested) */

#include <pe.h>
#include <primary_loader.h>

static void pe_load_section(EFI_FILE_PROTOCOL *file_buf, UINT64 size, Section_header section, UINT8 *load_address)
{

    file_buf->SetPosition(file_buf, section.PointerToRawData);

    file_buf->Read(file_buf, &size, (void*)load_address);

}

static void pe_relocate(EFI_FILE_PROTOCOL *file_buf, Section_header section, UINT64 delta, Opt_COFF_header hdr, UINT8* base_address)
{
    UINTN size = round_4k(section.SizeOfRawData)*PAGESIZE;
    UINT64 im_offset;
    UINT64 *reloc_address;
    UINT64 value;
    UINT32 p_rva;
    UINT32 reloc_size;
    UINT32 *block_hdr_read;
    UINT16 page_offset;
    UINT16 *cache = NULL;
    UINT16 *buf;
    UINT8 type;
    
    EFI_STATUS status;
           
    file_buf->SetPosition(file_buf, section.PointerToRawData);

    status = BS->AllocatePool(EfiLoaderData, size, (void**)&cache);
    EFI_FATAL_REPORT(L"Could not allocate memory for reloc section!\r\n", status);

    buf = cache;
    block_hdr_read = (UINT32*)cache;
    file_buf->Read(file_buf, &size, (void*)cache);

    p_rva = *block_hdr_read;
    reloc_size = *(block_hdr_read + 1);  
    im_offset = p_rva - (hdr.BaseOfCode - hdr.ImageBase);
    cache += 4;
    reloc_size -= 8;
    
    //Read and parse the reloc section to make appropriate relocations

    while(reloc_size)
    {
        page_offset = *cache;
        type = (page_offset >> 12) & 0x0f;
        page_offset = page_offset & 0x0fff;

        if(type == IMAGE_REL_BASED_DIR64)
        {   
            reloc_address = (UINT64*)(base_address + im_offset + page_offset);
            value = *reloc_address;
            *reloc_address = value + delta;
        }
        
        reloc_size -= 2;
        cache++;
        
    }
    status = BS->FreePool((void*)buf);
    EFI_FATAL_REPORT(L"Memory region busy!\r\n", status);
    
}
UINT64 round_4k(UINT64 value) 
{
    UINT64 pages = (value % PAGESIZE)?value/PAGESIZE + 1: value/PAGESIZE;
    return pages;
}
static BOOLEAN pe_verify(EFI_FILE_PROTOCOL *file_buf)
{
    UINT16 mz;
    UINT32 pe;
    UINT8 offset;
    UINTN buf_size = 2;
    file_buf->Read(file_buf, &buf_size, (void*)&mz);

    //Basic PE file verification

    if(mz != dos_signature)
        return FALSE;
    
    file_buf->SetPosition(file_buf, signature_offset);

    buf_size = 1;
    file_buf->Read(file_buf, &buf_size, (void*)&offset);
    file_buf->SetPosition(file_buf, offset);
    buf_size = 4;
    file_buf->Read(file_buf, &buf_size, (void*)&pe);
    if(pe != pe_signature)
        return FALSE;

    return TRUE;
}

static UINT8* pe_load(EFI_FILE_PROTOCOL *file_buf, Image_data *image)
{
    EFI_STATUS status;
    BOOLEAN load_verify = FALSE;
    COFF_header pe_hdr;
    UINTN buf_size = sizeof(pe_hdr);
    Opt_COFF_header pe_opt_hdr;
    UINT64 pages = 0;
    UINT8 *load_address;
    UINT8 *cur_address;
    Section_header section;
    UINT64 sect_counter = 0;
    BOOLEAN text_sect = FALSE;

    load_verify = pe_verify(file_buf);
    if(!load_verify)
       return NULL; 
    
    file_buf->Read(file_buf, &buf_size, (void*)&pe_hdr);
    if(pe_hdr.machine != IMAGE_FILE_MACHINE_AMD64)
    {
        printEFI(L"Machine Type is not x86_64\r\n");
        printEFI(L"Cannot continue execution\r\n");
        while(1){}
    }
    buf_size = pe_hdr.SizeOfOptionalHeader;

    //Read optional header
    file_buf->Read(file_buf, &buf_size, (void*)&pe_opt_hdr);
        
    UINT64 size_code = round_4k(pe_opt_hdr.SizeOfCode);
    UINT64 size_data = round_4k(pe_opt_hdr.SizeOfInitializedData);
    UINT64 size_bss = round_4k(pe_opt_hdr.SizeOfUninitializedData);   
    UINT64 pos; 
    pages = size_code + size_data + size_bss;

    //Allocate suitable amount of pages to load requested file
    status = BS->AllocatePool(EfiLoaderData, pages * PAGESIZE, (void**)&load_address);
    EFI_FATAL_REPORT(L"Memory is insufficient to load kernel", status);

    buf_size = sizeof(section);
    cur_address = load_address;    

    UINT64 delta = (UINT64)load_address - pe_opt_hdr.BaseOfCode; //To get relocation offset
    
    while(sect_counter < pe_hdr.NumberOfSections)
    {
        //Read the section header
        file_buf->Read(file_buf, &buf_size, (void*)&section);
        file_buf->GetPosition(file_buf, &pos);
        //Parse the section header
        if(!rstrcmp(section.name, ".text"))
        {
            text_sect = TRUE;
            pe_load_section(file_buf, pe_opt_hdr.SizeOfCode, section, cur_address);
            cur_address = cur_address + size_code*PAGESIZE;
        }
        else if(!rstrcmp(section.name, ".data"))
        {
            pe_load_section(file_buf, pe_opt_hdr.SizeOfInitializedData, section, cur_address);
            cur_address = cur_address + size_data*PAGESIZE;
        } 
        else if(!rstrcmp(section.name, ".bss"))
        {
            //.bss section has nothing to load. We only need to allocate space for it
            cur_address = cur_address + size_bss*PAGESIZE;
        }
        else if(!rstrcmp(section.name, ".reloc"))
        {
            //Apply DIR64 type relocation 
            //Relocation is necessary even with PIC as global pointers may have fixed addresses which we need to change
            pe_relocate(file_buf, section, delta, pe_opt_hdr, load_address);
        }  
        sect_counter++;
        file_buf->SetPosition(file_buf, pos);

    }

    UINT8 *entry_point = load_address + (pe_opt_hdr.AddressOfEntryPoint - pe_opt_hdr.BaseOfCode);
    image->entry_point = entry_point;
    image->base = load_address;
    image->pages = pages;

    if(!text_sect)
    {
        printEFI(L"No executable section found!\r\n");
        printEFI(L"Cannot continue execution\r\n");
        while(1){}
    }    
    return entry_point;
    
}
EFI_FILE_PROTOCOL* openfile(EFI_HANDLE deviceHandle, CHAR16 *filepath)
{
    EFI_STATUS status;
    EFI_GUID simple_fs_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *simple_fs = NULL;
    EFI_FILE_PROTOCOL *root = NULL;
    EFI_FILE_PROTOCOL *file_handle = NULL;

    //Get simple filesystem protocol for the device handle
    status = BS->HandleProtocol(deviceHandle, &simple_fs_guid, (void**)&simple_fs);
    EFI_FATAL_REPORT(L"Filesystem Handle locate error!", status);

    //Access root directory of device of file I/O
    status = simple_fs->OpenVolume(simple_fs, (EFI_FILE_PROTOCOL**)&root);
    EFI_FATAL_REPORT(L"Could not open root directory", status);

    //Open the requested file 
    status = root->Open(root, (EFI_FILE_PROTOCOL**)&file_handle, filepath, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
    if(EFI_ERROR(status))
    {
        printEFI(L"Fatal error!\r\n");
        printEFI(L"Could not load requested file at path %s\r\n", filepath);
        printEFI(L"Cannot continue execution!\r\n");
        while(1){}
    }

    return file_handle;

}

EFI_HANDLE file_init(EFI_HANDLE ImageHandle)
{
    EFI_STATUS status;
    EFI_GUID load_img_guid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_LOADED_IMAGE_PROTOCOL *load_img_prot = NULL;

    //Get teh loaded image protocol for ImageHandle
    status = BS->HandleProtocol(ImageHandle, &load_img_guid, (void**)&load_img_prot);    
    EFI_FATAL_REPORT(L"Load image protocol error", status);

    //Get the image's device handle (Please note that this is not the same as ImageHandle)
    EFI_HANDLE deviceHandle = load_img_prot->DeviceHandle;

    return deviceHandle;
}



UINT8* pe_loadfile(EFI_HANDLE ImageHandle, CHAR16* filepath, Image_data *image)
{
    UINT8 *entry = NULL;
    EFI_HANDLE main_handle;
    EFI_FILE_PROTOCOL *kernel_buf = NULL;

    main_handle = file_init(ImageHandle);  //Load the device handle

    kernel_buf = openfile(main_handle, filepath);  //Get file handle to kernel 
    
    entry = pe_load(kernel_buf, image);   //Load kernel and get image data

    kernel_buf->Close(kernel_buf); //Close kernel file handle

    return entry;
}