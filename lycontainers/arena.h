// FILE:  arena.h

#ifndef ___LYARENA_VERSION___
#define ___LYARENA_VERSION___ 0.01f

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
  void* base;
  void* cur;
  size_t count;
  size_t capacity;
} LyArena;

// Initialize arena / Linear Allocator
LyArena
lyArenaInit(size_t amm);

// Allocate (data) From Stack To Arena
void*
lyArenaAlloc(LyArena* ptr, void* data, size_t szs);

// Reset (ptr) Cur and Count to 0
void*
lyArenaReset(LyArena* ptr);

//
void*
lyArenaFree(LyArena* ptr);

#endif

#ifdef LYARENA_IMPL
LyArena
lyArenaInit(size_t amm) {
  char* val = malloc(sizeof(char) * amm);
  LyArena arena = (LyArena){
      .base = (void*)val, .cur = (void*)val, .count = 0, .capacity = amm};
  return arena;
}

void*
lyArenaAlloc(LyArena* ptr, void* data, size_t szs) {
  if (ptr->count + szs >= ptr->capacity) {
    return NULL;
  }
  memcpy(ptr->cur, data, sizeof(char) * szs);
  void* tp = ptr->cur;
  ptr->cur = (char*)ptr->cur + szs;
  ptr->count += szs;
  return tp;
}

void*
lyArenaReset(LyArena* ptr) {
  ptr->cur = ptr->base;
  ptr->count = 0;
}

void*
lyArenaFree(LyArena* ptr) {
  free(ptr->base);
}

#endif // LYARENA_IMPL
