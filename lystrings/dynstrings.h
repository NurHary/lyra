// Name:  dynstrings.h
// Desc:  Module for dynamic sized list using malloc

#ifndef ___LYDYNSTRINGS_VERSION___
#define ___LYDYNSTRINGS_VERSION___ "0.0.1"

#include <stddef.h>

// // // DECLARATION // // //
typedef struct {
  size_t capacity;
  size_t count;
  size_t offset;
  char* arr;
} DynStrings;

void
DynStringsInit(DynStrings* st);
void
DynStringsNew(DynStrings* st, char* s);
void
DynStringsReRender(DynStrings* st);
void
DynStringsCat(DynStrings* st, char* s);
void
DynStringsToNts(DynStrings st, char* t);
void
DynStringsCpy(DynStrings* st, DynStrings* t);
void
DynStringsFree(DynStrings* st);
void
DynStringsSlice(DynStrings* st, int l, int r);
void
DynStringsAddCount(DynStrings* st, int l, int r);
void
DynStringsResetSlices(DynStrings* st);
void
DynStringsTrim(DynStrings* st);
DynStrings
DynStringsSplit(DynStrings* st, char sep);
char**
DynStringsSplitMulti(DynStrings st, char sep);

// // // IMPLEMENTATION // // //

#define ___LYDYNSTRINGS_IMP___
#ifdef ___LYDYNSTRINGS_IMP___

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// EXPAND FROM lyutils.h
#ifndef ___LYUTILS_VERSION___
#if (__STDC_VERSION__ >= 202311l)
#define LYNULL nullptr
#else
#define LYNULL NULL
#endif
// EXPAND FROM lyutils.h

// #include "../lycontainers/dynlist.h"
// EXPAND FROM dylist.h
#ifndef ___LYDYNLIST_VERSION___
#define ___LYDYNLIST_VERSION___ "0.0.1"
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
// EXPAND FROM dylist.h

// IMPLEMENTATION OF DynStrings

#define DYNSTRINGSBASECAPACITY 1
#define DYNSTRINGS char*

// TO FIX: UBAH LITERALLY DARI NULLTERMINATED
void
DynStringsInit(DynStrings* st) {
  if (st->arr == nullptr) {
    st->arr = malloc(DYNSTRINGSBASECAPACITY);
    st->capacity = DYNSTRINGSBASECAPACITY;
    // st->arr[st->capacity - 1] = 0;
    st->count = 0;
    st->offset = 0;
  };
}

/* create new DynStrings with input of dynstrings itself and strings, it will
 * override if the dynstrings already have a values
 */
void
DynStringsNew(DynStrings* st, char* s) {
  DynStringsInit(st);
  int lstr = strlen(s);
  if (lstr >= st->capacity) {
    st->capacity = lstr;
    char* tmp = realloc(st->arr, st->capacity + 1);
    if (tmp == NULL) {
      return;
    }
    st->arr = tmp;

    st->arr[lstr] = 0;
  }
  st->count = lstr;
  memcpy(st->arr, s, lstr + 1);
}

void
DynStringsReRender(DynStrings* st) {
  if (st->count != st->capacity || st->offset != 0) {
    char tempchar[st->count];
    memcpy(tempchar, st->arr, st->count);
    st->arr -= st->offset;
    st->offset = 0;
    st->arr = realloc(st->arr, st->count);
    st->capacity = st->count;
    memcpy(st->arr, tempchar, st->count);
  }
}

void
DynStringsCat(DynStrings* st, char* s) {
  DynStringsReRender(st);
  DynStringsInit(st);
  int lstr = strlen(s);
  st->capacity += lstr;
  st->arr = realloc(st->arr, st->capacity);
  for (int i = 0; i < lstr; i++) {
    st->arr[st->count + i] = s[i];
  }
  st->count += lstr;
}

void
DynStringsToNts(DynStrings st, char* t) {
  memcpy(t, st.arr, st.count - st.offset);
  t[st.count] = 0; // add Stupid Null
}

void
DynStringsCpy(DynStrings* st, DynStrings* t) {
  DynStringsNew(t, st->arr);
}

void
DynStringsFree(DynStrings* st) {
  st->arr -= st->offset;
  free(st->arr);
}

void
DynStringsSlice(DynStrings* st, int l, int r) {
  st->count -= r + l;
  st->arr += l;
  st->offset += l;
}

// Function to add len based on the values, if v exceed the capacity / offset,
// it will truncate to maximum
void
DynStringsAddCount(DynStrings* st, int l, int r) {
  if (st->count + r <= st->capacity) {
    st->count += r;
  } else {
    st->count = strlen(st->arr);
  }
  if (l < st->offset) {
    st->arr -= l;
    st->offset -= l;
  } else {
    st->arr -= st->offset;
    st->offset = 0;
  }
}

// Function To Reset Slices / reset offset to zero and count to capacity
void
DynStringsResetSlices(DynStrings* st) {
  st->arr -= st->offset;
  st->offset = 0;
  st->count = strlen(st->arr);
}

/* Trim strings from space on left and rights
 */
void
DynStringsTrim(DynStrings* st) {
  while (st->count > 0 && isspace(st->arr[0])) { // THANK YOU TSODING
    DynStringsSlice(st, 1, 0);
  }
  while (st->count > 0 && isspace(st->arr[st->count - 1])) {
    DynStringsSlice(st, 0, 1);
  }
}

/* Function to split strings from the seperators, it return char** which is
 * null terminated, Kinda Unsafe Bruh
 */

DynStrings
DynStringsSplit(DynStrings* st, char sep) { // THANKS TSODING, AGAIN
  size_t i = 0;
  while (i < st->count && st->arr[i] != sep) {
    i += 1;
  }
  if (i < st->count) {
    DynStrings r = {
        .count = i,
        .capacity = i,
        .arr = st->arr,
        .offset =
            0}; // ada masalah: kalau yang utama di free maka ini juga akan free
    DynStringsSlice(st, i + 1, 0);
    return r;
  }
  DynStrings r = *st;
  DynStringsSlice(st, st->count, 0);
  return r;
}

[[maybe_unused]]
char**
DynStringsSplitMulti(DynStrings st, char sep) { // TO REFACTOR
  int* bufid = nullptr;
  for (int i = 0; i < st.count; i++) {
    if (st.arr[i] == sep) {
      lymDynlistPush(bufid, i);
    }
  }
  lymDynlistPush(bufid, st.count);
  size_t buflen = lymDynlistLen(bufid);
  int templast = 0;

  char** curhead = (char**)malloc(sizeof(char*) * buflen);
  if (curhead == NULL) {
    return NULL;
  }

  for (int i = 0; i < buflen; i++) {
    if (isspace(st.arr[templast])) {
      templast += 1;
    }
    int bufsize = bufid[i] - templast;
    char* curptr = (char*)malloc(bufsize + 1);
    curptr[bufsize] = 0;
    DynStringsSlice(&st, templast, buflen - bufid[i]);
    DynStringsTrim(&st);
    memcpy(curptr, st.arr, bufsize);
    DynStringsResetSlices(&st);
    curhead[i] = curptr;
    templast = bufid[i] + 1;
  }

  lymDynlistFree(bufid);
  return curhead;
}

#ifdef MACROIMPLEMENTATION
#define DynStringsNew(arr, s)                                                  \
  {                                                                            \
    if (arr == nullptr) {                                                      \
      DynStringsHeader* header = malloc(                                       \
          sizeof(DynStringsHeader) + sizeof(char) * DYNSTRINGSBASECAPACITY);   \
      header->capacity = DYNSTRINGSBASECAPACITY;                               \
      header->count = 0;                                                       \
      arr = (char*)(header + 1);                                               \
    };                                                                         \
    int lstr = strlen(s);                                                      \
    DynStringsHeader* header = (DynStringsHeader*)(arr) - 1;                   \
    if (header->count + lstr >= header->capacity) {                            \
      header->capacity = lstr * 1.25;                                          \
      header = realloc(header, sizeof(*arr) * header->capacity +               \
                                   sizeof(DynStringsHeader));                  \
      arr = (char*)(header + 1);                                               \
    }                                                                          \
    for (int i = 0; i <= lstr; i++) {                                          \
      (arr)[i] = (s[i]);                                                       \
    }                                                                          \
  }

#define DynStringsCat(arr, s)

#define DynStringsFree(arr)                                                    \
  free((DynStringsHeader*)(arr) - 1);                                          \
  arr = nullptr
#define DynStringsLen(arr) ((DynStringsHeader*)(arr) - 1)->count
#endif

#endif
#endif
