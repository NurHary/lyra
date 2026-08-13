// NAME: lymemop.h
// DESC: Header for memory operations

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef __LYMEMOP_VERSION__

#include "lylog/lylog.h" // THIS SHIT SHOULD BE ILLEGAL

#include <stddef.h>
#include <stdint.h>

// lyutils.h
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a > b) ? b : a)
// EXPAND FROM lyutils.h

#ifdef __cplusplus
extern "C" {
#endif

#if (__STDC_VERSION__ >= 202311l)
#define LYMAYBEE_UNUSED [[maybe_unused]]
#else
#define LYMAYBEE_UNUSED
#include <stdbool.h>
#endif

// //
// // Memory Allocation // //
// //

// LYMAYBEE_UNUSED
// void*
// lymemalign(const size_t size, const size_t alignment);

// //
// // Memory Movement Operation // //
// //

typedef enum { RLEFT, RRIGHT } LYMEM_ROTATION_DIRECTION;

// Function to copy mem (s) with (szs) size to mem (d) with (szd) size
size_t
lymemcpy(void* restrict s, const size_t szs, void* restrict d,
         const size_t szd);
// mem char copy, memcpy but stop if (szs || szd) or if char c occurance
const size_t
lymemccpy(void* restrict s, const size_t szs, void* restrict d,
          const size_t szd, char c);
// Function to move memory of (s) with amount of (n). return void*
size_t
lymemmove(void* s, const size_t szs, void* d, const size_t szd);
// Function to duplicate mem of (s) with amount of (n). return void*
void*
lymemdup(void* restrict s, const size_t szs);
// mem duplicate zero, memdup with null values added at the end if the iteration
// hit szs
void*
lymemdupz(void* restrict s, const size_t szs);
// Function to duplicate the container with malloc, it will duplicate and set to
// 0
void*
lymemdupc(void* restrict s, const size_t szs);
// Function to swap values of mem adress (s) with (szs) size, to value
// of mem adress (d) with (szd) size
void
lymemswap(void* restrict s, const size_t szs, void* restrict d,
          const size_t szd);
// Function to reverse values from memory adress of (d) with the amount of (n)
void
lymemrev(void* d, const size_t n);

// Function to rotate memories
void
lymemrot(void* s, size_t szs, LYMEM_ROTATION_DIRECTION rt, size_t val);

// //
// // Memory Values Operation // //
// //

// Function to set memory of the (d) of the size of (szd) and values of (c)
static inline void
lymemset(void* restrict d, const char c, const size_t n);
// Function to set memory of the (d) with amount of (n) and with values of 0
static inline void
lymemzero(void* d, size_t n);
// Function to set memory of the (d) with amount of (n) and with values of 1
static inline void
lymemone(void* d, size_t n);
// Function to replace mem (d) of (n) amount with (c). (o) as the output /
// values that get replaced
void
lymemreplace(void* d, const size_t n, char c, void* o);
// Function to replace values of (d) with (n) amount with strings pattern of
// (p). return int8_t of the last array values of the strings pattern (p)
int32_t
lymempattern(void* d, const size_t n, char* p, size_t szp);

// //
// // Memory Checks Operation // //
// //

// Function to check if every memory in (s) is all 0; return 0 if there's non 0
// values and return 1 if all is 0
bool
lymemiszero(void* restrict s, const size_t n);
// Function to get the position of the first occurance of (c) on mem (s) with
// (szs) size. return ptrdiff_t to show relative index of the first occurance
// (c) and -1 if there's none
ptrdiff_t
lymemchar(void* restrict s, const size_t szs, char c);
// Function to compare values of (s) again values of (d) with
// (n) amount. return values of integer to indicate how many diff between two
// mem
int32_t
lymemcmp(void* restrict s, void* restrict d, const size_t n);
// Function to compare values of (s) again values of (d) with both sizes
// included
size_t
lymemszcmp(void* restrict s, const size_t szs, void* restrict d,
           const size_t szd);
// Function to find sequence of memory (t) with (szt) size inside (s) with (szs)
// size. return ptrdiff_t as realtive position of the memory sequence occurance
void*
lymemmem(void* d, const size_t szd, void* p, const size_t szp);
// Function to check if (s) and (d) with (n) amount is equal
bool
lymemeq(void* restrict s, void* restrict d, const size_t n);
// Function to get how many occurance of (c) in (d) with (n) amount
size_t
lymemcount(void* d, size_t n, char c);

#define LYMEMOP_IMPL
#ifdef LYMEMOP_IMPL
// LYMAYBEE_UNUSED
// void*
// lymemalign(const size_t size, const size_t alignment) {}

size_t
lymemcpy(void* restrict s, const size_t szs, void* restrict d,
         const size_t szd) {
  if (s == d) {
    lym_printlog(ERROR, "lymemcpy: Pointer Overlap. Don't pass two pointer of "
                        "the same location");
    exit(1);
  } // TOFIX
  for (size_t i = 0; i < szs && i < szd; ++i) {
    ((char*)d)[i] = ((char*)s)[i];
  }
  return MAX(szs, szd) - MIN(szs, szd);
}

const size_t
lymemccpy(void* restrict s, const size_t szs, void* restrict d,
          const size_t szd, char c) {
  size_t j = 0;
  for (size_t i = 0; i < szs && i < szd; ++i) {
    if (((char*)s)[i] == c)
      break;
    ((char*)d)[i] = ((char*)s)[i];
    ++j;
  }
  return MAX(szs, szd) - j;
}

size_t
lymemmove(void* s, const size_t szs, void* d, const size_t szd) {
  for (size_t i = 0; i < szs && i < szd; ++i) {
    ((char*)d)[i] = ((char*)s)[i];
    ((char*)s)[i] = 0;
  }
  return MAX(szs, szd) - MIN(szs, szd);
}

void*
lymemdup(void* restrict s, const size_t szs) {
  char* r = malloc((szs + 1) * sizeof(char));
  lymemcpy(s, szs, r, szs);
  return (void*)r;
}

void*
lymemdupz(void* restrict s, const size_t szs) {
  char* r = malloc((szs + 1) * sizeof(char));
  lymemcpy(s, szs, r, szs);
  r[szs] = 0;
  return (void*)r;
}

void*
lymemdupc(void* restrict s, const size_t szs) {
  char* r = malloc((szs + 1) * sizeof(char));
  lymemset(r, 0, szs);
  return (void*)r;
}

void
lymemswap(void* restrict s, const size_t szs, void* restrict d,
          const size_t szd) {}

// Function to reverse partially, taken two parameter source which is the
// location to reverse the memory, and n amount of byte to reverse
void
lymemrev(void* d, const size_t n) {
  unsigned char t;
  unsigned char* p = d;
  for (size_t i = 0; i < n / 2; ++i) {
    t = p[i];
    p[i] = p[n - 1 - i];
    p[n - 1 - i] = t;
  }
}

void
lymemrot(void* s, size_t szs, LYMEM_ROTATION_DIRECTION rt, size_t val) {
  if (szs == 0)
    return;
  val %= szs;
  if (val == 0)
    return;

  if (rt == RLEFT) {
    lymemrev(s, val);
    lymemrev(s + val, szs - val);
    lymemrev(s, szs);
  } else {
    lymemrev(s, szs - val);
    lymemrev(s + szs - val, val);
    lymemrev(s, szs);
  }
}

static inline void
lymemset(void* restrict d, const char c, const size_t n) {
  for (size_t i = 0; i < n; ++i) {
    *(char*)d = c;
    d = (char*)d + 1;
  }
}

static inline void
lymemzero(void* d, size_t n) {
  lymemset(d, 0, n);
}

static inline void
lymemone(void* d, size_t n) {
  lymemset(d, 1, n);
}

void
lymemreplace(void* d, const size_t n, char c, void* o) {}

void
lymemclear(void* d, const size_t n) {
  lymemset(d, 0, n);
}

int32_t
lymempattern(void* d, const size_t n, char* p, size_t szp) {
  size_t j = 0, i = 0;
  for (; i < n; ++i, ++j) {
    if (j >= szp) {
      j = 0;
    }
    ((char*)d)[i] = p[j];
  }
  return j;
}

bool
lymemiszero(void* restrict s, const size_t n) {
  for (size_t i = 0; i < n; ++i) {
    if (((char*)s)[i] != 0)
      return 0;
  }
  return 1;
}

ptrdiff_t
lymemchar(void* restrict s, const size_t szs, char c) {
  for (size_t i = 0; i < szs; ++i) {
    if (((char*)s)[i] == c) {
      return i;
    }
  }
  return -1;
}

int32_t
lymemcmp(void* restrict s, void* restrict d, const size_t n) {
  int32_t ra = 0;
  int32_t rb = 0;
  for (size_t i = 0; i < n; ++i) {
    ra += ((char*)s)[i];
    rb += ((char*)d)[i];
  }
  return ra - rb;
}

size_t
lymemszcmp(void* restrict s, const size_t szs, void* restrict d,
           const size_t szd) {
  int32_t ra = 0;
  int32_t rb = 0;
  for (size_t i = 0; i < MIN(szs, szd); ++i) {
    ra += ((char*)s)[i];
    rb += ((char*)d)[i];
  }
  return ra - rb;
}

void*
lymemmem(void* d, const size_t szd, void* p, const size_t szp) {
  if (!(szd >= szp)) {
    lym_printlog(ERROR,
                 "UKURAN PATTERN JAUH LEBIH BESAR DARIPADA UKURAN DESTINASI");
    return NULL;
  }
  for (size_t i = 0; i < szd; ++i) {
    size_t j = 0;
    if (((char*)d)[i] == ((char*)p)[0])
      for (; j < szp && i + j < szd; ++j) {
        if (!(((char*)d)[i + j] == ((char*)p)[j])) {
          break;
        }
      }
    if (j == szp) {
      return (void*)((char*)d) + i;
    }
  }
  return NULL;
}

bool
lymemeq(void* restrict s, void* restrict d, const size_t n) {
  for (size_t i = 0; i < n; ++i) {
    if (((char*)s)[i] != ((char*)d)[i])
      return 0;
  }
  return 1;
}

size_t
lymemcount(void* d, size_t n, char c) {
  size_t r = 0;
  for (size_t i = 0; i < n; ++i) {
    if (((char*)d)[i] == c)
      r++;
  }
  return r;
}
#endif

#ifdef __cplusplus
}
#endif

#endif
