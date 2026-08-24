// FILE:  hashmap.h
// DESC:  Single-Header Library for lyra hashmap
// NOTE:  do not use! still under massive development and expected to have tons
//        of bug

#ifndef ___LYHASHMAP_VERSION___
#define ___LYHASHMAP_VERSION___ 0.01f
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define LYM_HASHMAP(type) type**

#ifndef ___LYMEMOP_VERSION___
#error "Must Include lymemop"
#endif

typedef struct {
  size_t capacity;
  size_t count;
  size_t allcount;
} ___HashMapHeader;

typedef struct {
  char* key;
  uint32_t hash;
} ___HashItemHeader;

typedef struct HashNodes {
  ___HashItemHeader items; // 64 + 32
  struct HashNodes* pnext; // 64
} HashNodes;

#define ___LYMCHASHMAP_BASECAPACITY___ 2

// Fungsi untuk menambahkan val ke dalam arr dengan tambahan key dan hash
#define ___lymCollisionBucketPush(arr, val, pkey, phash)                       \
  do {                                                                         \
    HashNodes* new_node = malloc(sizeof(HashNodes) + sizeof(*arr));            \
                                                                               \
    if (new_node == NULL) {                                                    \
      fprintf(stderr, "Error Pada Malloc Collision Bucket Push\n");            \
      exit(400);                                                               \
    }                                                                          \
    new_node->items.key = pkey;                                                \
    new_node->items.hash = phash;                                              \
                                                                               \
    if (arr == NULL) {                                                         \
      new_node->pnext = NULL;                                                  \
    } else {                                                                   \
      new_node->pnext = (HashNodes*)(arr) - 1;                                 \
    }                                                                          \
    arr = (void*)(new_node + 1);                                               \
    *arr = val;                                                                \
  } while (0)

#define ___lymCollisionBucketPushMem(arr, pos, pkey, phash)                    \
  do {                                                                         \
    HashNodes* new_node = malloc(sizeof(HashNodes) + sizeof(*arr));            \
                                                                               \
    if (new_node == NULL) {                                                    \
      fprintf(stderr, "Error Pada Malloc Collision Bucket Push\n");            \
      exit(400);                                                               \
    }                                                                          \
    new_node->items.key = pkey;                                                \
    new_node->items.hash = phash;                                              \
                                                                               \
    if (arr == NULL) {                                                         \
      new_node->pnext = NULL;                                                  \
    } else {                                                                   \
      new_node->pnext = (HashNodes*)(arr) - 1;                                 \
    }                                                                          \
    arr = (void*)(new_node + 1);                                               \
    lymemcpy(pos, sizeof(*arr), (void*)arr, sizeof(*arr));                     \
  } while (0)

#define ___lymCollisionBucketFreeAll(arr)                                      \
  HashNodes* curconnection = (HashNodes*)(arr) - 1;                            \
  while (curconnection != NULL) {                                              \
    HashNodes next = curconnection->pnext;                                     \
    free(curconnection);                                                       \
    curconnection = next;                                                      \
  }                                                                            \
  arr = NULL;

// Macros Function To Init and Start To Put Keys and Values To Hashmap
#define lymHashMapPut(map, key, val)                                           \
  do {                                                                         \
    if (map == NULL) {                                                         \
      ___HashMapHeader* header =                                               \
          malloc(sizeof(___HashMapHeader) +                                    \
                 sizeof(map) * ___LYMCHASHMAP_BASECAPACITY___);                \
      header->capacity = ___LYMCHASHMAP_BASECAPACITY___;                       \
      header->count = 0;                                                       \
      header->allcount = 0;                                                    \
      map = (void*)(header + 1);                                               \
    }                                                                          \
    ___HashMapHeader* header = (___HashMapHeader*)(map) - 1;                   \
    if (header->count >= header->capacity) {                                   \
      lymHashMapUpdate(map);                                                   \
      header = (___HashMapHeader*)(map) - 1;                                   \
    }                                                                          \
    uint32_t hashval = ____hashfunction(key);                                  \
    uint32_t hashid = hashval % header->capacity;                              \
    if (map[hashid] == NULL) {                                                 \
      header->count++;                                                         \
    }                                                                          \
    header->allcount++;                                                        \
    ___lymCollisionBucketPush(map[hashid], val, key, hashval);                 \
  } while (0)

// Macros Function to get items based on the keys and output to buf as HashNodes
#define lymHashMapGetItemsNodes(map, pkey, buf)                                \
  do {                                                                         \
    ___HashMapHeader* header = (___HashMapHeader*)(map) - 1;                   \
    uint32_t hashval = ____hashfunction(pkey);                                 \
    uint32_t hashid = hashval % header->capacity;                              \
    if (map[hashid] == NULL) {                                                 \
      fprintf(stderr,                                                          \
              "LOG | HashMap Get Nodes: Tidak Menemukan Nilai pada pkey: %s "  \
              "id: %d\n",                                                      \
              pkey, hashid);                                                   \
    } else {                                                                   \
      buf = (HashNodes*)(map[hashid]) - 1;                                     \
      while (buf != NULL) {                                                    \
        if (buf->items.hash == hashval &&                                      \
            strcmp((void*)buf->items.key, (void*)pkey) == 0) {                 \
          break;                                                               \
        }                                                                      \
        buf = buf->pnext;                                                      \
      }                                                                        \
    }                                                                          \
  } while (0)

// Macros Function to get items values
#define lymHashMapGetValPtr(map, pkey, buf)                                    \
  do {                                                                         \
    ___HashMapHeader* header = (___HashMapHeader*)(map) - 1;                   \
    uint32_t hashval = ____hashfunction(pkey);                                 \
    uint32_t hashid = hashval % header->capacity;                              \
    if (map[hashid] == NULL) {                                                 \
      fprintf(stderr,                                                          \
              "LOG | HashMap Get Ptr: Tidak Menemukan Nilai pada pkey: %s "    \
              "id: %d\n",                                                      \
              pkey, hashid);                                                   \
    } else {                                                                   \
      HashNodes* trav = (HashNodes*)(map[hashid]) - 1;                         \
      while (trav != NULL) {                                                   \
        if (trav->items.hash == hashval &&                                     \
            strcmp((void*)trav->items.key, (void*)pkey) == 0) {                \
          buf = (void*)(trav + 1);                                             \
          break;                                                               \
        }                                                                      \
        trav = trav->pnext;                                                    \
      }                                                                        \
    }                                                                          \
  } while (0)

#define lymHashMapUpdate(map)                                                  \
  do {                                                                         \
    ___HashMapHeader* header = (___HashMapHeader*)(map) - 1;                   \
    size_t ol_cap = header->capacity;                                          \
    header->capacity = header->capacity * 1.5;                                 \
    header = realloc(header, sizeof(___HashMapHeader) +                        \
                                 sizeof(map) * header->capacity);              \
    lymemset((void**)((char*)(header + 1) + sizeof(map) * ol_cap), 0,          \
             sizeof(map) * (header->capacity - ol_cap));                       \
    map = (void*)(header + 1);                                                 \
                                                                               \
    for (size_t i = 0; i < header->count; ++i) {                               \
      if (map[i] == NULL)                                                      \
        continue;                                                              \
                                                                               \
      HashNodes* curconnection = (HashNodes*)(map[i]) - 1;                     \
      map[i] = NULL;                                                           \
      while (curconnection != NULL) {                                          \
        HashNodes* nextcon = curconnection->pnext;                             \
        uint32_t new_index = curconnection->items.hash % header->capacity;     \
        if (map[new_index] != NULL) {                                          \
          HashNodes* tgt = (HashNodes*)(map[new_index]) - 1;                   \
          curconnection->pnext = tgt;                                          \
        } else {                                                               \
          curconnection->pnext = NULL;                                         \
        }                                                                      \
        map[new_index] = (void*)(curconnection + 1);                           \
        curconnection = nextcon;                                               \
      }                                                                        \
    }                                                                          \
  } while (0)

// TODO
#define lymHashMapRemove(hash, key)
// TODO
#define lymHashMapFree(hash)

uint32_t
____hashfunction(char* s);
void*
___lyHashMapItemGets(HashNodes* p);

#ifdef LYHASHMAP_IMPL

void*
___lyHashMapItemGets(HashNodes* p) {
  if (p == NULL)
    return NULL;
  return (void*)(p + 1);
}

uint32_t
____fmix32(uint32_t h) {
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;

  return h;
}

uint32_t
____hashfunction(char* s) {
  uint32_t Seed = 0x091190, C1 = 0xcc9e2d51, C2 = 0x1b873593, N = 0xe6546b64;
  uint8_t M = 5, R1 = 15, R2 = 13;
  size_t len = strlen(s);
  int32_t tv = len / 4, *Chunks = (int32_t*)s;
  int32_t hash = Seed, k;
  for (int i = 0; i < tv; ++i) {
    k = Chunks[i];
    k *= C1;
    lymemrot((void*)&k, sizeof(k), RLEFT, R1);

    hash ^= k;
    lymemrot((void*)&hash, sizeof(hash), RLEFT, R2);
    hash = (hash * M) + N;
  }

  const uint8_t* t = (uint8_t*)s + tv * 4;
  k = 0;

  switch (len & 3) { // equal as % 4
  case 3:
    k ^= t[2] << 16;
  case 2:
    k ^= t[1] << 8;
  case 1:
    k ^= t[0];
    k *= C1;
    lymemrot((void*)&k, sizeof(k), RLEFT, R1);
    k *= C2;
    hash ^= k;
  }
  hash ^= len;
  hash = ____fmix32(hash);

  return hash;
}
#endif // LYHASHMAP_IMPL
#endif //___LYHASHMAP_VERSION___
