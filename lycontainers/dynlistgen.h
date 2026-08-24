#ifndef ___LYDYNLIST_VERSION___
#define ___LYDYNLIST_VERSION___ 0.01f

// EXPAND FROM lyutils.h
#ifndef ___LYUTILS_VERSION___
#include <stddef.h>
#include <stdlib.h>

#define ___LYMCDYNLIST_BASECAPACITY___ 2

#if (__STDC_VERSION__ >= 202311l)
#define LYNULL nullptr
#else
#define LYNULL NULL
#endif
// EXPAND FROM lyutils.h
#endif // LYUTILS

#ifdef LYDYNLISTGEN_IMPL
#define LyDynlistGenerate(name, type)                                          \
  typedef struct {                                                             \
    size_t capacity;                                                           \
    size_t count;                                                              \
    type* data;                                                                \
  } LyDynlist##name;                                                           \
                                                                               \
  void LyDynlist##name##Init(LyDynlist##name* data) {                          \
    data->data = malloc(sizeof(type) * ___LYMCDYNLIST_BASECAPACITY___);        \
    if (data->data == LYNULL)                                                  \
      return;                                                                  \
    data->capacity = ___LYMCDYNLIST_BASECAPACITY___;                           \
    data->count = 0;                                                           \
  };                                                                           \
                                                                               \
  void LyDynlist##name##Push(LyDynlist##name* data, type val) {                \
    if (data->data == LYNULL)                                                  \
      LyDynlist##name##Init(data);                                             \
    if (data->count >= data->capacity) {                                       \
      data->capacity *= 2;                                                     \
      type* tmp = realloc(data->data, sizeof(type) * data->capacity);          \
      if (tmp)                                                                 \
        data->data = tmp;                                                      \
    }                                                                          \
    data->data[data->count] = val;                                             \
    data->count++;                                                             \
  };                                                                           \
                                                                               \
  void LyDynlist##name##Free(LyDynlist##name* data) {                          \
    free(data->data);                                                          \
    data->data = LYNULL;                                                       \
    data->capacity = 0;                                                        \
    data->count = 0;                                                           \
  };
#else

#define LyDynlistGenerate(name, type)                                          \
  typedef struct {                                                             \
    size_t capacity;                                                           \
    size_t count;                                                              \
    type* data;                                                                \
  } LyDynlist##name;                                                           \
                                                                               \
  void LyDynlist##name##Init(LyDynlist##name* data);                           \
  void LyDynlist##name##Push(LyDynlist##name* data, type val);                 \
  void LyDynlist##name##Free(LyDynlist##name* data);

#endif

#endif
