/* Files  : dynamiclist.h
 * Desc   : Header files untuk dynamiclist dengan implementasi
 * Revs   : Tambahkan fungi alternativ mengingat tidak semua compiler akan
 *          support return sistem untuk macros layaknya GCC (Extension)
 */

#ifndef ___LYDYNLIST_VERSION___
#define ___LYDYNLIST_VERSION___ "0.0.1"

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

#endif

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

#endif
