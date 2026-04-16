/*
 * Name: lylog.c
 *
 * Purpose: Header For lylog.c used to logging
 *
 * Notes:
 *
 * Error/ Warn:
 * -------------------------------------
 * |   MSG  |   Types   |   Indicator  |
 * -------------------------------------
 * |
 * |
 *
 */






#include "../lylog.h"
#include "../lyutils.h"
#include <stdio.h>
#include <stdlib.h>


// ANSI ITALIC
#define LYMC_LOGITALIC "\e[3m"

// TODO
// ANSI COLOR FOREGROUND / TEXT
#define LYM_LOGCOLORFG "\033[38;2;"
// ANSI COLOR BACKGROUND
#define LYMC_LOGCOLORBG "\033[48;2;"

// ANSI END FORMAT
#define LYMC_LOGFORMATEND "\033[0m"

const char* LYGC_LOGMSG[] = {
  LYM_SETLOG(LYM_SETLOGENUMSTR)
};

const char* LYGC_LOGCOLORS[] = {
  LYM_SETLOG(LYM_SETLOGCOLOR)
};

#define lylog_printlog(t, ...)


void ___print_log(const char* f, i32 l, LYE_LOGTYPE t, char* m, ...){
  fprintf(stderr, "%s %s JAJAL %s" LYMC_LOGFORMATEND , LYGC_LOGMSG[t], LYGC_LOGCOLORS[t], m);

}
