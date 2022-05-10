#include <efi.h>
#include <libefi.h>

VOID puts(CHAR16 *string)
{
  ST->ConOut->OutputString(ST->ConOut, string);
  ST->ConOut->OutputString(ST->ConOut, L"\n\r");
}

VOID putchar(CHAR16 character)
{
  CHAR16 string[2] = {character, L'\0'};

  ST->ConOut->OutputString(ST->ConOut, string);
}
  
INTN printf(CHAR16 *format, ...)
{
  while(*format)
    putchar(*format++);

  return 0;
}
