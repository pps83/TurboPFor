#if !(defined(__i386__) || defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86))
#error only x86/x64 builds are supported
#endif

#define __STDC_WANT_IEC_60559_TYPES_EXT__

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

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <malloc.h>
#if defined(_MSC_VER)
#include <intrin.h>
#endif
#if defined(__i386__) || defined(__x86_64__)
#include <x86intrin.h>
#endif

#if defined(__GNUC__) || defined(__clang__)
#ifdef __clang__
#pragma clang attribute push (__attribute__((target("bmi2,avx2"))),apply_to = function)
#pragma clang diagnostic push
#else
#pragma GCC push_options
#pragma GCC target("bmi2,avx2")
#endif
#pragma GCC diagnostic ignored "-Wmacro-redefined"
#pragma GCC diagnostic ignored "-Wmissing-braces"
#pragma GCC diagnostic ignored "-Wparentheses-equality"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wtautological-constant-out-of-range-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#elif defined(_MSC_VER)
#pragma warning(disable: 4018 4100 4101 4127 4146 4189 4244 4245 4267 4319 4333 4389 4456 4457 4505 4701 4702) // Ignore /W4 warnings
#pragma warning(disable: 4242 4365 4388 4514 4548 4555 4668 4710 4711 4820 4883 5045 5219 5245)                // Ignore /Wall warnings
#endif

#include "include/ic.h"

#define TURBOPFOR_DAC

#include "lib/bitpack.c"
#include "lib/bitunpack.c"
#include "lib/bitutil.c"
#include "lib/transpose.c"
#include "lib/vp4c.c"
#include "lib/vp4d.c"

#ifdef __clang__
#pragma clang attribute pop
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC pop_options
#endif
