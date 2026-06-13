// Name:  linal.h
// Desc:  Linear Algebra Library for Lyra, giving vec2->4 mat2->x with float and
//        int dtypes
// Auth:  KillingWhales (Nur Hary)
// Stat:  On Development
// Targ:  Complete and SIMD

#ifndef ___LY_LINAL_VERSION___
#define ___LY_LINAL_VERSION___ "0.0.1"
#include "../lyutils.h"

#ifdef LYMS_DISABLE_SIMD // TODO
#define float floatin
#endif

// DECLARATION //

typedef struct {
  float x;
  float y;
} v2;
typedef struct {
  float x;
  float y;
  float z;
} v3;
typedef struct {
  float x;
  float y;
  float z;
  float a;
} v4;

typedef struct {
  int32_t x;
  int32_t y;
} v2i;
typedef struct {
  int32_t x;
  int32_t y;
  int32_t z;
} v3i;
typedef struct {
  int32_t x;
  int32_t y;
  int32_t z;
  int32_t a;
} v4i;

typedef v4 quaternion; // quaternion

// IMPLEMENTATION //

#ifdef ___LY_LINAL_IMP___
#endif

#endif
