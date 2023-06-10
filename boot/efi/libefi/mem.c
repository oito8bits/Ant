#include <libefi.h>

VOID *memcpy(VOID *dest, const VOID *src, UINT64 n)
{
  UINT8 *p = dest;
  const UINT8 *q = src;

  while(n--)
    *p++ = *q++;;

  return dest;
}
