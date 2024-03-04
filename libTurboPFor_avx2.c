#if !(defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64))
#error only x86/x64 builds are supported
#endif

#if defined(__clang__)
#define __RTMINTRIN_H // workaround for https://github.com/llvm/llvm-project/issues/95133
#pragma clang diagnostic push
#pragma clang attribute push (__attribute__((target("bmi,bmi2,lzcnt,avx2"))),apply_to = function)
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC push_options
#pragma GCC target("bmi,bmi2,lzcnt,avx2")
#endif

#define __STDC_WANT_IEC_60559_TYPES_EXT__

#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
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
#pragma GCC diagnostic ignored "-Wunknown-warning-option"
#pragma GCC diagnostic ignored "-Wkeyword-macro"
#pragma GCC diagnostic ignored "-Wtautological-constant-out-of-range-compare"
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
#pragma GCC diagnostic ignored "-Wextra-semi"
#pragma GCC diagnostic ignored "-Wstatic-in-inline"
#pragma GCC diagnostic ignored "-Wc23-extensions"
#else
#pragma GCC diagnostic ignored "-Wnarrowing"
#pragma GCC diagnostic ignored "-Woverflow"
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif
#ifdef __cplusplus
#pragma GCC diagnostic ignored "-Wregister"
#endif
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#pragma GCC diagnostic ignored "-Wsequence-point"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#elif defined(_MSC_VER)
#pragma warning(disable: 4018 4100 4101 4127 4146 4189 4242 4244 4245 4267 4319 4333 4365 4388 4389 4456 4457 4464 4514 4548 4555 4701 4710 4711 4820 5033 5045 5046 5219 5245)
#endif

#include "include/ic.h"

#define TURBOPFOR_DAC

#include "lib/bitpack.c"
#include "lib/bitunpack.c"
#include "lib/bitutil.c"
#include "lib/transpose.c"
#include "lib/vp4c.c"
#include "lib/vp4d.c"

#include "lib/bic.c"
#include "lib/eliasfano.c"
#include "lib/fp.c"
#include "lib/transpose_.c"
#include "lib/v8.c"
#include "lib/vsimple.c"

// #define VB_MAX
#include "lib/v8pack.c"
#include "lib/vint.c"

// trlec.c and trled.c include trle_.h which redefines some macro from vlcbyte.h
#include "lib/trlec.c"
#include "lib/trled.c"

// vbit.c and iccodec.c include bitiobe.h which redefines some macro from bitutil_.h
#include "lib/iccodec.c"
#include "lib/vbit.c"

#ifdef __clang__
#pragma clang attribute pop
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC pop_options
#pragma GCC diagnostic pop
#endif
