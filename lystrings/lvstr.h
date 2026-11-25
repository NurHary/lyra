#ifndef LYVSTR_H_
#define LYVSTR_H_
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
}lvstr;

#endif LYVSTR_H_
