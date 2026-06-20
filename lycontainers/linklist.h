
#ifndef ___LYLINKLIST_VERSION___
#define ___LYLINKLIST_VERSION___ "0.0.2" // DO NOT USE

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef ___LYUTILS_VERSION___

#if (__STDC_VERSION__ >= 202311l)
#define LYNULL nullptr
#define LYTYPEOF typeof

#if (defined(_MSC_VER))
#define LYTYPEOF __typeof__
#endif

#else
#define LYNULL NULL
#define LYTYPEOF __typeof__

#endif

#endif

#define LY_LINKLIST(x) x*

typedef struct LinkedListConnection {
  struct LinkedListConnection* ptr;
} LLConnection;

typedef struct {
  size_t count;
} LLPtrHeader;

// Fungsi macros untuk init linklist, tidak diniatkan untuk dipanggil oleh
// pengguna akhir
#define ___lyLinkListInit(arr, val)                                            \
  {                                                                            \
    if (arr == LYNULL) {                                                       \
      LLPtrHeader* header =                                                    \
          malloc(sizeof(LLPtrHeader) + sizeof(LLConnection) + sizeof(*arr));   \
      header->count = 0;                                                       \
      LLConnection* connection = (LLConnection*)(header + 1);                  \
      connection->ptr = LYNULL;                                                \
      arr = (void*)(connection + 1);                                           \
    };                                                                         \
  }

// Macros Function to insert values to linklist
#define lyLinkListInsert(arr, val, id)                                         \
  {                                                                            \
    ___lyLinkListInit(arr, val) LLConnection* connection =                     \
        (LLConnection*)(arr) - 1;                                              \
    LLPtrHeader* header = (LLPtrHeader*)(connection) - 1;                      \
    if (id > header->count) {                                                  \
      lyLinkListPush(arr, val)                                                 \
    } else {                                                                   \
      LYTYPEOF(arr) curarr = LYNULL;                                           \
      LLConnection* curhead = malloc(sizeof(LLConnection) + sizeof(*arr));     \
      curarr = (void*)(curhead + 1);                                           \
      *curarr = val;                                                           \
      curhead->ptr = LYNULL;                                                   \
      if (id == 0) {                                                           \
        *curarr = *arr;                                                        \
        *arr = val;                                                            \
        curhead->ptr = connection->ptr;                                        \
        connection->ptr = curhead;                                             \
      } else {                                                                 \
        LLConnection* curcon = connection;                                     \
        LLConnection* lastcon = LYNULL;                                        \
        for (int i = 0; i < id; i++) {                                         \
          lastcon = curcon;                                                    \
          curcon = curcon->ptr;                                                \
        }                                                                      \
        lastcon->ptr = curhead;                                                \
        curhead->ptr = curcon;                                                 \
      }                                                                        \
      header->count++;                                                         \
    }                                                                          \
  }

// lyLinkListPush adalah fungsi Linklist untuk add anakan di bagian paling akhir
// linklist
#define lyLinkListPush(arr, val)                                               \
  {                                                                            \
    ___lyLinkListInit(arr, val) LLConnection* connection =                     \
        (LLConnection*)(arr) - 1;                                              \
    LLPtrHeader* header = (LLPtrHeader*)(connection) - 1;                      \
    if (header->count == 0) {                                                  \
      *arr = val;                                                              \
      header->count++;                                                         \
    } else {                                                                   \
      LLConnection* curhead = malloc(sizeof(LLConnection) + sizeof(*arr));     \
      curhead->ptr = LYNULL;                                                   \
      arr = (void*)(curhead + 1);                                              \
      *arr = val;                                                              \
      LLConnection* curcon = connection;                                       \
      for (int i = 1; i < header->count; i++) {                                \
        curcon = curcon->ptr;                                                  \
      }                                                                        \
      curcon->ptr = curhead;                                                   \
      header->count++;                                                         \
      arr = (void*)(connection + 1);                                           \
    }                                                                          \
  }

#define lyLinkListGetPtr(arr, mainid)                                          \
  ({                                                                           \
    LLConnection* connection = (LLConnection*)(arr) - 1;                       \
    LLPtrHeader* header = (LLPtrHeader*)(connection) - 1;                      \
    if (mainid > header->count) {                                              \
      for (int i = 0; i < mainid && i < header->count - 1; i++) {                \
        connection = connection->ptr;                                            \
      }                                                                          \
      (void*)(connection + 1);                                                   \
  })

#define lyLinkListGetArr(arr, buf)                                             \
  {                                                                            \
    LLConnection* connection = (LLConnection*)(arr) - 1;                       \
    LLPtrHeader* header = (LLPtrHeader*)(connection) - 1;                      \
    for (int i = 0; i < header->count; i++) {                                  \
      arr = (void*)(connection + 1);                                           \
      buf[i] = *arr;                                                           \
      connection = connection->ptr;                                            \
    }                                                                          \
    connection = (LLConnection*)(header + 1);                                  \
    arr = (void*)(connection + 1);                                             \
  }

#define lyLinkListLen(arr)                                                     \
  ({                                                                           \
    LLConnection* connection = (LLConnection*)(arr) - 1;                       \
    ((LLPtrHeader*)(connection) - 1)->count;                                   \
  })

#define lyLinkListDeleteId(arr, id)                                            \
  {                                                                            \
    LLConnection* connection = (LLConnection*)(arr) - 1;                       \
    LLPtrHeader* header = (LLPtrHeader*)(connection) - 1;                      \
    if (id < header->count) {                                                  \
      if (id == 0) {                                                           \
        LLConnection* curcon = connection->ptr;                                \
        typeof(*arr)* curarr = (void*)(curcon + 1);                            \
        *arr = *curarr;                                                        \
        connection->ptr = curcon->ptr;                                         \
        free(curcon);                                                          \
        header->count--;                                                       \
      } else {                                                                 \
        LLConnection* lastcon = LYNULL;                                        \
        for (int i = 0; i < id; i++) {                                         \
          lastcon = connection;                                                \
          connection = connection->ptr;                                        \
        }                                                                      \
        lastcon->ptr = connection->ptr;                                        \
        free(connection);                                                      \
        header->count--;                                                       \
      }                                                                        \
    }                                                                          \
  }

#define lyLinkListDeleteAll(arr)                                               \
  {                                                                            \
    LLConnection* connection = (LLConnection*)(arr) - 1;                       \
    LLPtrHeader* header = (LLPtrHeader*)(connection) - 1;                      \
    while (header->count > 0) {                                                \
      header->count--;                                                         \
      lyLinkListDeleteId(arr, header->count);                                  \
    }                                                                          \
  }

#define lyLinkListSwapId(arr, idx, idy)                                        \
  {                                                                            \
    LLConnection* connection = (LLConnection*)(arr) - 1;                       \
    LLPtrHeader* header = (LLPtrHeader*)(connection) - 1;                      \
    typeof(*arr) temp;                                                         \
    typeof(*arr)* arrx = LYNULL;                                               \
    typeof(*arr)* arry = LYNULL;                                               \
    int maxit = (idx < idy) ? idy : idx;                                       \
    if (idx != idy && idx < header->count && idy < header->count) {            \
      for (int i = 0; i <= maxit; i++) {                                       \
        if (i == idy)                                                          \
          arry = (void*)(connection + 1);                                      \
        if (i == idx)                                                          \
          arrx = (void*)(connection + 1);                                      \
        connection = connection->ptr;                                          \
      }                                                                        \
      temp = *arrx;                                                            \
      *arrx = *arry;                                                           \
      *arry = temp;                                                            \
    } else                                                                     \
      printf("SWAP DIBATALKAN\n");                                             \
  }

#define LL_PRINTALL(arr)                                                       \
  {                                                                            \
    LLConnection* connection = (LLConnection*)(arr) - 1;                       \
    LLPtrHeader* header = (LLPtrHeader*)(connection) - 1;                      \
    printf("ITERASI LINKLIST:\n");                                             \
    for (int i = 0; i < header->count; i++) {                                  \
      arr = (void*)(connection + 1);                                           \
      printf("ID%d:%d\n", i, *arr);                                            \
      connection = connection->ptr;                                            \
    }                                                                          \
    connection = (LLConnection*)(header + 1);                                  \
    arr = (void*)(connection + 1);                                             \
  }

// NEXT TO IMPLEMENT: DELETE PTR

#endif
