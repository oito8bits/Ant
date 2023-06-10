#include <libefi.h>

VOID *malloc(UINTN size)
{
  VOID *buffer;
  EFI_STATUS status;

  status = BS->AllocatePool(EfiLoaderData, size, &buffer);

  if(status != EFI_SUCCESS)
    return NULL;

  return buffer;
}

VOID free(VOID *buffer)
{
  BS->FreePool(buffer);
}
