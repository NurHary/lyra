// NAME:  strop.h
// DESC:  Strings operation headers, headers that hold strings operation that
// can
//        be used by any type of lyra strings

#include <stdint.h>

// //
// // Strings Checks Operation // //
// //

// Macros to compare strings from (s) to (d), return (o) as int
#define lystrcomp(s, d, o)

// Macros to check if the strings (s) match the (d), return (o) as boolean
#define lystreq(s, d, o)

// funtion to convert any type of lyra strings to any number based on the t, the
// values of it stored on the b parameter

// //
// // Strings Movement Operation // //
// //

#define lystrswap(s, d)

#define lystrpartswap(s, ssl, ssr, d, dsl, dsr)

#define lystrrev()

// //
// // Strings Convertion Operation // //
// //

typedef enum { I8, I16, I32, I64, F32, F64 } LYSTRTO_BUFFERTYPE;
#define lystrto(s, b, t)
