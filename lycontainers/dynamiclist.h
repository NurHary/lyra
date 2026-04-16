/* Files  : dynamiclist.h
 * Desc   : Header files untuk dynamiclist dengan implementasi  
 *
 *
 */

#ifndef DYNLIST
#define DYNLIST

#include "../lyutils.h"
#include <stddef.h>
#include <stdlib.h>

#define LYMCONTAINER_DYNLIST(type) type*
#define BASECAPACITY 2

typedef struct {
  // Placeholder
  size_t capacity;
  size_t count;
} Lycontainer_DynlistHeader;

#define LYMCONTAINER_DYNLIST_PUSH(arr, val)\
{\
  if (arr==NULL){\
    Lycontainer_DynlistHeader* header = malloc(sizeof(*arr)*BASECAPACITY + sizeof(Lycontainer_DynlistHeader));\
    header->capacity = BASECAPACITY;\
    header->count = 0;\
    arr = (void*)(header+1);\
    printf("Cap Init %lu\n", header->capacity);\
  };\
  Lycontainer_DynlistHeader* header = (Lycontainer_DynlistHeader*)(arr)-1;\
  if (header->count >= header->capacity){\
    header->capacity *= 1.5;\
    header = realloc(header, sizeof(*arr)*header->capacity + sizeof(Lycontainer_DynlistHeader));\
    arr = (void*)(header+1);\
    printf("Cap Now %lu\n", header->capacity);\
  }\
  (arr)[header->count++] = (val);\
}\

#define LYMCONTAINER_DYNLIST_FREE(arr) free((Lycontainer_DynlistHeader*)(arr)-1);arr=NULL
#define LYMCONTAINER_DYNLIST_LEN(arr) ((Lycontainer_DynlistHeader*)(arr)-1)->count

// tambahkan fungsi untuk trim

#endif
