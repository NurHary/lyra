#define ___LYLOG_IMP___
#include "../lylog/lylog.h"

void
printou_function_shit();
void
printour();

int
main() {
  lylogConfToggleFileInfo();
  lym_printlog(WARN, "ADAPUN YANG MEREKA COBA, %d", 5);
  lym_printlog(ERROR, "ADAPUN YANG MEREKA COBA, %f", 12.5);

  lylogConfToggleFileInfo();
  lym_printlog(INFO, "ADAPUN YANG MEREKA COBA, %s", "HAI SAYANG");
  lym_printlog(WARN, "ADAPUN YANG MEREKA COBA, %c", 110);

  printou_function_shit();
  printour();
  return 0;
}
