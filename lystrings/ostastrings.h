/* NAME:  stastrings.h
 * Desc:  Implementation of Read only Static Strings / String View
 * Auth:  KillingWhales (Nur Hary)
 * TODO:  1. Implementation Function for anystrings
 *        2. menambahkan compiler option msvc
 *        3. menambahkan support untuk versi c lainnya mulai dari c99 -> c23++
 */

#if (__STDC_VERSION__ <= 199900l)
#error "lyra library can only be used on std c >= 99"
#endif

#ifndef ___LYSTASTRINGS_VERSION___
#define ___LYSTASTRINGS_VERSION___ "0.0.2"

#include <stddef.h>
#include <stdlib.h>

typedef struct {
  const char* arr;
  size_t count;
  size_t offset;
} StaStrings;

void
StaStringsNew(StaStrings* st, const char* s);
void
StaStringsTrim(StaStrings* st);
void
StaStringsSlices(StaStrings* st, int l, int r);

// Fungsi Split untuk stastrings, fungsi ini menerima 3 parameter yaitu
// stringsnya itu sendiri, seperator, dan posisi return.
// posisi return berikan nilai 0 untuk mereturn split sebelumnya dan berikan
// nilai 1 apabila ingin return strings setelah sep
StaStrings
StaStringsSplitCopy(StaStrings st, char sep, char p);
StaStrings
StaStringsSplit(StaStrings* st, char sep);
char**
StaStringsSplitMulti(StaStrings st, char sep, size_t* len);
void
lyMultiFree(char** c, size_t len);

#ifdef LYSTASTRINGS_IMPL
#include <ctype.h>
#include <string.h>

#ifndef ___LYDYNLIST_VERSION___
#error "StaStrings Membutuhkan Dynlist"
#endif // ___LYDYNLIST_VERSION___

void
StaStringsNew(StaStrings* st, const char* s) {
  st->count = strlen(s);
  st->arr = s;
}

void
StaStringsTrim(StaStrings* st) {
  while (st->count > 0 && isspace(st->arr[0])) { // THANK YOU TSODING
    st->arr++;
    st->count -= 1;
  }
  while (st->count > 0 &&
         isspace(st->arr[st->count - 1])) { // THANK YOU TSODING
    st->count -= 1;
  }
}

void
StaStringsSlices(StaStrings* st, int l, int r) {
  st->count -= r + l;
  st->offset += l;
  st->arr += l;
}

// Need More Refactors especially:
// 1. Part where it checks if i < count
// Ganti Pendekatan menjadi full slices
StaStrings
StaStringsSplitCopy(StaStrings st, char sep, char p) {
  size_t i = 0;
  while (i < st.count && st.arr[i] != sep) { // to find the position of sep
    i += 1;
  }

  if (i >= st.count) {
    StaStrings r = st;
    return r;
  }

  if (p) { // apabila p = 1
    StaStringsSlices(&st, i + 1, 0);
    st.count -= i;
    return st;
  } else {
    StaStringsSlices(&st, 0, st.count - i);
    st.count = i;
    return st;
  }
}

StaStrings
StaStringsSplit(StaStrings* st,
                char sep) { // THANKS TSODING, AGAIN
  size_t i = 0;
  while (i < st->count && st->arr[i] != sep) {
    i += 1;
  }
  if (i < st->count) {
    StaStrings r = {
        .count = i,
        .arr = st->arr,
    }; // ada masalah: kalau yang utama di free maka ini juga akan free
    StaStringsSlices(st, i + 1, 0);
    return r;
  }
  StaStrings r = *st;
  StaStringsSlices(st, st->count, 0);
  return r;
}

__LYMAYBEUNUSED
char**
StaStringsSplitMulti(StaStrings st, char sep, size_t* len) {
  int* bufid = LYNULL;
  int i = 0;
  while (i < st.count) {
    i += 1;
    if (st.arr[i] == sep) {
      lymDynlistPush(bufid, i);
    }
  }
  lymDynlistPush(bufid, st.count);
  size_t buflen = lymDynlistLen(bufid);
  int templast = 0;

  const char* curref = st.arr;
  char** curhead = (char**)malloc(sizeof(char*) * buflen);
  if (curhead == LYNULL) {
    return LYNULL;
  }
  for (int i = 0; i < buflen; i++) {
    st.arr = curref;
    if (isspace(st.arr[templast])) {
      templast += 1;
    }
    int bufsize = bufid[i] - templast;
    char* curptr = (char*)malloc(bufsize + 1);
    curptr[bufsize] = 0;
    StaStringsSlices(&st, templast, buflen - bufid[i]);
    StaStringsTrim(&st);
    memcpy(curptr, st.arr, bufsize);

    curhead[i] = curptr;
    templast = bufid[i] + 1;
  }
  *len = lymDynlistLen(bufid);
  lymDynlistFree(bufid);
  return curhead;
}

void
lyMultiFree(char** c, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    free(c[i]);
  }
  free(c);
}

#endif

#endif
