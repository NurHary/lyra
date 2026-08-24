#define LYDYNLISTGEN_IMPL
#include "dynlistgen.h"
#include <stdio.h>

LyDynlistGenerate(Bokep, int);

int
main() {
  LyDynlistBokep jajal = {0};
  LyDynlistBokepPush(&jajal, 10);
  LyDynlistBokepPush(&jajal, 20);
  LyDynlistBokepPush(&jajal, 30);
  LyDynlistBokepPush(&jajal, 50);
  LyDynlistBokepPush(&jajal, 40);
  LyDynlistBokepPush(&jajal, 70);
  for (int i = 0; i < jajal.count; ++i) {
    printf("Id: %d = %d\n", i, jajal.data[i]);
  }
  LyDynlistBokepFree(&jajal);
  printf("JAJAL: %lu", jajal.capacity);
}
