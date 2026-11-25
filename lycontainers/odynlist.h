/* Files  : odynlist.h
 * Desc   : Header files untuk dynamiclist dengan implementasi
 * Revs   : Tambahkan fungi alternativ mengingat tidak semua compiler akan
 *          support return sistem untuk macros layaknya GCC (Extension)
 */

#ifndef ___LYDYNLIST_VERSION___
#define ___LYODYNLIST_VERSION___ 0.01f // OLD VERSION OF DYNLIST

#include <stddef.h>
#include <stdlib.h>

// EXPAND FROM lyutils.h
#ifndef ___LYUTILS_VERSION___
#if (__STDC_VERSION__ >= 202311l)
#define LYNULL nullptr
#else
#define LYNULL NULL
#endif
// EXPAND FROM lyutils.h
#endif // LYUTILS

#define LYM_DYNLIST(type) type*
#define ___LYMCDYNLIST_BASECAPACITY___ 2

typedef struct {
  size_t capacity;
  size_t count;
} ___LyDynlistHeader;

#define lymDynlistPush(arr, val)                                               \
  {                                                                            \
    if (arr == LYNULL) {                                                       \
      ___LyDynlistHeader* header =                                             \
          malloc(sizeof(*arr) * ___LYMCDYNLIST_BASECAPACITY___ +               \
                 sizeof(___LyDynlistHeader));                                  \
      header->capacity = ___LYMCDYNLIST_BASECAPACITY___;                       \
      header->count = 0;                                                       \
      arr = (void*)(header + 1);                                               \
    };                                                                         \
    ___LyDynlistHeader* header = (___LyDynlistHeader*)(arr) - 1;               \
    if (header->count >= header->capacity) {                                   \
      header->capacity *= 1.5;                                                 \
      header = realloc(header, sizeof(*arr) * header->capacity +               \
                                   sizeof(___LyDynlistHeader));                \
      arr = (void*)(header + 1);                                               \
    }                                                                          \
    (arr)[header->count++] = (val);                                            \
  }

#define lymDynlistFree(arr)                                                    \
  free((___LyDynlistHeader*)(arr) - 1);                                        \
  arr = LYNULL
#define lymDynlistLen(arr) ((___LyDynlistHeader*)(arr) - 1)->count

// Duplication Method For Copying Char* / Strings
char*
LyDynListCharDup(char* s);

// Freeing Strings From Dynlist
void
LyDynlistCharFree(char** d);

#ifdef LYDYNLIST_IMPL
#ifndef ___LYMEMOP_VERSION___
#error "Dynlist need lymemop"
#endif // ___LYMEMOP_VERSION___
char*
LyDynListCharDup(char* s) {
  int len = strlen(s);
  char* val = malloc(sizeof(char) * len + 1);
  lymemcpy(s, len + 1, val, len + 1);
  return val;
}
void
LyDynlistCharFree(char** d) {
  size_t len = lymDynlistLen(d);
  for (size_t i = 0; i < len; ++i) {
    free(d[i]);
  }
}
#endif // LYDYNLIST_IMPL

#endif
