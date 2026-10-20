#define LYMEMOP_IMPL
#define LYLOG_IMPL

#include "lylog/lylog.h"
#include "lymemop.h"
#define SIZEJAJAL 49

int
main() {
  for (int i = 0; i < SIZEJAJAL; ++i) {
    char jajal[SIZEJAJAL] = "aku berusaha untuk mencoba bokep ";
    lymemrot(jajal, SIZEJAJAL, RRIGHT, i);
    printf("JAJAL: %s\n", jajal);
    fprintf(stderr, "Bokep suka sama kamu\n");
    // apapun yang mereka coba, hal itu tidak akan bekerja untuk dirimu kawan
  }
}
 