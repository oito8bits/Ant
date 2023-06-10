#include <libefi.h>

INTN fat_init_file_protocol(EFI_FILE_PROTOCOL **root)
{
  EFI_STATUS status;

  EFI_GUID fs_protocol_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *device;
  status = BS->LocateProtocol(&fs_protocol_guid,
                              NULL,
                              (VOID **) &device);

  if(status != EFI_SUCCESS)
    return 1;
  
  EFI_FILE_PROTOCOL *rootp;
  status = device->OpenVolume(device, &rootp);
  if(status != EFI_SUCCESS)
    return 1;

  *root = rootp;

  return 0;
}

// Open a file from fat partition.
INTN fat_open_file(EFI_FILE_PROTOCOL *root,
                         EFI_FILE_PROTOCOL **file_interface,
                         CHAR16 *pathname,
                         UINT64 open_mode, 
                         UINT64 attributes)
{
  EFI_STATUS status;
  status = root->Open(root, file_interface, pathname, open_mode, attributes);
  
  if(status != EFI_SUCCESS)
    return 1;

  return status;
}

// Close file.
INTN fat_close_file(EFI_FILE_PROTOCOL *file_interface)
{
  file_interface->Close(file_interface);
}

// Set the byte position.
UINTN fat_set_position(EFI_FILE_PROTOCOL *file_interface, UINT64 position)
{
  EFI_STATUS status;
  file_interface->SetPosition(file_interface, position);

  if(status != EFI_SUCCESS)
    return 1;

  return 0;
}

// Read a file.
INTN fat_read_file(EFI_FILE_PROTOCOL *file_interface,
                         UINTN *buffer_size,
                         VOID *buffer)
{
  EFI_STATUS status;
  status = file_interface->Read(file_interface, buffer_size, buffer);
  if(status != EFI_SUCCESS)
    return 1;

  return 0;
}
