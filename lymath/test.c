#define LYVEC_IMPL
#include "vec.h"

#include <stdio.h>

int
main() {

  v2 jajal = {3.0, -4.0};
  printf("01: %f, %f\n", jajal.x, jajal.y);
  v2 normja = ly_v2norm(jajal.e);
  printf("01: %f, %f\n", normja.x, normja.y);
  ly_v2pnorm(jajal.e);
  printf("01: %f, %f\n", jajal.x, jajal.y);
  

  return 0;
}
