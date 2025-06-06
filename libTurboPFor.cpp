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

#define IC_NO_EXTERN_C 1
#define TURBOPFOR_DAC
//#define register

namespace
{
namespace ic
{
#define __AVX2__ 1
#include "lib/bitpack.c"
#include "lib/bitunpack.c"
#include "lib/bitutil.c"
#include "lib/transpose.c"
#include "lib/vp4c.c"
#include "lib/vp4d.c"

#undef __AVX2__
#include "lib/bitpack.c"
#include "lib/bitunpack.c"
#include "lib/bitutil.c"
#include "lib/transpose.c"
#include "lib/vp4c.c"
#include "lib/vp4d.c"

#define __AVX2__ 1
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
}
}

extern "C"
{
size_t p4nenc256v32(uint32_t* in, size_t n, uint8_t* out)
{
    return ic::p4nenc256v32(in, n, out);
}
size_t p4ndec256v32(const uint8_t* in, size_t n, uint32_t* out)
{
    return ic::p4ndec256v32(in, n, out);
}
uint32_t bitzenc32(uint32_t* in, unsigned n, uint32_t* out, uint32_t start, uint32_t mindelta)
{
    return ic::bitzenc32(in, n, out, start, mindelta);
}
void bitzdec32(uint32_t* in, unsigned n, uint32_t start)
{
    return ic::bitzdec32(in, n, start);
}
unsigned char* vsenc32(unsigned* __restrict in, size_t n, unsigned char* __restrict out)
{
    return ic::vsenc32(in, n, out);
}
unsigned char* vsdec32(unsigned char* __restrict in, size_t n, unsigned* __restrict out)
{
    return ic::vsdec32(in, n, out);
}
size_t p4nzenc32(uint32_t* __restrict in, size_t n, unsigned char* __restrict out)
{
    return ic::p4nzenc32(in, n, out);
}
size_t p4nzdec32(const unsigned char* __restrict in, size_t n, uint32_t* __restrict out)
{
    return ic::p4nzdec32(in, n, out);
}
size_t p4nzenc256v32(uint32_t* __restrict in, size_t n, unsigned char* __restrict out)
{
    return ic::p4nzenc256v32(in, n, out);
}
size_t p4nzdec256v32(const unsigned char* __restrict in, size_t n, uint32_t* __restrict out)
{
    return ic::p4nzdec256v32(in, n, out);
}
size_t bitnxpack128v32(uint32_t* __restrict in, size_t n, unsigned char* __restrict out)
{
    return ic::bitnxpack128v32(in, n, out);
}
size_t bitnxunpack128v32(const unsigned char* __restrict in, size_t n, uint32_t* __restrict out)
{
    return ic::bitnxunpack128v32(in, n, out);
}
size_t bitnzpack128v32(uint32_t* __restrict in, size_t n, unsigned char* __restrict out)
{
    return ic::bitnzpack128v32(in, n, out);
}
size_t bitnzunpack128v32(const unsigned char* __restrict in, size_t n, uint32_t* __restrict out)
{
    return ic::bitnzunpack128v32(in, n, out);
}
size_t v8nxenc128v32(uint32_t* __restrict in, size_t n, unsigned char* __restrict out)
{
    return ic::v8nxenc128v32(in, n, out);
}
size_t v8nxdec128v32(unsigned char* __restrict in, size_t n, uint32_t* __restrict out)
{
    return ic::v8nxdec128v32(in, n, out);
}
size_t v8nzenc128v32(uint32_t* __restrict in, size_t n, unsigned char* __restrict out)
{
    return ic::v8nzenc128v32(in, n, out);
}
size_t v8nzdec128v32(unsigned char* __restrict in, size_t n, uint32_t* __restrict out)
{
    return ic::v8nzdec128v32(in, n, out);
}
size_t v8nzenc256v32(uint32_t* __restrict in, size_t n, unsigned char* __restrict out)
{
    return ic::v8nzenc256v32(in, n, out);
}
size_t v8nzdec256v32(unsigned char* __restrict in, size_t n, uint32_t* __restrict out)
{
    return ic::v8nzdec256v32(in, n, out);
}
size_t vlccomp32x(const unsigned char* in, size_t inlen, unsigned char* out, size_t outlen, unsigned char* tmp, ic::codec_func enc)
{
    return ic::vlccomp32x(in, inlen, out, outlen, tmp, enc);
}
size_t vlcdecomp32x(const unsigned char* in, size_t inlen, unsigned char* out, size_t outlen, unsigned char* tmp, ic::codec_func dec)
{
    return ic::vlcdecomp32x(in, inlen, out, outlen, tmp, dec);
}
size_t vhicomp32x(const unsigned char* in, size_t inlen, unsigned char* out, size_t outlen, unsigned char* tmp, ic::codec_func enc)
{
    return ic::vhicomp32x(in, inlen, out, outlen, tmp, enc);
}
size_t vhidecomp32x(const unsigned char* in, size_t inlen, unsigned char* out, size_t outlen, unsigned char* tmp, ic::codec_func dec)
{
    return ic::vhidecomp32x(in, inlen, out, outlen, tmp, dec);
}
}


#ifdef __clang__
#pragma clang attribute pop
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC pop_options
#pragma GCC diagnostic pop
#endif
