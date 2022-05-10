#ifndef _LIBEFI_INCLUDE_
#define _LIBEFI_INCLUDE_

#include <efi.h>

EFI_SYSTEM_TABLE *ST;
EFI_HANDLE IH;
EFI_BOOT_SERVICES *BS;
EFI_RUNTIME_SERVICES *RS;

VOID init_lib(EFI_HANDLE, EFI_SYSTEM_TABLE *);

// Console functions.
VOID puts(CHAR16 *);
VOID putchar(CHAR16);
INTN printf(CHAR16 *, ...);

#endif
