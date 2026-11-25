// NAME:  con.h
// DESC:  Conditional utilities for lyra development

// RENAMING FOR EASIER CALLING 

#ifdef _WIN32
#define LYOS_WINDOWS32
#endif // _WIN32

#ifdef _WIN64
#define LYOS_WINDOWS64
#endif // _WIN64

#ifdef __linux
#define LYOS_LINUX
#endif // __linux__

#ifdef __APPLE__
#define LYOS_APPLE
#endif

#ifdef __unix
#define LYOS_UNIX
#endif // __unix

#ifdef __posix
#define LYOS_POSIX
#endif // __posix


// #define LYAPI

#ifdef LYCON_IMPL_
#include <stdio.h>
void
    lycon_testos(){
    #ifdef LYOS_WINDOWS32
    fprintf(stderr, "CON WINDOW32 IS ON\n");
    #endif // LYOS_WINDOWS32
    
    #ifdef LYOS_WINDOWS64
    fprintf(stderr, "CON WINDOW64 IS ON\n");
    #endif // LYOS_WINDOWS64
    
    #ifdef LYOS_LINUX
    fprintf(stderr, "CON LINUX IS ON\n");
    #endif // LYOS_LINUX
    
    #ifdef LYOS_APPLE
    fprintf(stderr, "CON APPLE IS ON\n");
    #endif // LYOS_APPLE
    
    #ifdef LYOS_UNIX
    fprintf(stderr, "CON UNIX IS ON\n");
    #endif // LYOS_UNIX
    
    #ifdef LYOS_POSIX
    fprintf(stderr, "CON POSIX IS ON\n");
    #endif // LYOS_POSIX
}


#endif // LYCON_IMPL_