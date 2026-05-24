

#define LYM_SETLOG(X)                                                          \
  X(BRUTAL, RGBTOANSI(255, 0, 0))                                              \
  LYMC_LOGDEFAULT(X)

#include "../lylog/lylog.h"

int
main() {
  lylogConfToggleFileInfo();
  lym_printlog(BRUTAL, "ADAPUN YANG MEREKA COBA, %d", 5);
  lym_printlog(ERROR, "ADAPUN YANG MEREKA COBA, %f", 12.5);

  lylogConfToggleFileInfo();
  lym_printlog(INFO, "ADAPUN YANG MEREKA COBA, %s", "HAI SAYANG");
  lym_printlog(WARN, "ADAPUN YANG MEREKA COBA, %c", 110);
  return 0;
}
