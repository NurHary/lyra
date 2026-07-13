#include <stdio.h>

#define LYSTASTRINGS_IMPL
#include "stastrings.h"

int
main() {
  StaStrings jajal = {0};
  StaStringsNew(&jajal, "BOKEP SUKA KAMU, KAMU SUKA BOKEP");
  StaStrings bokap = StaStringsSplitCopy(jajal, ',', 1);
  printf("1: %.*s\n", (int)jajal.count, jajal.arr);
  printf("2: %.*s\n", (int)bokap.count, bokap.arr);
  StaStrings bekop = StaStringsSplit(&jajal, ',');
  printf("3: %.*s\n", (int)jajal.count, jajal.arr);
  printf("4: %.*s\n", (int)bekop.count, bekop.arr);

  return 0;
}
