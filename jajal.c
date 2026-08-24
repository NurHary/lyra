#define LYMEMOP_IMPL
#define LYLOG_IMPL

#include "lylog/lylog.h"
#include "lymemop.h"
#define SIZEJAJAL 30

int
main() {
  for (int i = 0; i < SIZEJAJAL; ++i) {
    char jajal[SIZEJAJAL] = "aku berusaha untuk mencobanya ";
    lymemrot(jajal, SIZEJAJAL, RRIGHT, i);
    printf("JAJAL: %s\n", jajal);
  }
}
