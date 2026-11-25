#ifndef LYSTRV_H_
#define LYSTRV_H_
#define ___LYVSTRINGS_VERSION___ 0.02f

// CONFIGURATION
#ifdef LYCONFIG
#include LYCONFIG
#endif LYCONFIG

#include <stddef.h>

// String Views
typedef struct {
  char* str;
  size_t count, offset;
}lstrv;

#endif // LYSTRV_H_
