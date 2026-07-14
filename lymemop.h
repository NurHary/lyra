// NAME: lymemop.h
// DESC: Header for memory operations

#ifndef LYMEMOP_IMPL

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if (__STDC_VERSION__ >= 202311l)
#else
#include <stdbool.h>
#endif

// //
// // Memory Allocation // //
// //

void*
lymemalign(const size_t size, const size_t alignment);

// //
// // Memory Movement Operation // //
// //

// Function to copy mem (s) with (szs) size to mem (d) with (szd) size
void
lymemcpy(void* restrict s, const size_t szs, void* restrict d,
         const size_t szd);
// mem char copy, memcpy but stop if (szs || szd) or if char c occurance
void
lymemccpy(void* restrict s, const size_t szs, void* restrict d,
          const size_t szd, char c);
// Function to move memory of (s) with amount of (n). return void*
void*
lymemmove(void* restrict s, const size_t n);
// Function to duplicate mem of (s) with amount of (n). return void*
void*
memdup(void* restrict s, const size_t szs);
// mem duplicate zero, memdup with null values added at the end if the iteration
// hit szs
void*
memdupz(void* restrict s, const size_t szs);
// Function to swap values of mem adress (s) with (szs) size, to value
// of mem adress (d) with (szd) size
void
lymemswap(void* restrict s, const size_t szs, void* restrict d,
          const size_t szd);
// Function to reverse values from memory adress of (d) with the amount of (n)
void
lymemrev(void* d, const size_t n);

// //
// // Memory Values Operation // //
// //

// Function to set memory of the (d) of the size of (szd) and values of (c)
void
lymemset(void* restrict d, const size_t szd, const char c);
// Function to set memory of the (d) with amount of (n) and with values of 0
void
lymemzero(void* d, size_t n);
// Function to set memory of the (d) with amount of (n) and with values of 1
void
lymemone(void* d, size_t n);
// Function to replace mem (d) of (n) amount with (c). (o) as the output /
// values that get replaced
void
lymemreplace(void* d, const size_t n, char c, void* o);
// Function to replace values of (d) with (n) amount with strings pattern of
// (p). return int8_t of the last array values of the strings pattern (p)
int8_t
lymempattern(void* d, const size_t n, char* p, size_t szp);

// //
// // Memory Checks Operation // //
// //

// Function check if mem adress start from (s) with (n) amount is zero
bool
lymemiszero(void* restrict s, const size_t n);
// Function to get the position of the first occurance of (c) on mem (s) with
// (szs) size. return ptrdiff_t to show relative index of the first occurance
// (c)
ptrdiff_t
lymemchar(void* restrict s, const size_t szs, char c);
// Function to compare values of (s) again values of (d) with
// (n) amount. return values of integer to indicate how many diff between two
// mem
size_t
lymemcmp(void* restrict s, void* restrict d, const size_t n);
// Function to find sequence of memory (t) with (szt) size inside (s) with (szs)
// size. return ptrdiff_t as realtive position of the memory sequence occurance
ptrdiff_t
lymemmem(void* s, const size_t szs, void* t, const size_t szt);
// Function to check if (s) and (d) with (n) amount is equal
bool
lymemeq(void* restrict s, void* restrict d, const size_t n);
// Function to get how many occurance of (c) in (d) with (n) amount
size_t
lymemcount(void* d, size_t n, char c);

#ifdef LYMEMPRO_IMPL
void*
lymemalign(const size_t size, const size_t alignment) {}

void
lymemcpy(void* restrict s, const size_t szs, void* restrict d,
         const size_t szd) {}

void
lymemccpy(void* restrict s, const size_t szs, void* restrict d,
          const size_t szd, char c) {}

void*
lymemmove(void* restrict s, const size_t n) {}

void*
memdup(void* restrict s, const size_t szs) {}

void*
memdupz(void* restrict s, const size_t szs) {}

void
lymemswap(void* restrict s, const size_t szs, void* restrict d,
          const size_t szd) {}

// Function to reverse partially, taken two parameter source which is the
// location to reverse the memory, and n amount of byte to reverse
void
lymemrev(void* d, const size_t n) {}

void
lymemset(void* restrict d, const size_t szd, const char c) {}

void
lymemzero(void* d, size_t n) {}

void
lymemone(void* d, size_t n) {}

void
lymemfill(void* d, const size_t n, char c) {}

void*
lymemreplace(void* d, const size_t n, char c) {}

void
lymemclear(void* d, const size_t n) {}

void
lymempattern(void* d, const size_t n, char* p) {}

bool
lymemiszero(void* restrict s, const size_t n) {}

ptrdiff_t
lymemchar(void* restrict s, const size_t szs, char c) {}

size_t
lymemcmp(void* restrict s, void* restrict d) {}

size_t
lymemncmp(void* restrict s, const size_t szs, void* restrict d,
          const size_t szd) {}

void*
lymemmem(void* s, const size_t szs, void* d, const size_t szd) {}

bool
lymemeq(void* s, void* d) {}

size_t
lymemcount(void* d, size_t n, char c) {}
#endif

#ifdef __cplusplus
}
#endif

#endif
