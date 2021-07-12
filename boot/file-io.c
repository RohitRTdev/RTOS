#include <boot/file-io.h>
#include <refilib.h>

EFI_FILE_PROTOCOL* openfile(EFI_HANDLE device_handle, CHAR16 *file_path)
{
    EFI_STATUS status;
    EFI_GUID simple_fs_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *simple_fs = NULL;
    EFI_FILE_PROTOCOL *root = NULL;
    EFI_FILE_PROTOCOL *file_handle = NULL;

    //Get simple filesystem protocol for the device handle
    status = BS->HandleProtocol(device_handle, &simple_fs_guid, (void**)&simple_fs);
    EFI_FATAL_REPORT(L"Filesystem Handle locate error!", status);

    //Access root directory of device of file I/O
    status = simple_fs->OpenVolume(simple_fs, (EFI_FILE_PROTOCOL**)&root);
    EFI_FATAL_REPORT(L"Could not open root directory", status);

    //Open the requested file 
    status = root->Open(root, (EFI_FILE_PROTOCOL**)&file_handle, file_path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
    if(EFI_ERROR(status))
    {
        printEFI(L"Fatal error!\r\n");
        printEFI(L"Could not load requested file at path %s\r\n", file_path);
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

    //Get the loaded image protocol for ImageHandle
    status = BS->HandleProtocol(ImageHandle, &load_img_guid, (void**)&load_img_prot);    
    EFI_FATAL_REPORT(L"Load image protocol error", status);

    //Get the image's device handle (Please note that this is not the same as ImageHandle)
    EFI_HANDLE device_handle = load_img_prot->DeviceHandle;

    return device_handle;
}