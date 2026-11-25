#define ___C_LYARENA_VERSION___ 0.01f

#include <arena.h>

// Function to init Arena, return arena with base that get mmapped
LyArena
lyArenaInit(size_t amm) {
  char* val = mmap(NULL, amm, PROT_READ | PROT_WRITE,
                   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  LyArena arena = (LyArena){
      .base = (void*)val, .cur = (void*)val, .count = 0, .capacity = amm};
  return arena;
}

// Allocate (data) with size of (szs) to arena* (ptr)
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

// Reset count and cur of Arena* (ptr)
void*
lyArenaReset(LyArena* ptr) {
  ptr->cur = ptr->base;
  ptr->count = 0;
}

// Free Arena* (ptr) base
void
lyArenaFree(LyArena* ptr) {
  munmap(ptr->base, ptr->capacity);
}
