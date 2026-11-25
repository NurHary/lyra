// NAME:  lstr.h
// DESC:  Lyra Strings With Small String Optimization
//        and written length with offset values.

#if (__STDC_VERSION__ <= 199900l)
#error "lyra library can only be used on std c >= 99"
#endif

#ifndef LYSTR_H_
#define LYSTR_H_
#define ___LYSTR_VERSION___ 0.01f

// CONFIGURATION
#ifdef LYCONFIG
#include LYCONFIG
#endif LYCONFIG

#ifndef LYC_SSOMINSZS
#define LYC_SSOMINSZS 8
#endif // LYC_SSOMINSZS


#include <stddef.h>
#include <string.h>

// Small String Optimized Static Strings 
typedef union {
  struct {char str [LYC_SSOMINSZS]; size_t count, offset; } sml;
  struct {char* str; size_t count, offset; }lng;
}lstr;

//! Create new strings with value of (*s)
lstr
lstr_new(const char* s);

//! Slices (*str) with value of (r) for right and (l) for left
lstr
lstrSlices(lstr* str, int r, int l);

//! Trim (*str) from space [isspace()] from left and right
void
lstrTrim(lstr* str);

//! Split (*str) with (sep) as splittimg point, return *trimmed* lstr
//! after the (sep) while the (*str) will max to the (sep) position
lstr
lstrSplit(lstr* str, char sep);

//! Split (*str) with (sep) as splittimg point, return *trimmed* lstr
//! start at 0 before (sep) while the (*str) will start after (sep) position
lstr
lstrSplitR(lstr* str, char sep, char p);

//! split string (*str) and (sep) as seperator then make list of lstr
//! based on how many (sep) encountered
lstr*
lstrSplitMulti(lstr* str, char sep, size_t rlen);

//! Free 
void
lstr_multifree(lstr* str, size_t amnt);

void
lstr_free(lstr* str);


#endif // LYSTR_H_


#ifdef LYSTR_IMPL_

#ifdef LYUSEARENA

#else // LYUSEARENA

#endif // LYUSEARENA

#endif LYSTR_IMPL_