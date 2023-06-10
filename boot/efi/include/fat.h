#ifndef _DEFINE_FAT_
#define _DEFINE_FAT_

#include <efi.h>

INTN fat_init_file_protocol(EFI_FILE_PROTOCOL **);
INTN fat_open_file(EFI_FILE_PROTOCOL *,
                   EFI_FILE_PROTOCOL **,
                   CHAR16 *,
                   UINT64,
                   UINT64);
INTN fat_close_file(EFI_FILE_PROTOCOL *);
INTN fat_read_file(EFI_FILE_PROTOCOL *,
                   UINTN *,
                   VOID *);
UINTN fat_set_position(EFI_FILE_PROTOCOL *,
                       UINT64);
#endif
