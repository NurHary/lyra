
// #define LYM_SETLOG(X) LYMC_LOGDEFAULT(X)

#define LYLOG_IMPL
#include "../lylog/lylog.h"
#include <stdio.h>
#include <string.h>

enum { JAJALOKE, JAJALAHA };

int
main() {

  lym_printlog(FATAL, "JAJAL UHUY");

  return 0;
}
