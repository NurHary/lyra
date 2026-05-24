/*
 * NAME:  lylog.h
 * DESC:  Header To Enable Logging Systems In Lyra
 * NOTE:  Fungsi masih belum benar - benar bisa menghandle nilai yang setelahnya
 * /
 */

#include <wchar.h>
#ifndef LYLOG_VERSION
#define LYLOG_VERSION "0.0.3"

#define RGBTOANSI(r, g, b) "\033[38;2;" #r ";" #g ";" #b "m"

// TO ACCESS DEFAULT MSG AND CLR
#define LYMC_LOGDEFAULT(X)                                                     \
  X(ERROR, RGBTOANSI(255, 0, 0))                                               \
  X(WARN, RGBTOANSI(0, 255, 0))                                                \
  X(INFO, RGBTOANSI(0, 0, 255))                                                \
  X(FATAL, RGBTOANSI(0, 0, 255))

// You Can Define Your Own Log Colors Before This,
#ifndef LYM_SETLOG
#define LYM_SETLOG(X) LYMC_LOGDEFAULT(X)
#endif

#define LYM_SETLOGENUM(e, c) e,
#define LYM_SETLOGENUMSTR(e, c) #e,
#define LYM_SETLOGCOLOR(e, c) c,

typedef enum { LYM_SETLOG(LYM_SETLOGENUM) LENGTH } LYLOGE_LOGTYPE;

// DISABLE DEBUG
#ifndef LY_BUILD_MODE

#include "../lyutils.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

#define LYMC_LOGITALIC "\e[3m"
#define LYM_LOGCOLORFG "\033[38;2;"
#define LYMC_LOGCOLORBG "\033[48;2;"
#define LYMC_LOGFORMATEND "\033[0m"

// // // MACRO PRINT FORMAT // // //

#define lym_printlog(LYLOGE_LOGTYPE, ...)                                      \
  ___print_log(__FILE__, __LINE__, LYLOGE_LOGTYPE, __VA_ARGS__)

// // // STRUCT // // //

// MAXIMUM CALLBACk FOR LOGGING
#define ___MAXIMUM_CALL 32

typedef struct {
  va_list ap;
  const char* fmt;
  const char* file;
  struct tm* time;
  void* prtout;
  i32 line;
  i32 msge;
} LyLogEvent;

typedef void (*log_LogFn)(LyLogEvent* ev);
typedef void (*log_LockFn)(bool lock, void* udata);

typedef struct {
  log_LogFn fn;
  void* udata;
  i32 msge;
} ___Callback;

static struct {
  void* udata;
  log_LockFn lock;
  i32 msge;
  i8 fileinfo : 1;
  i8 justtxt : 1;
  ___Callback callback[___MAXIMUM_CALL];
} ___L;

// IMPLEMENTATION

/// VARIABLES ///
// TIPE LOG ENUM NYA MODEL STRING
const char* LYGC_LOGMSG[] = {LYM_SETLOG(LYM_SETLOGENUMSTR)};
// TIPE WARNA LOG ENUM NYA
const char* LYGC_LOGCOLORS[] = {LYM_SETLOG(LYM_SETLOGCOLOR)};

/// CONFIG ///
/// Fungsi konfigurasi untuk hanya melihat Error bagian mana saja yang muncul
void
lylogConfLSetLevel(i32 msge) {
  ___L.msge = msge;
}

/// Fungsi konfigurasi untuk menambahkan info file juga pada logging
void
lylogConfToggleFileInfo() {
  ___L.fileinfo = !___L.fileinfo;
}
void
lylogConfToggleTxtOnly() {
  ___L.justtxt = !___L.justtxt;
}

/// /// ///

static void
____lock_L(void) {
  if (___L.lock) {
    ___L.lock(true, ___L.udata);
  }
}

static void
____unlock_L(void) {
  if (___L.lock) {
    ___L.lock(false, ___L.udata);
  }
}

/// Fungsi untuk init event, memberikan nilai waktu, dan output keluar
/// (standardnya stderr)
static void
___initialize_event(LyLogEvent* ev, void* ptrout) {
  if (!ev->time) {
    time_t t = time(NULL);
    ev->time = localtime(&t);
  }
  ev->prtout = ptrout;
}

static void
____printout_callback(LyLogEvent* ev) {
  char buf[16];
  buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] =
      '\0'; // damn, this implementation
  if (___L.justtxt) {
  } else if (___L.fileinfo) {
    fprintf(ev->prtout, "%s %s%s %s " LYMC_LOGFORMATEND, buf, ev->file,
            LYGC_LOGCOLORS[ev->msge], LYGC_LOGMSG[ev->msge]);
  } else {
    fprintf(ev->prtout, "%s%s %s " LYMC_LOGFORMATEND, buf,
            LYGC_LOGCOLORS[ev->msge], LYGC_LOGMSG[ev->msge]);
  }
  vfprintf(ev->prtout, ev->fmt, ev->ap);
  fprintf(ev->prtout, "\n");
  fflush(ev->prtout);
}

void
___print_log(const char* f, i32 l, LYLOGE_LOGTYPE t, char* fmt, ...) {
  // fprintf(stderr, "%s %s JAJAL %s" LYMC_LOGFORMATEND, LYGC_LOGMSG[t],
  //         LYGC_LOGCOLORS[t], m);
  LyLogEvent ev = {
      .fmt = fmt,
      .file = f,
      .line = l,
      .msge = t,
  };
  ____lock_L(); // LOCK

  if (t >= ___L.msge) {
    ___initialize_event(&ev, stderr);
    va_start(ev.ap, fmt);
    ____printout_callback(&ev);
    va_end(ev.ap);
  }

  for (int i = 0; i < ___MAXIMUM_CALL && ___L.callback[i].fn; i++) {
    ___Callback* cb = &___L.callback[i];
    if (t >= cb->msge) {
      ___initialize_event(&ev, cb->udata);
      va_start(ev.ap, fmt);
      ____printout_callback(&ev);
      va_end(ev.ap);
    }
  }

  ____unlock_L();
}

#else
#define lym_printlog(LYLOGE_LOGTYPE, ...)
#define lylogConfToggleFileInfo()
#define lylogConfToggleTxtOnly()
#define lylogConfLSetLevel(msge)
#endif

#endif
