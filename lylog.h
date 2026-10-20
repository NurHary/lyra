/*
 * NAME:  lylog.h
 * DESC:  Header To Enable Logging Systems In Lyra
 * NOTE:  Secara keseluruhan untuk logging yang telah di predefine di file
 *        header telah bisa dilakukan secara lengkap
 * TRGT:  Update untuk bisa menerima custom msg dan colours di seluruh files
 * TODO:  1. Merapikan Urutan Headers
 *        2. Menambahkan MSVC Compiler Options
 *        3. Menambahkan Portabilitas untuk versi c manapun dari 99 sampai 23++
 */


// REWRITE IT ALL
#ifndef ___LYLOG_VERSION___
#define ___LYLOG_VERSION___ 0.01

#ifdef NDEBUG
#else


extern char (*GC_MSG)[4];

struct LyLogArena{
  void* base, cur;
  size_t cap, count;
};

//! Ini Namanya bebgini karena saya bingung nama apa yang baik
struct  LyLogLog{
  char* fmt; // disimpan dalam arena juga.
  const char* file
  struct tm* time;
  int32_t msg;
  int32_t line;
};

typedef struct {
  // CONFIG - CONFIG taruh disini
  FILE* files;
  struct LyLogArena* arena; // everyhing will be stored here. even the log log
  struct LyLogLog* loglist;
  size_t amount;
  int32_t write_to_file : 1;
  int32_t log_color: 1;
  int32_t log_msg: 1;
  int32_t 
} LyLogUnit;


//! Adapaun (amnt) disini menjadi acuan jumlah 
struct LyLogArena
lyLog_ArenaInit(size_t amnt);

//! (llamnt) adalah jumlah banyaknya Log Log, dimana iya semua itu
//! disimpan di dalam (arena) itu sendiri
LyLogUnit
lyLog_UnitInit(struct ___LyLogArena* arena, size_t llamnt);

void
lyLog_UnitSetFiles(LyLogUnit* unit, FILE* file);

#define lyLog_PrintLog(unit, msg, fmt, ...) ___lyLog_PrintLog(__FILE__, __LINE__, unit, msg, fmt, __VA_ARGS__)

int
lyLog_ToFiles(LyLogUnit* unit);

void
lyLog_ClearUnit(LyLogUnit* unit)

void
___lyLog_PrintLog(const char* file, size_t line, LyLogUnit* unit, msg, char* fmt, ... );

// // IMPLEMENTATION // //
#if defined(LYLOG_IMPL) && !defined(LYLOG_AIMPL)
#define LYLOG_AIMPL

char (*GC_MSG)[4] = {"INFO", "WARN", "ERROR", "FATAL"};

#endif // defined(LYLOG_IMPL) && !defined(LYLOG_AIMPL)

#endif // NDEBUG

#endif // ___LYLOG_VERSION___

/* EXMPLES:
 * int main(){
 *   struct LyLogArena logarena = lyLog_ArenaInit(1024);
 *   LyLogUnit unit =lyLog_UnitInit(&logarena, 50);
 *   lyLog_PrintLog(&unit, WARN, "KAU JANGAN NONTON BOKEP\n");
 * }
 *
 */


// OLD

/* #if (__STDC_VERSION__ <= 199900l) */
/* #error "lyra library can only be used on std c >= 99" */
/* #endif */

/* #ifndef ___LYLOG_VERSION___ */
/* #define ___LYLOG_VERSION___ "0.1.0" */

/* #include <stdarg.h> */
/* #include <stdint.h> */
/* #include <time.h> */

/* // TODO: Implementasi Custom Log msg pada setiap file */
/* #define RGBTOANSI(r, g, b) "\033[38;2;" #r ";" #g ";" #b "m" */

/* // TO ACCESS DEFAULT MSG AND CLR */
/* #define LYMC_LOGDEFAULT(X)                                                     \ */
/*   X(INFO, RGBTOANSI(0, 0, 255))                                                \ */
/*   X(WARN, RGBTOANSI(0, 255, 0))                                                \ */
/*   X(ERROR, RGBTOANSI(255, 0, 0))                                               \ */
/*   X(FATAL, RGBTOANSI(0, 0, 255)) */

/* // You Can Define Your Own Log Colors Before This, */
/* #define LYM_SETLOG(X) LYMC_LOGDEFAULT(X) */

/* #define LYM_SETLOGENUM(e, c) e, */
/* #define LYM_SETLOGENUMSTR(e, c) #e, */
/* #define LYM_SETLOGCOLOR(e, c) c, */

/* typedef enum { LYM_SETLOG(LYM_SETLOGENUM) } LYLOGE_LOGTYPE; */
/* typedef enum { */
/*   LYLOG_CFG_FILEINFO = 1u << 0, */
/*   LYLOG_CFG_TEXTONLY = 1u << 1, */
/*   LYLOG_CFG_TIME = 1u << 2, */
/*   LYLOG_CFG_COLOUR = 1u << 3 */
/* } ___LYLOG_CONFENUM; */
/* static const char* LYGC_LOGMSG[] = {LYM_SETLOG(LYM_SETLOGENUMSTR)}; */
/* static const char* LYGC_LOGCOLORS[] = {LYM_SETLOG(LYM_SETLOGCOLOR)}; */

/* // DISABLE DEBUG */
/* #ifndef LYNDEBUG */

/* // EXPAND FROM lyutils.h */
/* #ifndef ___LYUTILS_VERSION___ */
/* #if (__STDC_VERSION__ >= 202311l) */
/* #define LYNULL nullptr */
/* #else */
/* #define LYNULL NULL */
/* #endif */

/* #endif */

/* #define LYMC_LOGITALIC "\e[3m" */
/* #define LYM_LOGCOLORFG "\033[38;2;" */
/* #define LYMC_LOGCOLORBG "\033[48;2;" */
/* #define LYMC_LOGFORMATEND "\033[0m" */

/* // // // MACRO PRINT FORMAT // // // */

/* #define lym_printlog(LYLOGE_LOGTYPE, ...)                                      \ */
/*   ___print_log(__FILE__, __LINE__, LYLOGE_LOGTYPE, __VA_ARGS__) */

/* // // // STRUCT // // // */

/* // MAXIMUM CALLBACk FOR LOGGING */
/* #define ___MAXIMUM_CALL 32 */

/* typedef struct { */
/*   va_list ap; */
/*   const char* fmt; */
/*   const char* file; */
/*   struct tm* time; */
/*   void* prtout; */
/*   int32_t line; */
/*   int32_t msge; */
/* } LyLogEvent; */

/* typedef void (*log_LogFn)(LyLogEvent* ev); */
/* typedef void (*log_LockFn)(char lock, void* udata); */

/* typedef struct { */
/*   log_LogFn fn; */
/*   void* udata; */
/*   int32_t msge; */
/* } ___Callback; */

/* static struct { */
/*   void* udata; */
/*   log_LockFn lock; */
/*   int32_t msge; */
/*   uint8_t config; */
/*   // fileinfo : 1; */
/*   // justtxt : 2; */
/*   // enabletime : 4; */
/*   ___Callback callback[___MAXIMUM_CALL]; */
/* } ___L = {.config = (LYLOG_CFG_FILEINFO | LYLOG_CFG_TIME | LYLOG_CFG_COLOUR)}; */

/* /// FORWARD DECLARATION /// */

/* #define lylogConfDisableFileInfo() lylogConfDisable(LYLOG_CFG_FILEINFO) */
/* #define lylogConfDisableTextOnly() lylogConfDisable(LYLOG_CFG_TEXTONLY) */
/* #define lylogConfDisableTime() lylogConfDisable(LYLOG_CFG_TIME) */
/* #define lylogConfDisableColour() lylogConfDisable(LYLOG_CFG_COLOUR) */

/* #define lylogConfEnableFileInfo() lylogConfEnable(LYLOG_CFG_FILEINFO) */
/* #define lylogConfEnableTextOnly() lylogConfEnable(LYLOG_CFG_TEXTONLY) */
/* #define lylogConfEnableTime() lylogConfEnable(LYLOG_CFG_TIME) */
/* #define lylogConfEnableColour() lylogConfEnable(LYLOG_CFG_COLOUR) */

/* void */
/* ___print_log(const char* f, int32_t l, LYLOGE_LOGTYPE t, char* fmt, ...); */

/* /// /// IMPLEMENTATION /// /// */
/* /// */
/* #ifdef LYLOG_IMPL */
/* #include <stdio.h> */
/* /// Fungsi konfigurasi untuk hanya melihat Error bagian mana saja yang */
/* /// muncul */
/* void */
/* lylogConfLSetLevel(int32_t msge) { */
/*   ___L.msge = msge; */
/* } */

/* /// Fungsi konfigurasi untuk menambahkan info file juga pada logging */
/* void */
/* lylogConfEnable(uint8_t b) { */
/*   ___L.config = ___L.config | b; */
/* } */
/* void */
/* lylogConfDisable(uint8_t b) { */
/*   ___L.config = ___L.config & ~b; */
/* } */

/* /// /// /// */

/* static void */
/* ____lock_L(void) { */
/*   if (___L.lock) { */
/*     ___L.lock(1, ___L.udata); */
/*   } */
/* } */

/* static void */
/* ____unlock_L(void) { */
/*   if (___L.lock) { */
/*     ___L.lock(0, ___L.udata); */
/*   } */
/* } */

/* /// Fungsi untuk init event, memberikan nilai waktu, dan output keluar */
/* /// (standardnya stderr) */
/* static void */
/* ___initialize_event(LyLogEvent* ev, void* ptrout) { */
/*   if (!ev->time) { */
/*     time_t t = time(LYNULL); */
/*     ev->time = localtime(&t); */
/*   } */
/*   ev->prtout = ptrout; */
/* } */

/* static void // TO FIX */
/* ____printout_callback(LyLogEvent* ev) { */
/*   char buf[16]; */
/*   strftime(buf, sizeof(buf), "%H:%M:%S", ev->time); */
/*   if (!(___L.config & LYLOG_CFG_TEXTONLY)) { */
/*     if (___L.config & LYLOG_CFG_TIME) */
/*       fprintf(ev->prtout, "|%s ", buf); */
/*     if (___L.config & LYLOG_CFG_FILEINFO) */
/*       fprintf(ev->prtout, "@ %s| ", ev->file); */

/*     fprintf(ev->prtout, "|"); */
/*     if (___L.config & LYLOG_CFG_COLOUR) { */
/*       fprintf(ev->prtout, "%s", LYGC_LOGCOLORS[ev->msge]); */
/*     } */
/*     fprintf(ev->prtout, "%s", LYGC_LOGMSG[ev->msge]); */

/*     if (___L.config & LYLOG_CFG_COLOUR) { */
/*       fprintf(ev->prtout, LYMC_LOGFORMATEND); */
/*     } */
/*     fprintf(ev->prtout, "| "); */
/*   } */
/*   vfprintf(ev->prtout, ev->fmt, ev->ap); */
/*   fprintf(ev->prtout, "\n"); */
/*   fflush(ev->prtout); */
/* } */

/* void */
/* ___print_log(const char* f, int32_t l, LYLOGE_LOGTYPE t, char* fmt, ...) { */
/*   // fprintf(stderr, "%s %s JAJAL %s" LYMC_LOGFORMATEND, LYGC_LOGMSG[t], */
/*   //         LYGC_LOGCOLORS[t], m); */
/*   LyLogEvent ev = { */
/*       .fmt = fmt, */
/*       .file = f, */
/*       .line = l, */
/*       .msge = t, */
/*   }; */
/*   ____lock_L(); // LOCK */

/*   if (t >= ___L.msge) { */
/*     ___initialize_event(&ev, stderr); */
/*     va_start(ev.ap, fmt); */
/*     ____printout_callback(&ev); */
/*     va_end(ev.ap); */
/*   } */

/*   for (int i = 0; i < ___MAXIMUM_CALL && ___L.callback[i].fn; i++) { */
/*     ___Callback* cb = &___L.callback[i]; */
/*     if (t >= cb->msge) { */
/*       ___initialize_event(&ev, cb->udata); */
/*       va_start(ev.ap, fmt); */
/*       ____printout_callback(&ev); */
/*       va_end(ev.ap); */
/*     } */
/*   } */

/*   ____unlock_L(); */
/* } */

/* #endif */

/* #else */
/* #define lym_printlog(LYLOGE_LOGTYPE, ...) */
/* #define lylogConfToggleFileInfo() */
/* #define lylogConfToggleTxtOnly() */
/* #define lylogConfLSetLevel(msge) */
/* #endif */

/* #endif */
