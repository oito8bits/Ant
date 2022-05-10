#ifndef _EFIBIND_INCLUDE_
#define _EFIBIND_INCLUDE_

#define EFIAPI __attribute__((ms_abi))

// Common UEFI Data Types.
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int int64_t;

typedef uint8_t   UINT8;
typedef uint16_t  UINT16;
typedef uint32_t  UINT32;
typedef uint64_t  UINT64;
typedef uint64_t  UINTN;

typedef int8_t  INT8;
typedef int16_t INT16;
typedef int32_t INT32;
typedef int64_t INT64;
typedef int64_t INTN;

typedef uint8_t BOOLEAN;


#define INTERFACE_DECL(x) struct x

#endif
