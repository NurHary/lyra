// FILE:  arena.h
// DESC:  Container for arena

#ifndef ___LYARENA_VERSION___
#define ___LYARENA_VERSION___ 0.01f

#include <stddef.h>
#include <string.h>
#include <sys/mman.h>
typedef struct {
  void* base, *cur;
  size_t count, cap;
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

// Free Arena / Deallocate Arena
void
lyArenaFree(LyArena* ptr);

#endif




#ifdef LYARENA_IMPL

// Function to init Arena, return arena with base that get mmapped
LyArena
lyArenaInit(size_t amm) {
  char* val = mmap(NULL, amm, PROT_READ | PROT_WRITE,
                   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  LyArena arena = (LyArena){
      .base = (void*)val, .cur = (void*)val, .count = 0, .cap = amm};
  return arena;
}

// Allocate (data) with size of (szs) to arena* (ptr)
void*
lyArenaAlloc(LyArena* ptr, void* data, size_t szs) {
  if (ptr->count + szs >= ptr->cap) {
    return NULL;
  }
  memcpy(ptr->cur, data, sizeof(char) * szs);
  void* tp = ptr->cur;
  ptr->cur = (char*)ptr->cur + szs;
  ptr->count += szs;
  return tp;
}

// Reset count and cur of Arena* (ptr)
void*
lyArenaReset(LyArena* ptr) {
  ptr->cur = ptr->base;
  ptr->count = 0;
}

// Free Arena* (ptr) base
void
lyArenaFree(LyArena* ptr) {
  munmap(ptr->base, ptr->cap);
}

#endif // LYARENA_IMPL
