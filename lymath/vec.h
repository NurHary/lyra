// Name:  vec.h
// Desc:  Vector single header library written by KillingWhales
// Auth:  KillingWhales (Nur Hary)
// Stat:  On Development
// Targ:  Complete and SIMD



#ifndef ___LYVEC_VERSION___
#define ___LYVEC_VERSION___ 0.01f
#include <math.h>
#include <stdint.h>
#include "../lyutils.h"

#ifdef LYMS_DISABLE_SIMD // TODO
#endif

/* #if !(defined(__STDC__) && __STDC__ == 1  && defined(__STDC_VERSION__) && __STDC_VERSION >= 110301L)
#error "linal membutuhkan seminimalnya C11"
#endif */

// SHORT NAMES
#ifndef LY_NO_SHORT_NAMES
#define vec2 lyvec2
#define v2add ly_v2add
#define v2sub ly_v2sub
#define v2padd ly_v2padd
#define v2psub ly_v2psub

#define v2mul ly_v2mul
#define v2div ly_v2div
#define v2pmul ly_v2pmul
#define v2pdiv ly_v2pdiv
#define v2hmul ly_v2hmul
#define v2hdiv ly_v2hdiv
#define v2phmul ly_v2phmul
#define v2phdiv ly_v2phdiv
#endif  // LY_NO_SHORT_NAMES

// Data Declarations //

typedef union {
  struct {
    float x, y;
  };
  float e[2];
} v2;

typedef union {
  struct {
    float x, y, z;
  };
  float e[3];
} v3;

typedef union {
  struct {
    float x, y, z, a;
  };
  float e[4];
} v4;

typedef union {
  struct {
    int32_t x, y;
  };
  int32_t e[2];
} v2i;

typedef union {
  struct {
    int32_t x, y, z;
  };
  int32_t e[3];
} v3i;

typedef union {
  struct{
    int32_t x, y, z, a;
  };
  int32_t e[4];
} v4i;

typedef v2i v2b;
typedef v3i v3b;
typedef v4i v4b;

typedef v4 quaternion; // quaternion

// Operations Declarations //
// // Standard Operations V2 // //

// Init new vector
v2
lyvec2(float x, float y);

v2
ly_v2add(v2 lhs, v2 rhs);

v2
ly_v2sub(v2 lhs, v2 rhs);

void
ly_v2padd(float* lhs, v2 rhs);

void
ly_v2psub(float* lhs, v2 rhs);

v2
ly_v2mul(v2 lhs, float val);

v2
ly_v2div(v2 lhs, float val);

void
ly_v2pmul(float* lhs, float val);

void
ly_v2pdiv(float* lhs, float val);

// Hadamard Operations //

// Hadamard Multiplication
v2
ly_v2hmul(float* lhs, v2 rhs);

v2
ly_v2hdiv(float* lhs, v2 rhs);

void
ly_v2phmul(float* lhs, v2 rhs);

void
ly_v2phdiv(float* lhs, v2 rhs);

float
ly_v2sqmagn(float* lhs);

v2
ly_v2norm(float* lhs);

void
ly_v2pnorm(float* lhs);

float
ly_v2dot(v2 lhs, v2 rhs);

float
ly_v2dist(v2 lhs, v2 rhs);

v2
ly_v2lerp(v2 lhs, v2 rhs, float amt);



// IMPLEMENTATION //
#if defined(LYVEC_IMPL) && !defined(LYVEC_AIMPl)
#define LYVEC_AIMPL // Already Implemented

// // Standard Operation V2 // //
v2
lyvec2(float x, float y){
  return (v2) {x, y};
}

v2
ly_v2add(v2 lhs, v2 rhs){
  return (v2){.x= rhs.x + lhs.x, .y= rhs.y + lhs.y};
}

v2
ly_v2sub(v2 lhs, v2 rhs){
  return (v2){.x= rhs.x - lhs.x, .y= rhs.y - lhs.y};
}

void
ly_v2padd(float* lhs, v2 rhs){
  for (int i = 0; i < 2; ++i){
    lhs[i] += rhs.e[i];
  }
}

void
ly_v2psub(float* lhs, v2 rhs){
  for (int i = 0; i < 2; ++i){
    lhs[i] -= rhs.e[i];
  }
}

v2
ly_v2mul(v2 lhs, float val){
  return (v2){.x=lhs.x*val, .y=lhs.y*val};
}

v2
ly_v2div(v2 lhs, float val){
  return (v2){.x=lhs.x/val, .y=lhs.y/val};
}

void
ly_v2pmul(float* lhs, float val){
  for (int i = 0; i < 2; ++i){
    lhs[i] *= val;
  }
}

void
ly_v2pdiv(float* lhs, float val){
  for (int i = 0; i < 2; ++i){
    lhs[i] /= val;
  }
}

// Hadamard Operation

v2
ly_v2hmul(float* lhs, v2 rhs){
  v2 ret = {0.0f, 0.0f};
  for (int i = 0; i < 2; ++i){
    ret.e[i] = lhs[i] * rhs.e[i];
  }
  return ret;
}

v2
ly_v2hdiv(float* lhs, v2 rhs){
  v2 ret = {0.0f, 0.0f};
  for (int i = 0; i < 2; ++i){
    ret.e[i] = lhs[i] / rhs.e[i];
  }
  return ret;
}

void
ly_v2phmul(float* lhs, v2 rhs){
  for (int i = 0; i < 2; ++i){
    lhs[i] *= rhs.e[i];
  }
}

void
ly_v2phdiv(float* lhs, v2 rhs){
  for (int i = 0; i < 2; ++i){
    lhs[i] /= rhs.e[i];
  }
}

float
ly_v2sqmagn(float* lhs){
  return lhs[0] * lhs[0] + lhs[1] * lhs[1];
}

v2
ly_v2norm(float* lhs){
  float sqmagn = sqrtf(ly_v2sqmagn(lhs));
  v2 ret = ly_v2div(lyvec2(lhs[0], lhs[1]), sqmagn);
  return ret;
}

void
ly_v2pnorm(float* lhs){
  float sqmagn = sqrtf(ly_v2sqmagn(lhs));
  ly_v2pdiv(lhs, sqmagn);
}


float
ly_v2dist(v2 lhs, v2 rhs){
  v2 sub = ly_v2sub(lhs, rhs);
  float mgn =  sqrtf(ly_v2sqmagn(sub.e));
  return (mgn);
}

v2
ly_v2lerp(v2 lhs, v2 rhs, float amt);

#endif // defined(LYVEC_IMPL) && !defined(LYVEC_AIMPl)

#endif //___LYVEC_VERSION___
