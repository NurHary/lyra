// FILE:  arena.h

#ifndef ___LYARENA_VERSION___
#define ___LYARENA_VERSION___ 0.01f

#include <stddef.h>
typedef struct {
  char* base;
  char* last_buptr;
  void* data;
  size_t count;
  size_t capacity;
} arena;

arena*
lyInitArena(size_t amm);

void*
lyAllocArena(void* data, size_t szs);

#endif
