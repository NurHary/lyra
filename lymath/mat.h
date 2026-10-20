// Name:  mat.h
// Desc:  Matrix library written by KillingWhales
// Auth:  KillingWhales (Nur Hary)
// Stat:  On Development
// Targ:  Complete and SIMD

#ifndef __LYMAT_VERSION__
#define __LYMAT_VERSION__ 0.01

#include <stddef.h>

#include "vec.h"


typedef struct {
  v2 data[2];
  size_t amount;
}mt2;

typedef struct {
  v3 data[3];
  size_t amount;
}mt3;

typedef struct {
  v4 data[4];
  size_t amount;
}mt4;




#endif // __LYMAT_VERSION__
