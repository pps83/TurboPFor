#if !defined(__i386__) && !defined(__x86_64__) && !defined(_M_X64) && !defined(_M_IX86)
#error only x86/x64 builds are supported
#endif

#if defined(__GNUC__) || defined(__clang__)
#ifdef __clang__
#pragma clang attribute push (__attribute__((target("bmi2,avx2"))),apply_to = function)
#pragma clang diagnostic push
#else
#pragma GCC push_options
#pragma GCC target("bmi2,avx2")
#endif

#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wuninitialized"

#ifdef __clang__
#pragma GCC diagnostic ignored "-Wconstant-conversion"
#pragma GCC diagnostic ignored "-Wtautological-constant-out-of-range-compare"
#pragma GCC diagnostic ignored "-Wcompare-distinct-pointer-types"
#else
#pragma GCC diagnostic ignored "-Wmultistatement-macros"
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wsequence-point"
#endif

#elif defined(_MSC_VER)
#pragma warning(disable: 4018 4100 4101 4127 4133 4146 4189 4244 4245 4267 4333 4389 4456 4554 4701 4706)
// #pragma warning(disable: 4242 4668 4555 4548 5045 4820 4711 4710) // /Wall
#endif

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
#include <intrin.h>
#include <immintrin.h>

#include "lib/include/conf.h"
#include "lib/include/vint_in.h"
#include "lib/include/bitpack.h"
#include "lib/include/vp4.h"
#include "lib/include/bitutil_in.h"  // has __AVX2__ checks
#include "lib/include/bitpack_dac.h" // has __AVX2__ checks (bzhi)


#include "lib/bitutil.c"
#include "lib/fp.c" // includes fp_tpl.h which has __AVX2__ checks
#include "lib/trlec.c"
#include "lib/trled.c"
#include "lib/v8.c"
#include "lib/vint.c"
#include "lib/vsimple.c"

#include "lib/bitpack.c"
#include "lib/bitunpack.c"
#include "lib/vp4c.c"
#include "lib/vp4d.c"
#include "lib/transpose.c"

#define AVX2_ON
#include "lib/bitpack.c"
#include "lib/bitunpack.c"
#include "lib/vp4c.c"
#include "lib/vp4d.c"
#include "lib/transpose.c"
#undef AVX2_ON

#define SSE2_ON
#undef __AVX2__
#include "lib/bitpack.c"
#include "lib/bitunpack.c"
#include "lib/vp4c.c"
#include "lib/vp4d.c"
#include "lib/transpose.c"
#undef SSE2_ON

#ifdef __clang__
#pragma clang attribute pop
#pragma clang diagnostic pop
#else
#pragma GCC pop_options
#endif
