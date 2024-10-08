#ifndef RASM_NUMBER_H
#define RASM_NUMBER_H

#include <limits.h>

#define RASM_UINT8_MAX ((rasm_uint8)-1)
#define RASM_INT8_MIN  ((rasm_int8)0x80)
#define RAMS_INT8_MAX  ((rasm_int8)0x7F)

#define RASM_UINT16_MAX ((rasm_uint16)-1)
#define RASM_INT16_MIN	((rasm_int16)0x8000)
#define RASM_INT16_MAX	((rasm_int16)0x7FFF)

#define RASM_UINT32_MAX ((rasm_uint32)-1)
#define RASM_INT32_MIN	((rasm_int32)0x80000000)
#define RASM_INT32_MAX	((rasm_int32)0x7FFFFFFF)

#define RASM_UINT64_MAX ((rasm_uint64)-1)
#define RASM_INT64_MIN	((rasm_int64)0x8000000000000000)
#define RASM_INT64_MAX	((rasm_int16)0x7FFFFFFFFFFFFFFF)

#define RASM_UINT8     unsigned char
#define RASM_UINT8_FMT "%u"

#define RASM_INT8     signed char
#define RASM_INT8_FMT "%d"

#define RASM_UINT16	unsigned short
#define RASM_UINT16_FMT "%uh"

#define RASM_INT16     short
#define RASM_INT16_FMT "%dh"

#define RASM_INT     int
#define RASM_INT_FMT "%d"

#define RASM_UINT     unsigned int
#define RASM_UINT_FMT "%u"

#if defined(ULLONG_MAX) && (ULONG_MAX < ULLONG_MAX)
#define RASM_SIZE     unsigned long long
#define RASM_SIZE_FMT "%llu"
#define RASM_SIZE_MAX ((rasm_size)(ULLONG_MAX))

#define RASM_SSIZE	long long
#define RASM_SSIZE_FMT	"%lld"
#define RASM_SSIZE_MAX	LLONG_MAX
#define RASM_SSIZE_MIN	LLONG_MIN
#define RASM_SSIZE_BITS sizeof(RASM_SSIZE) * CHAR_BIT;

#define RASM_UINT32	unsigned long
#define RASM_UINT32_FMT "%lu"

#define RASM_INT32     long
#define RASM_INT32_FMT "%ld"

#define RASM_UINT64	unsigned long long
#define RASM_UINT64_FMT "%llu"

#define RASM_INT64     long long
#define RASM_INT64_FMT "%ld"

#else
#define RASM_SIZE     unsigned long;
#define RASM_SIZE_FMT "%lu"
#define RASM_SIZE_MAX ((rasm_size)-1)

#define RASM_SSIZE     long
#define RASM_SSIZE_FMT "%ld"
#define RASM_SSIZE_MAX LONG_MAX
#define RASM_SSIZE_MIN LONG_MIN

#define RASM_UINT32	unsigned int
#define RASM_UINT32_FMT "%u"

#define RASM_INT32     int
#define RASM_INT32_FMT "%d"

#define RASM_UINT64	unsigned long;
#define RASM_UINT64_FMT "%llu"

#define RASM_INT64     long;
#define RASM_INT64_FMT "%ld"
#endif

typedef RASM_UINT8 rasm_uint8;
typedef RASM_INT8 rasm_int8;

typedef RASM_UINT16 rasm_uint16;
typedef RASM_INT16 rasm_int16;

typedef RASM_UINT32 rasm_uint32;
typedef RASM_INT32 rasm_int32;

typedef RASM_UINT64 rasm_uint64;
typedef RASM_INT64 rasm_int64;

typedef RASM_UINT rasm_uint;
typedef RASM_INT rasm_int;

typedef RASM_SIZE rasm_size;
typedef RASM_SSIZE rasm_ssize;

typedef rasm_uint16 rasm_float16;
typedef rasm_uint32 rasm_float32;
typedef rasm_uint64 rasm_float64;

typedef rasm_size rasm_float;

typedef enum { RASM_FALSE = 0, RASM_TRUE = 1 } rasm_bool;

typedef enum { RASM_POSITIVE = 0, RASM_NEGATIVE = 1 } rasm_sign;

typedef enum rasm_base {
	RASM_BASE_2  = 2,
	RASM_BASE_8  = 8,
	RASM_BASE_10 = 10,
	RASM_BASE_16 = 16

} rasm_base;

enum rasm_number { RASM_NUMBER_INTEGER, RASM_NUMBER_RATIONAL };

#endif
