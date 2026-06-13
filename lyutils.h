// Name       : lyutils.h
// Description: Single Header Library for lyra consist renaming
//              some type like i32 and the other and somes

#ifndef ___LYUTILS_VERSION___
#define ___LYUTILS_VERSION___ "0.0.2"
#include <stddef.h>
#include <stdint.h>

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a > b) ? b : a)

#define ARRAY_LEN(ar) (sizeof(ar) / sizeof(ar[0]))

#if (__STDC_VERSION__ >= 202311l)
#define LYNULL nullptr
#else
#define LYNULL NULL
#endif

#endif
