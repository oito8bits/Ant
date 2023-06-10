#include <libefi.h>

UINTN strlen(const CHAR16 *str)
{
  const CHAR16 *p = str - 1;

  while(*++p);

  return p - str;
}
