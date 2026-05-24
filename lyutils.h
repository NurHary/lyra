#ifndef LYUTILS_VERSION
#define LYUTILS_VERSION "0.0.2"
#include <stddef.h>

// Name       : lyutils.h
// Description: Single Header Library for lyra consist renaming
//              some type like i32 and the other and somes

#include <stdint.h>

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a > b) ? b : a)

#define ARRAY_LEN(ar) (sizeof(ar) / sizeof(ar[0]))

// // Standard Type For Integer Values // //

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// // Standard Type For Unsigned Integer Values // //
// Note: DO NOT USE IT, BAD PRACTICES //

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// // Standard Type For Floating Point Values // //

typedef float f32;
typedef double f64;

typedef size_t size;

#endif
