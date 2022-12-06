#ifdef _MSC_VER
#pragma warning(push, 1)
#pragma warning(disable: 4838)
#endif

#ifdef __clang__
#pragma clang attribute push (__attribute__((target("bmi2,avx2"))),apply_to = function)
#endif

#ifdef _MSC_VER
#define __SSE__ 1
#define __SSE2__ 1
#define __SSE3__ 1
#define __SSSE3__ 1
#define __SSE4_1__ 1
#define __SSE4_2__ 1
#define __BMI__ 1
#define __BMI2__ 1
#define __AVX__ 1
#define __AVX2__ 1
#endif

#include "FastPFor/src/bitpacking.cpp"
#include "FastPFor/src/bitpackingaligned.cpp"
#include "FastPFor/src/bitpackingunaligned.cpp"
#include "FastPFor/src/horizontalbitpacking.cpp"
#include "FastPFor/src/simdbitpacking.cpp"
#include "FastPFor/src/simdunalignedbitpacking.cpp"
extern "C" {
#include "FastPFor/src/streamvbyte.c"
//#include "FastPFor/src/varintdecode.c"
}

#ifdef __clang__
#pragma clang attribute pop
#endif
