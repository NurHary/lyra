// Name       : lyutils.h
// Description: Single Header Library for lyra consist renaming 
//              some type like i32 and the other and somes


#ifndef LYUTILS_VERSION
#define LYUTILS_VERSION "0.0.1"

#include <stdint.h>

// // Standard Type For Integer Values // //

// 8 bit integers, used to store small values. mostly unused to 
// avoid integer overflow
// `-128 to 127`
typedef int8_t i8;

// 16 bit integers
// `-32768 to 32767`
typedef int16_t i16;


// 32 bit integers
// `-2147483648 to 2147483647`
typedef int32_t i32;

// 64 bit integers
// `-9223372036854775808 to 9223372036854775807`
typedef int64_t i64;

// // Standard Type For Unsigned Integer Values // //
// Note: DO NOT USE IT, BAD PRACTICES //

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// // Standard Type For Floating Point Values // //

typedef float f32 ;
typedef double f64 ;

#endif
