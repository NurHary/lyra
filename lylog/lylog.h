// NAME   : lylog.h
// PURPOSE: Header For lylog, contains 
// 

#ifndef LYLOG_VERSION
#define LYLOG_VERSION "0.0.1"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lyutils.h"

#define RGBTOANSI(r, g, b) LYM_LOGCOLORFG #r ";" #g ";" #b "m"

// TO ACCESS DEFAULT MSG AND CLR
#define LYMC_LOGDEFAULT(X) \
  X(ERROR, RGBTOANSI(255, 0, 0))\
  X(WARN, RGBTOANSI(0, 255, 0))\
  X(INFO, RGBTOANSI(0, 0, 255))\
  X(FATAL, RGBTOANSI(0, 0, 255))\


// You Can Define Your Own Log Colors Before This,
#ifndef LYM_SETLOG
#define LYM_SETLOG(X) LYMC_LOGDEFAULT(X)
#endif

#define LYM_SETLOGENUM(e, c) e,
#define LYM_SETLOGENUMSTR(e, c) #e,
#define LYM_SETLOGCOLOR(e, c) c,

// // // MACRO PRINT FORMAT // // //


// void __attribute__((constructor)) ___convert_hex_colors_to_ansi();


#define lym_printlog(LYE_LOGTYPE, ...) ___print_log(__FILE__, __LINE__, LYE_LOGTYPE, __VA_ARGS__)

// // // STRUCT // // //
typedef enum {
  LYM_SETLOG(LYM_SETLOGENUM)
    LENGTH
} LYE_LOGTYPE;


// Function To Print Logs systems to the terminal
void ___print_log(const char* f, i32 l, LYE_LOGTYPE t, char* m, ...);

// Function to write logs to a files
void ly_writelog(LYE_LOGTYPE type, char* msg, FILE* file);
//
// Function To Print Logs systems to the terminal and
// to write the logs to a files
void ly_printwritelog(LYE_LOGTYPE type, char* msg, FILE* file);
  // const char *colors[] = DEFAULTLOGCOLORS;



#endif

