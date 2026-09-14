#define LYARENA_IMPL
#include "arena.h"

#include <stdio.h>

typedef struct {
  int jagal;
  float uji;
} Jajal;

void* val = NULL;
int con = 0;

int
main() {
  LyArena jajal = lyArenaInit(sizeof(Jajal) * 10); // 10 size_t
  Jajal* values2 =
      lyArenaAlloc(&jajal, &((Jajal){.jagal = 10, .uji = 3.f}), sizeof(Jajal));
  printf("S: %d, %f\n", values2->jagal, values2->uji);
  lyArenaFree(&jajal);
}
