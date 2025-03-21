/**
    Copyright (C) powturbo 2013-2023
    SPDX-License-Identifier: GPL v2 License

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    - homepage : https://sites.google.com/site/powturbo/
    - github   : https://github.com/powturbo
    - twitter  : https://twitter.com/powturbo
    - email    : powturbo [_AT_] gmail [_DOT_] com
**/
//   Nibble/Byte transpose
#ifndef ESIZE //---------------------------------- Functions -----------------------------------------------------------------
#include <string.h>
#include "include_/conf.h"
#include "include_/transpose.h"

#if defined(__SSSE3__) && defined(__powerpc64__)
#define __SSE__   1
#define __SSE2__  1
#define __SSE3__  1
#define NO_WARN_X86_INTRINSICS 1
#endif
#if defined(__ARM_NEON)
#include <arm_neon.h>
#include "include_/sse_neon.h"
#endif

#if defined(_MSC_VER) && !defined(__clang__)
#pragma warning(disable: 4005)
#endif

#include "include_/bitutil_.h"

#undef PREFETCH
  #ifdef __ARM_NEON
#define PREFETCH(_ip_,_rw_)
  #else
#define PREFETCH(_ip_,_rw_) __builtin_prefetch(_ip_,_rw_)
  #endif

#define powof2(n)        !((n)&((n)-1))

#undef TPENC
#undef TPDEC

//-- 24 bits / 3 bytes (scalar only) ----------------------
#define ESIZE 3
#define STRIDE ESIZE

#define TPENC            tpenc
#define TPDEC            tpdec
#include "transpose.c"
#undef TPENC
#undef TPDEC

#define TPENC            tpzenc
#define TPDEC            tpzdec
#include "transpose.c"
#undef TPENC
#undef TPDEC

#define TPENC            tpxenc
#define TPDEC            tpxdec
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef ESIZE

//-- 128 bits / 16 bytes (scalar only) --------------------
#define ESIZE 16
#define STRIDE ESIZE

#define TPENC            tpenc
#define TPDEC            tpdec
#include "transpose.c"
#undef TPENC
#undef TPDEC

#define TPENC            tpzenc
#define TPDEC            tpzdec
#include "transpose.c"
#undef TPENC
#undef TPDEC

#define TPENC            tpxenc
#define TPDEC            tpxdec
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VEINI128
#undef VDINI128
#undef VEINI256
#undef VDINI256
#undef VE128
#undef VD128
#undef VE256
#undef VD256

#undef ESIZE
#undef ST128
//-----------------------------------------------------------
#define LD128(_ip_)      _mm_loadu_si128( (__m128i *)(_ip_))
#define ST128(_op_,_v_)  _mm_storeu_si128((__m128i *)(_op_),_v_)

#define LD256(ip)        _mm256_loadu_si256(ip)
#define ST256(op,v)      _mm256_storeu_si256(op,v)
//---------------------------------------------- 16 bits -------------------------------------------------
#define ESIZE  2
#define USIZE 16

//-- byte ------------------------
#define STRIDE           ESIZE
#define TPENC            tpenc
#define TPDEC            tpdec
#define TPENC128V        tpenc128v
#define TPDEC128V        tpdec128v
#define TPENC256V        tpenc256v
#define TPDEC256V        tpdec256v

#define VEINI128
#define VEINI256
#define VE128(_v_,_sv_)
#define VE256(_v_,_sv_)
#define VDINI128
#define VDINI256
#define VD128(_ov_,_sv_)
#define VD256(_ov_,_sv_)
#include "transpose.c"
#undef  TPENC256V
#undef  TPDEC256V
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef VEINI128
#undef VDINI128
#undef VE128
#undef VD128
//--------------
#define ISDELTA
//-- zigzag
#define TPENC            tpzenc
#define TPDEC            tpzdec
#define TPENC128V        tpzenc128v
#define TPDEC128V        tpzdec128v

#define VEINI128         __m128i sv = _mm_setzero_si128()
#define VE128(_iv_,_sv_) { __m128i _tv = mm_delta_epi16(_iv_,_sv_); _sv_ = _iv_; _iv_ = mm_zzage_epi16(_tv); }
#define VDINI128         __m128i sv = _mm_setzero_si128()
#define VD128(_v_,_sv_)  _v_ = mm_zzagd_epi16( _v_); _sv_ = mm_scan_epi16(_v_,_sv_); _v_ = _sv_
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef VE128
#undef VD128

//-- xor
#define TPENC            tpxenc
#define TPDEC            tpxdec
#define TPENC128V        tpxenc128v
#define TPDEC128V        tpxdec128v

#define VEINI128         __m128i sv = _mm_setzero_si128()
#define VE128(_iv_,_sv_) { __m128i _tv = mm_xore_epi16(_iv_,_sv_); _sv_ = _iv_; _iv_ = _tv; }
#define VDINI128         __m128i sv = _mm_setzero_si128()
#define VD128(_v_,_sv_)  _sv_ = _v_ = mm_xord_epi16(_v_,_sv_)
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef VEINI128
#undef VDINI128
#undef VE128
#undef VD128
#undef ISDELTA
#undef STRIDE

//----------- nibble ---------
#define STRIDE 4
#define TPENC            tp4enc
#define TPDEC            tp4dec
#define TPENC128V        tp4enc128v
#define TPDEC128V        tp4dec128v
#define TPENC256V        tp4enc256v
#define TPDEC256V        tp4dec256v

#define VEINI128
#define VEINI256
#define VE128(_v_,_sv_)
#define VE256(_v_,_sv_)
#define VDINI128
#define VDINI256
#define VD128(_ov_,_sv_)
#define VD256(_ov_,_sv_)

#include "transpose.c"
#undef  TPENC256V
#undef  TPDEC256V
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef VEINI128
#undef VDINI128
#undef VE128
#undef VD128

#define ISDELTA
//-- zigzag
#define TPENC            tp4zenc
#define TPDEC            tp4zdec
#define TPENC128V        tp4zenc128v
#define TPDEC128V        tp4zdec128v

#define VEINI128         __m128i sv = _mm_setzero_si128()
#define VE128(_iv_,_sv_) { __m128i _tv = mm_delta_epi16(_iv_,_sv_); _sv_ = _iv_; _iv_ = mm_zzage_epi16(_tv); }
#define VDINI128         __m128i sv = _mm_setzero_si128()
#define VD128(_v_,_sv_)  _v_ = mm_zzagd_epi16( _v_); _sv_ = mm_scan_epi16(_v_,_sv_); _v_ = _sv_
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef VE128
#undef VD128

//-- xor
#define TPENC            tp4xenc
#define TPDEC            tp4xdec
#define TPENC128V        tp4xenc128v
#define TPDEC128V        tp4xdec128v

#define VEINI128         __m128i sv = _mm_setzero_si128()
#define VE128(_iv_,_sv_) { __m128i _tv = mm_xore_epi16(_iv_,_sv_); _sv_ = _iv_; _iv_ = _tv; }
#define VDINI128         __m128i sv = _mm_setzero_si128()
#define VD128(_v_,_sv_)  _sv_ = _v_ = mm_xord_epi16(_v_,_sv_)
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef VEINI128
#undef VDINI128
#undef VE128
#undef VD128
#undef ISDELTA
#undef STRIDE
#undef ESIZE
#undef USIZE

//------------------------------------------------ 32 bits ----------------------------------------------------------
#define ESIZE 4
#define USIZE 32

#define STRIDE ESIZE
//----------------- byte ------------
#define TPENC            tpenc
#define TPDEC            tpdec
#define TPENC128V        tpenc128v
#define TPDEC128V        tpdec128v
#define TPENC256V        tpenc256v
#define TPDEC256V        tpdec256v

#define VEINI128
#define VEINI256
#define VE128(_v_,_sv_)
#define VE256(_v_,_sv_)
#define VDINI128
#define VDINI256
#define VD128(_ov_,_sv_)
#define VD256(_ov_,_sv_)
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VEINI128
#undef VDINI128
#undef VEINI256
#undef VDINI256
#undef VE128
#undef VD128
#undef VE256
#undef VD256

//---------------------------------
#define ISDELTA
//-- zigzag
#define TPENC            tpzenc
#define TPDEC            tpzdec
#define TPENC128V        tpzenc128v
#define TPDEC128V        tpzdec128v
#define TPENC256V        tpzenc256v
#define TPDEC256V        tpzdec256v

#define VEINI128         __m128i sv = _mm_setzero_si128()
#define VE128(_iv_,_sv_) { __m128i _tv = mm_delta_epi32(_iv_,_sv_); _sv_ = _iv_; _iv_ = mm_zzage_epi32(_tv); }
#define VEINI256         __m256i sv = _mm256_setzero_si256()
#define VE256(_iv_,_sv_) { __m256i _tv = mm256_delta_epi32(_iv_,_sv_); _sv_ = _iv_; _iv_ = mm256_zzage_epi32(_tv); }
#define VDINI128         __m128i sv = _mm_setzero_si128()
#define VD128(_v_,_sv_)  _v_ = mm_zzagd_epi32( _v_); _sv_ = mm_scan_epi32(_v_,_sv_); _v_ = _sv_
#define VDINI256         __m256i sv = _mm256_setzero_si256()
#define VD256(_v_,_sv_)  _v_ = mm256_zzagd_epi32(_v_); _sv_ = mm256_scan_epi32(_v_,_sv_); _v_ = _sv_
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VE128
#undef VD128
#undef VE256
#undef VD256

//-- xor
#define TPENC            tpxenc
#define TPDEC            tpxdec
#define TPENC128V        tpxenc128v
#define TPDEC128V        tpxdec128v
#define TPENC256V        tpxenc256v
#define TPDEC256V        tpxdec256v

#define VEINI128         __m128i sv = _mm_setzero_si128()
#define VE128(_iv_,_sv_) { __m128i _tv =    mm_xore_epi32(_iv_,_sv_); _sv_ = _iv_; _iv_ = _tv; }
#define VEINI256         __m256i sv = _mm256_setzero_si256()
#define VE256(_iv_,_sv_) { __m256i _tv = mm256_xore_epi32(_iv_,_sv_); _sv_ = _iv_; _iv_ = _tv; }
#define VDINI128         __m128i sv =    _mm_setzero_si128()
#define VD128(_v_,_sv_)  _sv_ = _v_ = mm_xord_epi32(_v_,_sv_)
#define VDINI256         __m256i sv = _mm256_setzero_si256()
#define VD256(_v_,_sv_)  _sv_ = _v_ = mm256_xord_epi32(_v_,_sv_)
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VEINI128
#undef VDINI128
#undef VEINI256
#undef VDINI256
#undef VE128
#undef VD128
#undef VE256
#undef VD256
//---------

#undef ISDELTA
#undef STRIDE
//----------------- nibble ----------
#define STRIDE 8
#define TPENC            tp4enc
#define TPDEC            tp4dec
#define TPENC128V        tp4enc128v
#define TPDEC128V        tp4dec128v
#define TPENC256V        tp4enc256v
#define TPDEC256V        tp4dec256v

#define VEINI128
#define VEINI256
#define VE128(_v_,_sv_)
#define VE256(_v_,_sv_)
#define VDINI128
#define VDINI256
#define VD128(_ov_,_sv_)
#define VD256(_ov_,_sv_)
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VEINI128
#undef VDINI128
#undef VEINI256
#undef VDINI256
#undef VE128
#undef VD128
#undef VE256
#undef VD256

//-------------
#define ISDELTA
//-- zigzag
#define TPENC            tp4zenc
#define TPDEC            tp4zdec
#define TPENC128V        tp4zenc128v
#define TPDEC128V        tp4zdec128v
#define TPENC256V        tp4zenc256v
#define TPDEC256V        tp4zdec256v

#define VEINI128         __m128i sv = _mm_setzero_si128()
#define VE128(_iv_,_sv_) { __m128i _tv = mm_delta_epi32(_iv_,_sv_); _sv_ = _iv_; _iv_ = mm_zzage_epi32(_tv); }
#define VEINI256         __m256i sv = _mm256_setzero_si256()
#define VE256(_iv_,_sv_) { __m256i _tv = mm256_delta_epi32(_iv_,_sv_); _sv_ = _iv_; _iv_ = mm256_zzage_epi32(_tv); }
#define VDINI128         __m128i sv = _mm_setzero_si128()
#define VD128(_v_,_sv_)  _v_ = mm_zzagd_epi32( _v_); _sv_ = mm_scan_epi32(_v_,_sv_); _v_ = _sv_
#define VDINI256         __m256i sv = _mm256_setzero_si256()
#define VD256(_v_,_sv_)  _v_ = mm256_zzagd_epi32(_v_); _sv_ = mm256_scan_epi32(_v_,_sv_); _v_ = _sv_
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VE128
#undef VD128
#undef VE256
#undef VD256

//-- xor
#define TPENC            tp4xenc
#define TPDEC            tp4xdec
#define TPENC128V        tp4xenc128v
#define TPDEC128V        tp4xdec128v
#define TPENC256V        tp4xenc256v
#define TPDEC256V        tp4xdec256v

#define VEINI128         __m128i sv = _mm_setzero_si128()
#define VE128(_iv_,_sv_) { __m128i _tv = mm_xore_epi32(_iv_,_sv_); _sv_ = _iv_; _iv_ = _tv; }
#define VEINI256         __m256i sv = _mm256_setzero_si256()
#define VE256(_iv_,_sv_) { __m256i _tv = mm256_xore_epi32(_iv_,_sv_); _sv_ = _iv_; _iv_ = _tv; }
#define VDINI128         __m128i sv = _mm_setzero_si128()
#define VD128(_v_,_sv_)  _sv_ = mm_xord_epi32(_v_,_sv_); _v_ = _sv_
#define VDINI256         __m256i sv = _mm256_setzero_si256()
#define VD256(_v_,_sv_)  _sv_ = mm256_xord_epi32(_v_,_sv_); _v_ = _sv_
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VEINI128
#undef VDINI128
#undef VEINI256
#undef VDINI256
#undef VE128
#undef VD128
#undef VE256
#undef VD256

//--------------
#undef ISDELTA
#undef STRIDE
#undef ESIZE
#undef USIZE
//------------------------------- 64 bits ---------------------------------------------------------------
#define ESIZE 8
#define USIZE 64

#define STRIDE ESIZE
//--- byte 64 bits ------------
#define TPENC            tpenc
#define TPDEC            tpdec
#define TPENC128V        tpenc128v
#define TPDEC128V        tpdec128v
#define TPENC256V        tpenc256v
#define TPDEC256V        tpdec256v

#define VEINI128
#define VEINI256
#define VE128(_v_,_sv_)
#define VE256(_v_,_sv_)
#define VDINI128
#define VDINI256
#define VD128(_ov_,_sv_)
#define VD256(_ov_,_sv_)
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VEINI128
#undef VDINI128
#undef VEINI256
#undef VDINI256
#undef VE128
#undef VD128
#undef VE256
#undef VD256

//---------------
#define ISDELTA
//--- zigzag
#define TPENC            tpzenc
#define TPDEC            tpzdec
#define TPENC128V        tpzenc128v
#define TPDEC128V        tpzdec128v
#define TPENC256V        tpzenc256v
#define TPDEC256V        tpzdec256v

#define VEINI128         __m128i sv =    _mm_setzero_si128()
#define VE128(_iv_,_sv_)                                     { __m128i _tv =   mm_delta_epi64(_iv_,_sv_); _sv_ = _iv_; _iv_ =    mm_zzage_epi64(_tv); }
#define VEINI256         __m256i sv = _mm256_setzero_si256()
#define VE256(_iv_,_sv_)                                     { __m256i _tv = mm256_delta_epi64(_iv_,_sv_); _sv_ = _iv_; _iv_ = mm256_zzage_epi64(_tv); }
#define VDINI128         __m128i sv =    _mm_setzero_si128()
#define VD128(_v_,_sv_)                                      _v_ =    mm_zzagd_epi64(_v_); _sv_ =    mm_scan_epi64(_v_,_sv_); _v_ = _sv_
#define VDINI256         __m256i sv = _mm256_setzero_si256()
#define VD256(_v_,_sv_)                                      _v_ = mm256_zzagd_epi64(_v_); _sv_ = mm256_scan_epi64(_v_,_sv_); _v_ = _sv_
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VEINI128
#undef VDINI128
#undef VEINI256
#undef VDINI256
#undef VE128
#undef VD128
#undef VE256
#undef VD256

//--- xor
#define TPENC            tpxenc
#define TPDEC            tpxdec
#define TPENC128V        tpxenc128v
#define TPDEC128V        tpxdec128v
#define TPENC256V        tpxenc256v
#define TPDEC256V        tpxdec256v

#define VEINI128         __m128i sv = _mm_setzero_si128()
#define VE128(_iv_,_sv_)                                      { __m128i _tv =    mm_xore_epi64(_iv_,_sv_); _sv_ = _iv_; _iv_ = _tv; }
#define VEINI256         __m256i sv = _mm256_setzero_si256()
#define VE256(_iv_,_sv_)                                      { __m256i _tv = mm256_xore_epi64(_iv_,_sv_); _sv_ = _iv_; _iv_ = _tv; }
#define VDINI128         __m128i sv =    _mm_setzero_si128()
#define VD128(_v_,_sv_)                                       _sv_ = _v_ =    mm_xord_epi64(_v_,_sv_)
#define VDINI256         __m256i sv = _mm256_setzero_si256()
#define VD256(_v_,_sv_)                                       _sv_ = _v_ = mm256_xord_epi64(_v_,_sv_)
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VEINI128
#undef VDINI128
#undef VEINI256
#undef VDINI256
#undef VE128
#undef VD128
#undef VE256
#undef VD256
//-----------
#undef ISDELTA
#undef STRIDE
//---------- nibble ----------
#define STRIDE 16
#define TPENC            tp4enc
#define TPDEC            tp4dec
#define TPENC128V        tp4enc128v
#define TPDEC128V        tp4dec128v
#define TPENC256V        tp4enc256v
#define TPDEC256V        tp4dec256v

#define VEINI128
#define VEINI256
#define VE128(_v_,_sv_)
#define VE256(_v_,_sv_)
#define VDINI128
#define VDINI256
#define VD128(_ov_,_sv_)
#define VD256(_ov_,_sv_)
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VEINI128
#undef VDINI128
#undef VEINI256
#undef VDINI256
#undef VE128
#undef VD128
#undef VE256
#undef VD256
//-------------------------
#define ISDELTA
//-- zigzag
#define TPENC            tp4zenc
#define TPDEC            tp4zdec
#define TPENC128V        tp4zenc128v
#define TPDEC128V        tp4zdec128v
#define TPENC256V        tp4zenc256v
#define TPDEC256V        tp4zdec256v

#define VEINI128         __m128i sv =    _mm_setzero_si128()
#define VE128(_iv_,_sv_)                                     { __m128i _tv =   mm_delta_epi64(_iv_,_sv_); _sv_ = _iv_; _iv_ =    mm_zzage_epi64(_tv); }
#define VEINI256         __m256i sv = _mm256_setzero_si256()
#define VE256(_iv_,_sv_)                                     { __m256i _tv = mm256_delta_epi64(_iv_,_sv_); _sv_ = _iv_; _iv_ = mm256_zzage_epi64(_tv); }
#define VDINI128         __m128i sv =    _mm_setzero_si128()
#define VD128(_v_,_sv_)                                      _v_ =    mm_zzagd_epi64(_v_); _sv_ =    mm_scan_epi64(_v_,_sv_); _v_ = _sv_
#define VDINI256         __m256i sv = _mm256_setzero_si256()
#define VD256(_v_,_sv_)                                      _v_ = mm256_zzagd_epi64(_v_); _sv_ = mm256_scan_epi64(_v_,_sv_); _v_ = _sv_
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VEINI128
#undef VDINI128
#undef VEINI256
#undef VDINI256
#undef VE128
#undef VD128
#undef VE256
#undef VD256

//-- xor
#define TPENC            tp4xenc
#define TPDEC            tp4xdec
#define TPENC128V        tp4xenc128v
#define TPDEC128V        tp4xdec128v
#define TPENC256V        tp4xenc256v
#define TPDEC256V        tp4xdec256v

#define VEINI128         __m128i sv = _mm_setzero_si128()
#define VE128(_iv_,_sv_)                                      { __m128i _tv =    mm_xore_epi64(_iv_,_sv_); _sv_ = _iv_; _iv_ = _tv; }
#define VEINI256         __m256i sv = _mm256_setzero_si256()
#define VE256(_iv_,_sv_)                                      { __m256i _tv = mm256_xore_epi64(_iv_,_sv_); _sv_ = _iv_; _iv_ = _tv; }
#define VDINI128         __m128i sv =    _mm_setzero_si128()
#define VD128(_v_,_sv_)                                       _sv_ = _v_ =    mm_xord_epi64(_v_,_sv_)
#define VDINI256         __m256i sv = _mm256_setzero_si256()
#define VD256(_v_,_sv_)                                       _sv_ = _v_ = mm256_xord_epi64(_v_,_sv_)
#include "transpose.c"
#undef TPENC
#undef TPDEC
#undef TPENC128V
#undef TPDEC128V
#undef TPENC256V
#undef TPDEC256V
#undef VEINI128
#undef VDINI128
#undef VEINI256
#undef VDINI256
#undef VE128
#undef VD128
#undef VE256
#undef VD256

#undef ISDELTA
#undef STRIDE
#undef ESIZE
#undef USIZE
#undef ST

#else //*************************************************************  Templates ********************************************************************************************************

#define SIE(p,i)  (p+=stride) //faster on ARM //#define SIE(_p_,_i_)  (_p_+ _i_*stride)
#define SID(p,i)  (p+=stride) //#define SID(_p_,_i_)  (_p_+ _i_*stride)

  #if defined(__AVX2__)
    #ifdef TPENC256V
void T2(TPENC256V, ESIZE)(unsigned char *in, unsigned n, unsigned char *out) {
  unsigned      v = n&~(ESIZE*32-1);
  unsigned      stride = v/STRIDE;
  unsigned char *op,*ip;
  VEINI256;
    #if ESIZE == 2
  __m256i sf = _mm256_set_epi8( 15, 13, 11, 9, 7, 5, 3, 1,
                                14, 12, 10, 8, 6, 4, 2, 0,
                                15, 13, 11, 9, 7, 5, 3, 1,
                                14, 12, 10, 8, 6, 4, 2, 0);
  __m256i sv0 = _mm256_set_epi8(15, 13, 11, 9,
                                 7,  5,  3, 1,
                                14, 12, 10, 8,
                                 6,  4,  2, 0,
                                15, 13, 11, 9,
                                 7,  5,  3, 1,
                                14, 12, 10, 8,
                                 6,  4,  2, 0);
  __m256i sv1 = _mm256_set_epi8(14, 12, 10, 8,
                                 6,  4,  2, 0,
                                15, 13, 11, 9,
                                 7,  5,  3, 1,
                                14, 12, 10, 8,
                                 6,  4,  2, 0,
                                15, 13, 11, 9,
                                 7,  5,  3, 1);
   #else
  __m256i pv = _mm256_set_epi32( 7, 3, 6, 2, 5, 1, 4, 0),
      #if ESIZE == 4
          sv0 = _mm256_set_epi8(15, 11, 7, 3,
                                13,  9, 5, 1,
                                14, 10, 6, 2,
                                12,  8, 4, 0,
                                15, 11, 7, 3,
                                13,  9, 5, 1,
                                14, 10, 6, 2,
                                12,  8, 4, 0),
           sv1= _mm256_set_epi8(13,  9, 5, 1,
                                15, 11, 7, 3,
                                12,  8, 4, 0,
                                14, 10, 6, 2,
                                13,  9, 5, 1,
                                15, 11, 7, 3,
                                12,  8, 4, 0,
                                14, 10, 6, 2);
      #else
           sf = _mm256_set_epi8(15,  7,
                                14,  6,
                                13,  5,
                                12,  4,
                                11,  3,
                                10,  2,
                                 9,  1,
                                 8,  0,
                                15,  7,
                                14,  6,
                                13,  5,
                                12,  4,
                                11,  3,
                                10,  2,
                                 9,  1,
                                 8,  0 ),
           tv = _mm256_set_epi8(15, 14, 11, 10, 13, 12,  9,  8,
                                 7,  6,  3,  2,  5,  4,  1,  0,
                                15, 14, 11, 10, 13, 12,  9,  8,
                                 7,  6,  3,  2,  5,  4,  1,  0);
      #endif
    #endif
    #if STRIDE > ESIZE // ------------------ byte transpose ----------------------------------
  __m256i cl = _mm256_set1_epi8( 0x0f),
          ch = _mm256_set1_epi8( 0xf0u),
          cb = _mm256_set1_epi16(0xff);
    #endif

  for(ip = in,op = out; ip != in+v; ip += ESIZE*32, op += ESIZE*32/STRIDE) {
    unsigned char *p = op;                                                      PREFETCH(ip+ESIZE*192,0);
    __m256i iv[ESIZE], ov[ESIZE == 2 ? ESIZE + 2 : ESIZE];
      #if   ESIZE == 2
	ov[0] = LD256((__m256i *) ip    ); VE256(ov[0],sv); ov[0] = _mm256_shuffle_epi8(ov[0], sv0);
    ov[1] = LD256((__m256i *)(ip+32)); VE256(ov[1],sv); ov[1] = _mm256_shuffle_epi8(ov[1], sv1);
    iv[0] = _mm256_permute4x64_epi64(_mm256_blend_epi32(ov[0], ov[1],0b11001100),_MM_SHUFFLE(3, 1, 2, 0));
    iv[1] = _mm256_blend_epi32(ov[0], ov[1],0b00110011);
    iv[1] = _mm256_permute4x64_epi64(_mm256_shuffle_epi32(iv[1],_MM_SHUFFLE(1, 0, 3, 2)),_MM_SHUFFLE(3, 1, 2, 0));
      #elif ESIZE == 4
    iv[0] = LD256((__m256i *) ip    ); VE256(iv[0],sv); iv[0] = _mm256_shuffle_epi8(iv[0], sv0);
    iv[1] = LD256((__m256i *)(ip+32)); VE256(iv[1],sv); iv[1] = _mm256_shuffle_epi8(iv[1], sv1);
    iv[2] = LD256((__m256i *)(ip+64)); VE256(iv[2],sv); iv[2] = _mm256_shuffle_epi8(iv[2], sv0);
    iv[3] = LD256((__m256i *)(ip+96)); VE256(iv[3],sv); iv[3] = _mm256_shuffle_epi8(iv[3], sv1);

    ov[0] = _mm256_blend_epi32(iv[0], iv[1],0b10101010);
    ov[1] = _mm256_shuffle_epi32(_mm256_blend_epi32(iv[0], iv[1],0b01010101),_MM_SHUFFLE(2, 3, 0, 1));
    ov[2] = _mm256_blend_epi32(iv[2], iv[3],0b10101010);
    ov[3] = _mm256_shuffle_epi32(_mm256_blend_epi32(iv[2], iv[3],0b01010101),_MM_SHUFFLE(2, 3, 0, 1));

    iv[0] = _mm256_permutevar8x32_epi32(_mm256_unpacklo_epi64(ov[0], ov[2]), pv);
    iv[1] = _mm256_permutevar8x32_epi32(_mm256_unpackhi_epi64(ov[0], ov[2]), pv);
    iv[2] = _mm256_permutevar8x32_epi32(_mm256_unpacklo_epi64(ov[1], ov[3]), pv);
    iv[3] = _mm256_permutevar8x32_epi32(_mm256_unpackhi_epi64(ov[1], ov[3]), pv);
      #else
    ov[0] = LD256((__m256i *) ip    ); VE256(ov[0],sv); ov[0] = _mm256_shuffle_epi8(ov[0], sf);
    ov[1] = LD256((__m256i *)(ip+32)); VE256(ov[1],sv); ov[1] = _mm256_shuffle_epi8(ov[1], sf);
    ov[2] = LD256((__m256i *)(ip+64)); VE256(ov[2],sv); ov[2] = _mm256_shuffle_epi8(ov[2], sf);
    ov[3] = LD256((__m256i *)(ip+96)); VE256(ov[3],sv); ov[3] = _mm256_shuffle_epi8(ov[3], sf);

    iv[0] = _mm256_unpacklo_epi16(ov[0], ov[1]); iv[1] = _mm256_unpackhi_epi16(ov[0], ov[1]);
    iv[2] = _mm256_unpacklo_epi16(ov[2], ov[3]); iv[3] = _mm256_unpackhi_epi16(ov[2], ov[3]);

    ov[0] = _mm256_unpacklo_epi32(iv[0], iv[2]); ov[1] = _mm256_unpackhi_epi32(iv[0], iv[2]);
    ov[2] = _mm256_unpacklo_epi32(iv[1], iv[3]); ov[3] = _mm256_unpackhi_epi32(iv[1], iv[3]);


    ov[4] = LD256((__m256i *)(ip+128)); VE256(ov[4],sv); ov[4] = _mm256_shuffle_epi8(ov[4], sf);
    ov[5] = LD256((__m256i *)(ip+160)); VE256(ov[5],sv); ov[5] = _mm256_shuffle_epi8(ov[5], sf);
    ov[6] = LD256((__m256i *)(ip+192)); VE256(ov[6],sv); ov[6] = _mm256_shuffle_epi8(ov[6], sf);
    ov[7] = LD256((__m256i *)(ip+224)); VE256(ov[7],sv); ov[7] = _mm256_shuffle_epi8(ov[7], sf);

    iv[4] = _mm256_unpacklo_epi16(ov[4], ov[5]); iv[5] = _mm256_unpackhi_epi16(ov[4], ov[5]);
    iv[6] = _mm256_unpacklo_epi16(ov[6], ov[7]); iv[7] = _mm256_unpackhi_epi16(ov[6], ov[7]);

    ov[4] = _mm256_unpacklo_epi32(iv[4], iv[6]); ov[5] = _mm256_unpackhi_epi32(iv[4], iv[6]);
    ov[6] = _mm256_unpacklo_epi32(iv[5], iv[7]); ov[7] = _mm256_unpackhi_epi32(iv[5], iv[7]);

    iv[0] = _mm256_shuffle_epi8(_mm256_permutevar8x32_epi32(_mm256_unpacklo_epi64(ov[0], ov[4]), pv), tv);
    iv[1] = _mm256_shuffle_epi8(_mm256_permutevar8x32_epi32(_mm256_unpackhi_epi64(ov[0], ov[4]), pv), tv);
    iv[2] = _mm256_shuffle_epi8(_mm256_permutevar8x32_epi32(_mm256_unpacklo_epi64(ov[1], ov[5]), pv), tv);
    iv[3] = _mm256_shuffle_epi8(_mm256_permutevar8x32_epi32(_mm256_unpackhi_epi64(ov[1], ov[5]), pv), tv);

    iv[4] = _mm256_shuffle_epi8(_mm256_permutevar8x32_epi32(_mm256_unpacklo_epi64(ov[2], ov[6]), pv), tv);
    iv[5] = _mm256_shuffle_epi8(_mm256_permutevar8x32_epi32(_mm256_unpackhi_epi64(ov[2], ov[6]), pv), tv);
    iv[6] = _mm256_shuffle_epi8(_mm256_permutevar8x32_epi32(_mm256_unpacklo_epi64(ov[3], ov[7]), pv), tv);
    iv[7] = _mm256_shuffle_epi8(_mm256_permutevar8x32_epi32(_mm256_unpackhi_epi64(ov[3], ov[7]), pv), tv);
      #endif

      #if STRIDE <= ESIZE
    _mm256_storeu_si256((__m256i *) p,          iv[0]);
    _mm256_storeu_si256((__m256i *)(p+=stride), iv[1]);
        #if ESIZE > 2
    _mm256_storeu_si256((__m256i *)(p+=stride), iv[2]);
    _mm256_storeu_si256((__m256i *)(p+=stride), iv[3]);
          #if ESIZE > 4
    _mm256_storeu_si256((__m256i *)(p+=stride), iv[4]);
    _mm256_storeu_si256((__m256i *)(p+=stride), iv[5]);
    _mm256_storeu_si256((__m256i *)(p+=stride), iv[6]);
    _mm256_storeu_si256((__m256i *)(p+=stride), iv[7]);
          #endif
        #endif

      #else //---------------------- Nibble Transpose ------------------------
    #undef ST128
    #define mm256_packus_epi16(a, b) _mm256_permute4x64_epi64(_mm256_packus_epi16(a, b), _MM_SHUFFLE(3, 1, 2, 0))
    #define ST128(_p_,_v_,_i_) _mm_storeu_si128((__m128i *)SIE(_p_,_i_), _mm256_castsi256_si128(_v_))
    #define ST1280(_p_,_v_)    _mm_storeu_si128((__m128i *)(_p_), _mm256_castsi256_si128(_v_))

    ov[0] = _mm256_and_si256(iv[0], cl);                      ov[0] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[0],4), ov[0]),cb); ov[0] = mm256_packus_epi16(ov[0], _mm256_srli_si256( ov[0],2));
    ov[1] = _mm256_srli_epi16(_mm256_and_si256(iv[0], ch),4); ov[1] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[1],4), ov[1]),cb); ov[1] = mm256_packus_epi16(ov[1], _mm256_srli_si256( ov[1],2));
    ov[2] = _mm256_and_si256(iv[1], cl);                      ov[2] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[2],4), ov[2]),cb); ov[2] = mm256_packus_epi16(ov[2], _mm256_srli_si256( ov[2],2));
    ov[3] = _mm256_srli_epi16(_mm256_and_si256(iv[1], ch),4); ov[3] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[3],4), ov[3]),cb); ov[3] = mm256_packus_epi16(ov[3], _mm256_srli_si256( ov[3],2));
    ST1280(p,ov[0]);  ST128(p,ov[1],1); ST128(p,ov[2],2); ST128(p,ov[3],3);
        #if ESIZE > 2
    ov[0] = _mm256_and_si256(iv[2], cl);                      ov[0] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[0],4), ov[0]),cb); ov[0] = mm256_packus_epi16(ov[0], _mm256_srli_si256( ov[0],2));
    ov[1] = _mm256_srli_epi16(_mm256_and_si256(iv[2], ch),4); ov[1] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[1],4), ov[1]),cb); ov[1] = mm256_packus_epi16(ov[1], _mm256_srli_si256( ov[1],2));
    ov[2] = _mm256_and_si256(iv[3], cl);                      ov[2] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[2],4), ov[2]),cb); ov[2] = mm256_packus_epi16(ov[2], _mm256_srli_si256( ov[2],2));
    ov[3] = _mm256_srli_epi16(_mm256_and_si256(iv[3], ch),4); ov[3] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[3],4), ov[3]),cb); ov[3] = mm256_packus_epi16(ov[3], _mm256_srli_si256( ov[3],2));
    ST128(p,ov[0],4); ST128(p,ov[1],5); ST128(p,ov[2],6); ST128(p,ov[3],7);
          #if ESIZE > 4
    ov[0] = _mm256_and_si256(iv[4], cl);                      ov[0] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[0],4), ov[0]),cb); ov[0] = mm256_packus_epi16(ov[0], _mm256_srli_si256(  ov[0],2));
    ov[1] = _mm256_srli_epi16(_mm256_and_si256(iv[4], ch),4); ov[1] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[1],4), ov[1]),cb); ov[1] = mm256_packus_epi16(ov[1], _mm256_srli_si256(  ov[1],2));
    ov[2] = _mm256_and_si256(iv[5], cl);                      ov[2] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[2],4), ov[2]),cb); ov[2] = mm256_packus_epi16(ov[2], _mm256_srli_si256(  ov[2],2));
    ov[3] = _mm256_srli_epi16(_mm256_and_si256(iv[5], ch),4); ov[3] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[3],4), ov[3]),cb); ov[3] = mm256_packus_epi16(ov[3], _mm256_srli_si256(  ov[3],2));
    ST128(p,ov[0],8); ST128(p,ov[1],9); ST128(p,ov[2],10); ST128(p,ov[3],11);

    ov[0] = _mm256_and_si256(iv[6], cl);                      ov[0] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[0],4), ov[0]),cb); ov[0] =  mm256_packus_epi16(ov[0], _mm256_srli_si256(  ov[0],2));
    ov[1] = _mm256_srli_epi16(_mm256_and_si256(iv[6], ch),4); ov[1] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[1],4), ov[1]),cb); ov[1] =  mm256_packus_epi16(ov[1], _mm256_srli_si256(  ov[1],2));
    ov[2] = _mm256_and_si256(iv[7], cl);                      ov[2] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[2],4), ov[2]),cb); ov[2] =  mm256_packus_epi16(ov[2], _mm256_srli_si256(  ov[2],2));
    ov[3] = _mm256_srli_epi16(_mm256_and_si256(iv[7], ch),4); ov[3] = _mm256_and_si256(_mm256_or_si256(_mm256_srli_epi16(ov[3],4), ov[3]),cb); ov[3] =  mm256_packus_epi16(ov[3], _mm256_srli_si256(  ov[3],2));
    ST128(p,ov[0],12); ST128(p,ov[1],13); ST128(p,ov[2],14); ST128(p,ov[3],15);
          #endif
        #endif
      #endif
  }
  T2(tpenc,ESIZE)(in+v, n-v, out+v);
}
    #endif // TPENC256V

    #ifdef TPDEC256V
#define NBL0(x,y) ov[x] = _mm256_permute4x64_epi64(_mm256_castsi128_si256(_mm_loadu_si128((__m128i *)(p       ))),_MM_SHUFFLE(3, 1, 2, 0));\
                  ov[y] = _mm256_permute4x64_epi64(_mm256_castsi128_si256(_mm_loadu_si128((__m128i *)(p+=stride))),_MM_SHUFFLE(3, 1, 2, 0));

#define NBL(x,y)  ov[x] = _mm256_permute4x64_epi64(_mm256_castsi128_si256(_mm_loadu_si128((__m128i *)(p+=stride))),_MM_SHUFFLE(3, 1, 2, 0));\
                  ov[y] = _mm256_permute4x64_epi64(_mm256_castsi128_si256(_mm_loadu_si128((__m128i *)(p+=stride))),_MM_SHUFFLE(3, 1, 2, 0));

#define NB(x,y,_iv_) {\
  ov[x] = _mm256_and_si256(_mm256_unpacklo_epi8(ov[x], _mm256_srli_epi16(ov[x],4)), cl);\
  ov[y] = _mm256_and_si256(_mm256_unpacklo_epi8(ov[y], _mm256_srli_epi16(ov[y],4)), cl);\
  _iv_  = _mm256_or_si256(_mm256_slli_epi16(ov[y],4), ov[x]); \
}

void T2(TPDEC256V, ESIZE)(unsigned char *in, unsigned n, unsigned char *out) {
  unsigned      v      = n&~(ESIZE*32-1);
  unsigned      stride = v/STRIDE;
  unsigned char *op,*ip;
  VDINI256;

    #if STRIDE > ESIZE
  __m256i cl = _mm256_set1_epi8(0x0f), ch=_mm256_set1_epi8(0xf0u), cb = _mm256_set1_epi16(0xff);
    #endif

  for(op = out,ip = in; op != out+v; ip += ESIZE*32/STRIDE, op += ESIZE*32) { unsigned char *p = ip;    PREFETCH(ip+ESIZE*192,0);
    __m256i iv[ESIZE], ov[ESIZE == 2 ? ESIZE + 2 : ESIZE];

      #if STRIDE > ESIZE
    NBL0(0,1); NBL( 2,3); NB(0,1,iv[0]); NB(2,3,iv[1]);
        #if ESIZE > 2
    NBL( 0,1); NBL( 2,3); NB(0,1,iv[2]); NB(2,3,iv[3]);
          #if ESIZE > 4
    NBL(4,5); NBL( 6,7); NB(4,5,iv[4]); NB(6,7,iv[5]);
    NBL(4,5); NBL( 6,7); NB(4,5,iv[6]); NB(6,7,iv[7]);
          #endif
        #endif
      #else
    iv[0] = _mm256_loadu_si256((__m256i *) p        );
    iv[1] = _mm256_loadu_si256((__m256i *)(p+=stride));
        #if ESIZE > 2
    iv[2] = _mm256_loadu_si256((__m256i *)(p+=stride));
    iv[3] = _mm256_loadu_si256((__m256i *)(p+=stride));
          #if ESIZE > 4
    iv[4] = _mm256_loadu_si256((__m256i *)(p+=stride));
    iv[5] = _mm256_loadu_si256((__m256i *)(p+=stride));
    iv[6] = _mm256_loadu_si256((__m256i *)(p+=stride));
    iv[7] = _mm256_loadu_si256((__m256i *)(p+=stride));
          #endif
        #endif
      #endif

      #if ESIZE == 2
    ov[0] = _mm256_permute4x64_epi64(iv[0], _MM_SHUFFLE(3, 1, 2, 0));
    ov[1] = _mm256_permute4x64_epi64(iv[1], _MM_SHUFFLE(3, 1, 2, 0));
    iv[0] = _mm256_unpacklo_epi8(ov[0], ov[1]); VD256(iv[0],sv); _mm256_storeu_si256((__m256i *)op,      iv[0]);
    iv[1] = _mm256_unpackhi_epi8(ov[0], ov[1]); VD256(iv[1],sv); _mm256_storeu_si256((__m256i *)(op+32), iv[1]);
      #elif ESIZE == 4
    ov[0] = _mm256_unpacklo_epi8( iv[0], iv[1]); ov[1] = _mm256_unpackhi_epi8( iv[0], iv[1]);
    ov[2] = _mm256_unpacklo_epi8( iv[2], iv[3]); ov[3] = _mm256_unpackhi_epi8( iv[2], iv[3]);

    iv[0] = _mm256_unpacklo_epi16(ov[0], ov[2]); iv[1] = _mm256_unpackhi_epi16(ov[0], ov[2]);
    iv[2] = _mm256_unpacklo_epi16(ov[1], ov[3]); iv[3] = _mm256_unpackhi_epi16(ov[1], ov[3]);

    ov[0] = _mm256_permute2x128_si256(iv[0], iv[1], (2 << 4) | 0);
    ov[1] = _mm256_permute2x128_si256(iv[2], iv[3], (2 << 4) | 0);
    ov[2] = _mm256_permute2x128_si256(iv[0], iv[1], (3 << 4) | 1);
    ov[3] = _mm256_permute2x128_si256(iv[2], iv[3], (3 << 4) | 1);
    VD256(ov[0],sv); _mm256_storeu_si256((__m256i *) op,     ov[0]);
    VD256(ov[1],sv); _mm256_storeu_si256((__m256i *)(op+32), ov[1]);
    VD256(ov[2],sv); _mm256_storeu_si256((__m256i *)(op+64), ov[2]);
    VD256(ov[3],sv); _mm256_storeu_si256((__m256i *)(op+96), ov[3]);
      #else
    ov[0] = _mm256_unpacklo_epi8(iv[0], iv[1]); ov[1] = _mm256_unpackhi_epi8(iv[0], iv[1]);
    ov[2] = _mm256_unpacklo_epi8(iv[2], iv[3]); ov[3] = _mm256_unpackhi_epi8(iv[2], iv[3]);
    iv[0] = _mm256_permute4x64_epi64(_mm256_unpacklo_epi16(ov[0], ov[2]), _MM_SHUFFLE(3, 1, 2, 0));
    iv[1] = _mm256_permute4x64_epi64(_mm256_unpackhi_epi16(ov[0], ov[2]), _MM_SHUFFLE(3, 1, 2, 0));
    iv[2] = _mm256_permute4x64_epi64(_mm256_unpacklo_epi16(ov[1], ov[3]), _MM_SHUFFLE(3, 1, 2, 0));
    iv[3] = _mm256_permute4x64_epi64(_mm256_unpackhi_epi16(ov[1], ov[3]), _MM_SHUFFLE(3, 1, 2, 0));

    ov[4] = _mm256_unpacklo_epi8(iv[4], iv[5]); ov[5] = _mm256_unpackhi_epi8(iv[4], iv[5]);
    ov[6] = _mm256_unpacklo_epi8(iv[6], iv[7]); ov[7] = _mm256_unpackhi_epi8(iv[6], iv[7]);
    iv[4] = _mm256_permute4x64_epi64(_mm256_unpacklo_epi16(ov[4], ov[6]), _MM_SHUFFLE(3, 1, 2, 0));
    iv[5] = _mm256_permute4x64_epi64(_mm256_unpackhi_epi16(ov[4], ov[6]), _MM_SHUFFLE(3, 1, 2, 0));
    iv[6] = _mm256_permute4x64_epi64(_mm256_unpacklo_epi16(ov[5], ov[7]), _MM_SHUFFLE(3, 1, 2, 0));
    iv[7] = _mm256_permute4x64_epi64(_mm256_unpackhi_epi16(ov[5], ov[7]), _MM_SHUFFLE(3, 1, 2, 0));

    ov[0] = _mm256_unpacklo_epi32(iv[0], iv[4]);
    ov[1] = _mm256_unpacklo_epi32(iv[1], iv[5]);
    ov[2] = _mm256_unpacklo_epi32(iv[2], iv[6]);
    ov[3] = _mm256_unpacklo_epi32(iv[3], iv[7]);
    ov[4] = _mm256_unpackhi_epi32(iv[0], iv[4]);
    ov[5] = _mm256_unpackhi_epi32(iv[1], iv[5]);
    ov[6] = _mm256_unpackhi_epi32(iv[2], iv[6]);
    ov[7] = _mm256_unpackhi_epi32(iv[3], iv[7]);

    VD256(ov[0],sv); ST256((__m256i *) op,      ov[0] );
    VD256(ov[1],sv); ST256((__m256i *)(op+ 32), ov[1] );
    VD256(ov[2],sv); ST256((__m256i *)(op+ 64), ov[2] );
    VD256(ov[3],sv); ST256((__m256i *)(op+ 96), ov[3] );
    VD256(ov[4],sv); ST256((__m256i *)(op+128), ov[4] );
    VD256(ov[5],sv); ST256((__m256i *)(op+160), ov[5] );
    VD256(ov[6],sv); ST256((__m256i *)(op+192), ov[6] );
    VD256(ov[7],sv); ST256((__m256i *)(op+224), ov[7] );
      #endif
  }
  if(n-v) T2(tpdec,ESIZE)(in+v, n-v, out+v);
}
    #endif //TPDEC256V
  #else //__AVX2__

	#if (defined(__SSE3__) || defined(__ARM_NEON)) && (ESIZE == 2 || ESIZE == 4 || ESIZE == 8)
#define ST(_p_,_v_,_i_)  _mm_storeu_si128((__m128i *)SIE(_p_,_i_), _v_)
#define ST0(_p_,_v_)  _mm_storeu_si128((__m128i *)(_p_), _v_)

void T2(TPENC128V, ESIZE)(unsigned char *in, unsigned n, unsigned char *out) {
  unsigned           v = n&~(ESIZE*32-1);
  unsigned      stride = v/STRIDE;
  unsigned char *op,*ip;

    #if defined(__SSE3__) || defined(__ARM_NEON)
      #if ESIZE == 2
  __m128i sf = _mm_set_epi8(15, 13, 11, 9, 7, 5, 3, 1,
                            14, 12, 10, 8, 6, 4, 2, 0);
      #elif ESIZE == 4
  __m128i sf = _mm_set_epi8(15, 11, 7,3,
                            14, 10, 6,2,
                            13,  9, 5,1,
                            12,  8, 4,0);
      #else
  __m128i sf = _mm_set_epi8(15,  7,
                            14,  6,
                            13,  5,
                            12,  4,
                            11,  3,
                            10,  2,
                             9,  1,
                             8,  0  );
      #endif
    #endif
  VEINI128;
      #if STRIDE > ESIZE
  __m128i cl = _mm_set1_epi8(0x0f), ch=_mm_set1_epi8(0xf0u), cb = _mm_set1_epi16(0xff);
      #endif

  for(ip = in, op = out; ip != in+v; ip+=ESIZE*16,op += ESIZE*16/STRIDE) { unsigned char *p = op;   PREFETCH(ip+(ESIZE*16)*ESIZE,0);
    __m128i iv[ESIZE], ov[ESIZE == 2 ? ESIZE + 2 : ESIZE];
      #if defined(__SSSE3__) || defined(__ARM_NEON)
        #if   ESIZE == 2
          #ifdef __ARM_NEON
    uint8x16x2_t w = vld2q_u8(ip);
            #if STRIDE <= ESIZE
    ST0(p,(__m128i)w.val[0]); ST(p,(__m128i)w.val[1],1);
            #else
    iv[0] = (__m128i)w.val[0]; iv[1] = (__m128i)w.val[1];
            #endif
          #else
    ov[0] = LD128(ip);    VE128(ov[0],sv); ov[0] = _mm_shuffle_epi8(ov[0], sf);
    ov[1] = LD128(ip+16); VE128(ov[1],sv); ov[1] = _mm_shuffle_epi8(ov[1], sf);

    iv[0] = _mm_unpacklo_epi64(ov[0], ov[1]); iv[1] = _mm_unpackhi_epi64(ov[0], ov[1]);
            #if STRIDE <= ESIZE
    ST0(p,iv[0]); ST(p,iv[1],1);
            #endif
          #endif

        #elif ESIZE == 4
          #ifdef __ARM_NEON
    uint8x16x4_t w = vld4q_u8(ip);
            #if STRIDE <= ESIZE
    ST0(p,(__m128i)w.val[0]); ST(p,(__m128i)w.val[1],1); ST(p,(__m128i)w.val[2],2); ST(p,(__m128i)w.val[3],3);
            #else
    iv[0] = (__m128i)w.val[0]; iv[1] = (__m128i)w.val[1]; iv[2] = (__m128i)w.val[2]; iv[3] = (__m128i)w.val[3];
            #endif
          #else
    iv[0] = LD128(ip   ); VE128(iv[0],sv); iv[0] = _mm_shuffle_epi8(iv[0], sf);
    iv[1] = LD128(ip+16); VE128(iv[1],sv); iv[1] = _mm_shuffle_epi8(iv[1], sf);
    iv[2] = LD128(ip+32); VE128(iv[2],sv); iv[2] = _mm_shuffle_epi8(iv[2], sf);
    iv[3] = LD128(ip+48); VE128(iv[3],sv); iv[3] = _mm_shuffle_epi8(iv[3], sf);

    ov[0] = _mm_unpacklo_epi32(iv[0], iv[1]); ov[1] = _mm_unpackhi_epi32(iv[0], iv[1]);
    ov[2] = _mm_unpacklo_epi32(iv[2], iv[3]); ov[3] = _mm_unpackhi_epi32(iv[2], iv[3]);

    iv[0] = _mm_unpacklo_epi64(ov[0], ov[2]); iv[1] = _mm_unpackhi_epi64(ov[0], ov[2]);
    iv[2] = _mm_unpacklo_epi64(ov[1], ov[3]); iv[3] = _mm_unpackhi_epi64(ov[1], ov[3]);
            #if STRIDE <= ESIZE
    ST0(p,iv[0]); ST(p,iv[1],1); ST(p,iv[2],2); ST(p,iv[3],3);
            #endif
          #endif

        #elif ESIZE == 8
          #ifdef __ARM_NEON
    #define vzipl_u16(_a_,_b_) vzip_u16(vget_low_u16((uint16x8_t)(_a_)), vget_low_u16((uint16x8_t)(_b_)))
    #define vziph_u16(_a_,_b_) vzip_u16(vget_high_u16((uint16x8_t)(_a_)), vget_high_u16((uint16x8_t)(_b_)))
    //#define VQ
            #ifndef VQ
    uint16x4x2_t v16[8];
    uint32x2x2_t v32[8];
            #else
    uint8x16x2_t v8[4];
    uint16x8x2_t v16[4];
    uint32x4x2_t v32[4];   //uint64x2x2_t v64[4];
            #endif
            #ifdef VQ
    ov[0] = LD128(ip    ); VE128(ov[0],sv); //ov[0] = _mm_shuffle_epi8(ov[0], sv);
    ov[1] = LD128(ip+ 16); VE128(ov[1],sv); //ov[1] = _mm_shuffle_epi8(ov[1], sv);
    ov[2] = LD128(ip+ 32); VE128(ov[2],sv); //ov[2] = _mm_shuffle_epi8(ov[2], sv);
    ov[3] = LD128(ip+ 48); VE128(ov[3],sv); //ov[3] = _mm_shuffle_epi8(ov[3], sv);
    ov[4] = LD128(ip+ 64); VE128(ov[4],sv); //ov[4] = _mm_shuffle_epi8(ov[4], sv);
    ov[5] = LD128(ip+ 80); VE128(ov[5],sv); //ov[5] = _mm_shuffle_epi8(ov[5], sv);
    ov[6] = LD128(ip+ 96); VE128(ov[6],sv); //ov[6] = _mm_shuffle_epi8(ov[6], sv);
    ov[7] = LD128(ip+112); VE128(ov[7],sv); //ov[7] = _mm_shuffle_epi8(ov[7], sv);

    v8[0]  = vzipq_u8((uint8x16_t)ov[0], (uint8x16_t)ov[1]);
    v8[1]  = vzipq_u8((uint8x16_t)ov[2], (uint8x16_t)ov[3]);
    v8[2]  = vzipq_u8((uint8x16_t)ov[4], (uint8x16_t)ov[5]);
    v8[3]  = vzipq_u8((uint8x16_t)ov[6], (uint8x16_t)ov[7]);

/*    v16[0] = vzipq_u16((uint16x8_t)ov[0], (uint16x8_t)ov[1]);
    v16[1] = vzipq_u16((uint16x8_t)ov[2], (uint16x8_t)ov[3]);
    v16[2] = vzipq_u16((uint16x8_t)ov[4], (uint16x8_t)ov[5]);
    v16[3] = vzipq_u16((uint16x8_t)ov[6], (uint16x8_t)ov[7]);*/
    v16[0] = vzipq_u16(vreinterpretq_u16_u8( v8[0].val[0]),  vreinterpretq_u16_u8(v8[1].val[0]));
    v16[1] = vzipq_u16(vreinterpretq_u16_u8( v8[0].val[1]),  vreinterpretq_u16_u8(v8[1].val[1]));
    v16[2] = vzipq_u16(vreinterpretq_u16_u8( v8[2].val[0]),  vreinterpretq_u16_u8(v8[3].val[0]));
    v16[3] = vzipq_u16(vreinterpretq_u16_u8( v8[2].val[1]),  vreinterpretq_u16_u8(v8[3].val[1]));

    v32[0] = vzipq_u32(vreinterpretq_u32_u16(v16[0].val[0]), vreinterpretq_u32_u16(v16[2].val[0]));
    v32[1] = vzipq_u32(vreinterpretq_u32_u16(v16[0].val[1]), vreinterpretq_u32_u16(v16[2].val[1]));
    v32[2] = vzipq_u32(vreinterpretq_u32_u16(v16[1].val[0]), vreinterpretq_u32_u16(v16[3].val[0]));
    v32[3] = vzipq_u32(vreinterpretq_u32_u16(v16[1].val[1]), vreinterpretq_u32_u16(v16[3].val[1]));

    iv[0] = _mm_unpacklo_epi64(v32[0].val[0], v32[2].val[0]); iv[1] = _mm_unpackhi_epi64(v32[0].val[0], v32[2].val[0]);
    iv[2] = _mm_unpacklo_epi64(v32[0].val[1], v32[2].val[1]); iv[3] = _mm_unpackhi_epi64(v32[0].val[1], v32[2].val[1]);
    iv[4] = _mm_unpacklo_epi64(v32[1].val[0], v32[3].val[0]); iv[5] = _mm_unpackhi_epi64(v32[1].val[0], v32[3].val[0]);
    iv[6] = _mm_unpacklo_epi64(v32[1].val[1], v32[3].val[1]); iv[7] = _mm_unpackhi_epi64(v32[1].val[1], v32[3].val[1]);
            #else
    ov[0] = LD128(ip    ); VE128(ov[0],sv); ov[0] = _mm_shuffle_epi8(ov[0], sf);
    ov[1] = LD128(ip+ 16); VE128(ov[1],sv); ov[1] = _mm_shuffle_epi8(ov[1], sf);
    ov[2] = LD128(ip+ 32); VE128(ov[2],sv); ov[2] = _mm_shuffle_epi8(ov[2], sf);
    ov[3] = LD128(ip+ 48); VE128(ov[3],sv); ov[3] = _mm_shuffle_epi8(ov[3], sf);
    ov[4] = LD128(ip+ 64); VE128(ov[4],sv); ov[4] = _mm_shuffle_epi8(ov[4], sf);
    ov[5] = LD128(ip+ 80); VE128(ov[5],sv); ov[5] = _mm_shuffle_epi8(ov[5], sf);
    ov[6] = LD128(ip+ 96); VE128(ov[6],sv); ov[6] = _mm_shuffle_epi8(ov[6], sf);
    ov[7] = LD128(ip+112); VE128(ov[7],sv); ov[7] = _mm_shuffle_epi8(ov[7], sf);
    v16[0] = vzipl_u16(ov[0], ov[1]); v16[1] = vziph_u16(ov[0], ov[1]);
    v16[2] = vzipl_u16(ov[2], ov[3]); v16[3] = vziph_u16(ov[2], ov[3]);
    v16[4] = vzipl_u16(ov[4], ov[5]); v16[5] = vziph_u16(ov[4], ov[5]);
    v16[6] = vzipl_u16(ov[6], ov[7]); v16[7] = vziph_u16(ov[6], ov[7]);

    v32[0] = vzip_u32(vreinterpret_u32_u16(v16[0].val[0]), vreinterpret_u32_u16(v16[2].val[0]) );
    v32[1] = vzip_u32(vreinterpret_u32_u16(v16[0].val[1]), vreinterpret_u32_u16(v16[2].val[1]) );
    v32[2] = vzip_u32(vreinterpret_u32_u16(v16[1].val[0]), vreinterpret_u32_u16(v16[3].val[0]) );
    v32[3] = vzip_u32(vreinterpret_u32_u16(v16[1].val[1]), vreinterpret_u32_u16(v16[3].val[1]) );
    v32[4] = vzip_u32(vreinterpret_u32_u16(v16[4].val[0]), vreinterpret_u32_u16(v16[6].val[0]) );
    v32[5] = vzip_u32(vreinterpret_u32_u16(v16[4].val[1]), vreinterpret_u32_u16(v16[6].val[1]) );
    v32[6] = vzip_u32(vreinterpret_u32_u16(v16[5].val[0]), vreinterpret_u32_u16(v16[7].val[0]) );
    v32[7] = vzip_u32(vreinterpret_u32_u16(v16[5].val[1]), vreinterpret_u32_u16(v16[7].val[1]) );

    iv[0] = (__m128i)vcombine_u64(vreinterpret_u64_u32(v32[0].val[0]), vreinterpret_u64_u32(v32[4].val[0]) );
    iv[1] = (__m128i)vcombine_u64(vreinterpret_u64_u32(v32[0].val[1]), vreinterpret_u64_u32(v32[4].val[1]) );
    iv[2] = (__m128i)vcombine_u64(vreinterpret_u64_u32(v32[1].val[0]), vreinterpret_u64_u32(v32[5].val[0]) );
    iv[3] = (__m128i)vcombine_u64(vreinterpret_u64_u32(v32[1].val[1]), vreinterpret_u64_u32(v32[5].val[1]) );

    iv[4] = (__m128i)vcombine_u64(vreinterpret_u64_u32(v32[2].val[0]), vreinterpret_u64_u32(v32[6].val[0]) );
    iv[5] = (__m128i)vcombine_u64(vreinterpret_u64_u32(v32[2].val[1]), vreinterpret_u64_u32(v32[6].val[1]) );
    iv[6] = (__m128i)vcombine_u64(vreinterpret_u64_u32(v32[3].val[0]), vreinterpret_u64_u32(v32[7].val[0]) );
    iv[7] = (__m128i)vcombine_u64(vreinterpret_u64_u32(v32[3].val[1]), vreinterpret_u64_u32(v32[7].val[1]) );
            #endif
            #if STRIDE <= ESIZE
    ST0(p,iv[0]); ST(p,iv[1],1); ST(p,iv[2],2); ST(p,iv[3],3); ST(p,iv[4],4); ST(p,iv[5],5); ST(p,iv[6],6); ST(p,iv[7],7);
            #endif
          #else // SSE
    ov[0] = LD128(ip   ); VE128(ov[0],sv); ov[0] = _mm_shuffle_epi8(ov[0], sf);
    ov[1] = LD128(ip+16); VE128(ov[1],sv); ov[1] = _mm_shuffle_epi8(ov[1], sf);
    ov[2] = LD128(ip+32); VE128(ov[2],sv); ov[2] = _mm_shuffle_epi8(ov[2], sf);
    ov[3] = LD128(ip+48); VE128(ov[3],sv); ov[3] = _mm_shuffle_epi8(ov[3], sf);

    iv[0] = _mm_unpacklo_epi16(ov[0], ov[1]); iv[1] = _mm_unpackhi_epi16(ov[0], ov[1]);
    iv[2] = _mm_unpacklo_epi16(ov[2], ov[3]); iv[3] = _mm_unpackhi_epi16(ov[2], ov[3]);

    ov[0] = _mm_unpacklo_epi32(iv[0], iv[2]); ov[1] = _mm_unpackhi_epi32(iv[0], iv[2]);
    ov[2] = _mm_unpacklo_epi32(iv[1], iv[3]); ov[3] = _mm_unpackhi_epi32(iv[1], iv[3]);

    ov[4] = LD128(ip+ 64); VE128(ov[4],sv); ov[4] = _mm_shuffle_epi8(ov[4], sf);
    ov[5] = LD128(ip+ 80); VE128(ov[5],sv); ov[5] = _mm_shuffle_epi8(ov[5], sf);
    ov[6] = LD128(ip+ 96); VE128(ov[6],sv); ov[6] = _mm_shuffle_epi8(ov[6], sf);
    ov[7] = LD128(ip+112); VE128(ov[7],sv); ov[7] = _mm_shuffle_epi8(ov[7], sf);

    iv[4] = _mm_unpacklo_epi16(ov[4], ov[5]); iv[5] = _mm_unpackhi_epi16(ov[4], ov[5]);
    iv[6] = _mm_unpacklo_epi16(ov[6], ov[7]); iv[7] = _mm_unpackhi_epi16(ov[6], ov[7]);

    ov[4] = _mm_unpacklo_epi32(iv[4], iv[6]); ov[5] = _mm_unpackhi_epi32(iv[4], iv[6]);
    ov[6] = _mm_unpacklo_epi32(iv[5], iv[7]); ov[7] = _mm_unpackhi_epi32(iv[5], iv[7]);

    iv[0] = _mm_unpacklo_epi64(ov[0], ov[4]); iv[1] = _mm_unpackhi_epi64(ov[0], ov[4]);
    iv[2] = _mm_unpacklo_epi64(ov[1], ov[5]); iv[3] = _mm_unpackhi_epi64(ov[1], ov[5]);

    iv[4] = _mm_unpacklo_epi64(ov[2], ov[6]); iv[5] = _mm_unpackhi_epi64(ov[2], ov[6]);
    iv[6] = _mm_unpacklo_epi64(ov[3], ov[7]); iv[7] = _mm_unpackhi_epi64(ov[3], ov[7]);
             #if STRIDE <= ESIZE
    ST0(p,iv[0]); ST(p,iv[1],1); ST(p,iv[2],2); ST(p,iv[3],3); ST(p,iv[4],4); ST(p,iv[5],5); ST(p,iv[6],6); ST(p,iv[7],7);
            #endif
          #endif
        #endif

      #elif defined(__SSE3__)
        #if ESIZE == 2
    iv[0] = LD128(ip   );  VE128(iv[0],sv);
	iv[1] = LD128(ip+16)); VE128(iv[1],sv);

    ov[0] = _mm_unpacklo_epi8(iv[0], iv[1]); ov[1] = _mm_unpackhi_epi8(iv[0], iv[1]);
    iv[0] = _mm_unpacklo_epi8(ov[0], ov[1]); iv[1] = _mm_unpackhi_epi8(ov[0], ov[1]);

    ov[0] = _mm_unpacklo_epi8(iv[0], iv[1]); ov[1] = _mm_unpackhi_epi8(iv[0], iv[1]);
    iv[0] = _mm_unpacklo_epi8(ov[0], ov[1]); iv[1] = _mm_unpackhi_epi8(ov[0], ov[1]);
    ST0(p,iv[0]); ST(p,iv[1],1);
        #elif ESIZE == 4
    iv[0] = LD128(ip   ); VE128(iv[0],sv);
	iv[1] = LD128(ip+16); VE128(iv[1],sv);
	iv[2] = LD128(ip+32); VE128(iv[2],sv);
	iv[3] = LD128(ip+48); VE128(iv[3],sv);

    ov[0] = _mm_unpacklo_epi8( iv[0], iv[1]); ov[1] = _mm_unpackhi_epi8( iv[0], iv[1]);
    iv[0] = _mm_unpacklo_epi8( ov[0], ov[1]); iv[1] = _mm_unpackhi_epi8( ov[0], ov[1]);

    ov[0] = _mm_unpacklo_epi8( iv[0], iv[1]); ov[1] = _mm_unpackhi_epi8( iv[0], iv[1]);
    iv[0] = _mm_unpacklo_epi64(ov[0], ov[2]); iv[1] = _mm_unpackhi_epi64(ov[0], ov[2]);

    ov[2] = _mm_unpacklo_epi8( iv[2], iv[3]); ov[3] = _mm_unpackhi_epi8( iv[2], iv[3]);
    iv[2] = _mm_unpacklo_epi8( ov[2], ov[3]); iv[3] = _mm_unpackhi_epi8( ov[2], ov[3]);
    ov[2] = _mm_unpacklo_epi8( iv[2], iv[3]); ov[3] = _mm_unpackhi_epi8( iv[2], iv[3]);

    iv[2] = _mm_unpacklo_epi64(ov[1], ov[3]); iv[3] = _mm_unpackhi_epi64(ov[1], ov[3]);
    ST0(p,iv[0]); ST(p,iv[1],1); ST(p,iv[2],2); ST(p,iv[3],3);
        #elif ESIZE == 8
    iv[0] = LD128(ip   ); VE128(iv[0],sv);
	iv[1] = LD128(ip+16); VE128(iv[1],sv);
	iv[2] = LD128(ip+32); VE128(iv[2],sv);
	iv[3] = LD128(ip+48); VE128(iv[2],sv);
    iv[4] = LD128(ip+64); VE128(iv[4],sv);
	iv[5] = LD128(ip+80); VE128(iv[5],sv);
	iv[6] = LD128(ip+96); VE128(iv[6],sv);
	iv[7] = LD128(ip+112);VE128(iv[7],sv);

    ov[0] = _mm_unpacklo_epi8( iv[0], iv[1]); ov[1] = _mm_unpackhi_epi8( iv[0], iv[1]);
    ov[2] = _mm_unpacklo_epi8( iv[2], iv[3]); ov[3] = _mm_unpackhi_epi8( iv[2], iv[3]);
    ov[4] = _mm_unpacklo_epi8( iv[4], iv[5]); ov[5] = _mm_unpackhi_epi8( iv[4], iv[5]);
    ov[6] = _mm_unpacklo_epi8( iv[6], iv[7]); ov[7] = _mm_unpackhi_epi8( iv[6], iv[7]);

    iv[0] = _mm_unpacklo_epi8( ov[0], ov[1]); iv[1] = _mm_unpackhi_epi8( ov[0], ov[1]);
    iv[2] = _mm_unpacklo_epi8( ov[2], ov[3]); iv[3] = _mm_unpackhi_epi8( ov[2], ov[3]);
    iv[4] = _mm_unpacklo_epi8( ov[4], ov[5]); iv[5] = _mm_unpackhi_epi8( ov[4], ov[5]);
    iv[6] = _mm_unpacklo_epi8( ov[6], ov[7]); iv[7] = _mm_unpackhi_epi8( ov[6], ov[7]);

    ov[0] = _mm_unpacklo_epi32(iv[0], iv[2]); ov[1] = _mm_unpackhi_epi32(iv[0], iv[2]);
    ov[2] = _mm_unpacklo_epi32(iv[1], iv[3]); ov[3] = _mm_unpackhi_epi32(iv[1], iv[3]);
    ov[4] = _mm_unpacklo_epi32(iv[4], iv[6]); ov[5] = _mm_unpackhi_epi32(iv[4], iv[6]);
    ov[6] = _mm_unpacklo_epi32(iv[5], iv[7]); ov[7] = _mm_unpackhi_epi32(iv[5], iv[7]);
    ST0(p,iv[0]); ST(p,iv[1],1); ST(p,iv[2],2); ST(p,iv[3],3);

    iv[0] = _mm_unpacklo_epi64(ov[0], ov[4]); iv[1] = _mm_unpackhi_epi64(ov[0], ov[4]);
    iv[2] = _mm_unpacklo_epi64(ov[1], ov[5]); iv[3] = _mm_unpackhi_epi64(ov[1], ov[5]);
    iv[4] = _mm_unpacklo_epi64(ov[2], ov[6]); iv[5] = _mm_unpackhi_epi64(ov[2], ov[6]);
    iv[6] = _mm_unpacklo_epi64(ov[3], ov[7]); iv[7] = _mm_unpackhi_epi64(ov[3], ov[7]);
    ST(p,iv[4],4);
	ST(p,iv[5],5);
	ST(p,iv[6],6);
	ST(p,iv[7],7);
        #endif
      #endif

      #if STRIDE > ESIZE // ---------------------- Nibble -------------------------------------------
    #define STL(_p_,_v_,_i_)  _mm_storel_epi64((__m128i *)SIE(_p_,_i_), _v_)
    #define STL0(_p_,_v_)     _mm_storel_epi64((__m128i *)(_p_), _v_)

    ov[0] = _mm_and_si128(iv[0], cl);                   ov[0] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[0],4), ov[0]),cb); ov[0] = _mm_packus_epi16(ov[0], _mm_srli_si128(ov[0],2));
    ov[1] = _mm_srli_epi16(_mm_and_si128(iv[0], ch),4); ov[1] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[1],4), ov[1]),cb); ov[1] = _mm_packus_epi16(ov[1], _mm_srli_si128(ov[1],2));
    ov[2] = _mm_and_si128(iv[1], cl);                   ov[2] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[2],4), ov[2]),cb); ov[2] = _mm_packus_epi16(ov[2], _mm_srli_si128(ov[2],2));
    ov[3] = _mm_srli_epi16(_mm_and_si128(iv[1], ch),4); ov[3] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[3],4), ov[3]),cb); ov[3] = _mm_packus_epi16(ov[3], _mm_srli_si128(ov[3],2));
    STL0(p,ov[0]); STL(p,ov[1],1);STL(p,ov[2],2);STL(p,ov[3],3);
        #if ESIZE > 2
    ov[0] = _mm_and_si128(iv[2], cl);                   ov[0] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[0],4), ov[0]),cb); ov[0] = _mm_packus_epi16(ov[0], _mm_srli_si128(ov[0],2));
    ov[1] = _mm_srli_epi16(_mm_and_si128(iv[2], ch),4); ov[1] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[1],4), ov[1]),cb); ov[1] = _mm_packus_epi16(ov[1], _mm_srli_si128(ov[1],2));
    ov[2] = _mm_and_si128(iv[3], cl);                   ov[2] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[2],4), ov[2]),cb); ov[2] = _mm_packus_epi16(ov[2], _mm_srli_si128(ov[2],2));
    ov[3] = _mm_srli_epi16(_mm_and_si128(iv[3], ch),4); ov[3] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[3],4), ov[3]),cb); ov[3] = _mm_packus_epi16(ov[3], _mm_srli_si128(ov[3],2));
    STL(p,ov[0],4); STL(p,ov[1],5);STL(p,ov[2],6);STL(p,ov[3],7);
          #if ESIZE > 4
    ov[0] = _mm_and_si128(iv[4], cl);                   ov[0] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[0],4), ov[0]),cb); ov[0] = _mm_packus_epi16(ov[0], _mm_srli_si128(ov[0],2));
    ov[1] = _mm_srli_epi16(_mm_and_si128(iv[4], ch),4); ov[1] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[1],4), ov[1]),cb); ov[1] = _mm_packus_epi16(ov[1], _mm_srli_si128(ov[1],2));
    ov[2] = _mm_and_si128(iv[5], cl);                   ov[2] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[2],4), ov[2]),cb); ov[2] = _mm_packus_epi16(ov[2], _mm_srli_si128(ov[2],2));
    ov[3] = _mm_srli_epi16(_mm_and_si128(iv[5], ch),4); ov[3] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[3],4), ov[3]),cb); ov[3] = _mm_packus_epi16(ov[3], _mm_srli_si128(ov[3],2));
    STL(p,ov[0],8); STL(p,ov[1],9);STL(p,ov[2],10);STL(p,ov[3],11);

    ov[4] = _mm_and_si128(iv[6], cl);                   ov[4] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[4],4), ov[4]),cb); ov[4] = _mm_packus_epi16(ov[4], _mm_srli_si128(ov[4],2));
    ov[5] = _mm_srli_epi16(_mm_and_si128(iv[6], ch),4); ov[5] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[5],4), ov[5]),cb); ov[5] = _mm_packus_epi16(ov[5], _mm_srli_si128(ov[5],2));
    ov[6] = _mm_and_si128(iv[7], cl);                   ov[6] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[6],4), ov[6]),cb); ov[6] = _mm_packus_epi16(ov[6], _mm_srli_si128(ov[6],2));
    ov[7] = _mm_srli_epi16(_mm_and_si128(iv[7], ch),4); ov[7] = _mm_and_si128(_mm_or_si128(_mm_srli_epi16(ov[7],4), ov[7]),cb); ov[7] = _mm_packus_epi16(ov[7], _mm_srli_si128(ov[7],2));
    STL(p,ov[4],12);
	STL(p,ov[5],13);
	STL(p,ov[6],14);
	STL(p,ov[7],15);
          #endif
        #endif
      #endif
  }
  T2(tpenc,ESIZE)(in+v, n-v, out+v);
}

void T2(TPDEC128V, ESIZE)(unsigned char *in, unsigned n, unsigned char *out) {
  unsigned           v = n&~(ESIZE*32-1);
  unsigned      stride = v/STRIDE;
  unsigned char *op,*ip;

    #if STRIDE > ESIZE
  __m128i cl = _mm_set1_epi8(0x0f), ch=_mm_set1_epi8(0xf0u), cb = _mm_set1_epi16(0xff);
    #endif
  VDINI128;
  for(op = out,ip = in; op != out+v; op+=ESIZE*16,ip += ESIZE*16/STRIDE) {
    unsigned char *p=ip;                                                        PREFETCH(ip+(ESIZE*16/STRIDE)*ESIZE,0);
    __m128i iv[ESIZE], ov[ESIZE == 2 ? ESIZE + 2 : ESIZE];

      #if STRIDE > ESIZE //------------ Nibble transpose -------------------
    ov[0] = _mm_loadl_epi64((__m128i *)    p   );
    ov[1] = _mm_loadl_epi64((__m128i *)SID(p,1));
    ov[2] = _mm_loadl_epi64((__m128i *)SID(p,2));
    ov[3] = _mm_loadl_epi64((__m128i *)SID(p,3));

    ov[0] = _mm_unpacklo_epi8(ov[0], _mm_srli_epi16(ov[0],4)); ov[0] = _mm_and_si128(ov[0], cl); // 0,1->0
    ov[1] = _mm_unpacklo_epi8(ov[1], _mm_srli_epi16(ov[1],4)); ov[1] = _mm_and_si128(ov[1], cl);
    iv[0] = _mm_or_si128(_mm_slli_epi16(ov[1],4), ov[0]);

    ov[2] = _mm_unpacklo_epi8(ov[2], _mm_srli_epi16(ov[2],4)); ov[2] = _mm_and_si128(ov[2], cl); // 2,3->1
    ov[3] = _mm_unpacklo_epi8(ov[3], _mm_srli_epi16(ov[3],4)); ov[3] = _mm_and_si128(ov[3], cl);
    iv[1] = _mm_or_si128(_mm_slli_epi16(ov[3],4), ov[2]);
        #if ESIZE > 2
    ov[0] = _mm_loadl_epi64((__m128i *)SID(p,4));
    ov[1] = _mm_loadl_epi64((__m128i *)SID(p,5));
    ov[2] = _mm_loadl_epi64((__m128i *)SID(p,6));
    ov[3] = _mm_loadl_epi64((__m128i *)SID(p,7));

    ov[0] = _mm_unpacklo_epi8(ov[0], _mm_srli_epi16(ov[0],4)); ov[0] = _mm_and_si128(ov[0], cl); // 0,1->2
    ov[1] = _mm_unpacklo_epi8(ov[1], _mm_srli_epi16(ov[1],4)); ov[1] = _mm_and_si128(ov[1], cl);
    iv[2] = _mm_or_si128(_mm_slli_epi16(ov[1],4), ov[0]);

    ov[2] = _mm_unpacklo_epi8(ov[2], _mm_srli_epi16(ov[2],4)); ov[2] = _mm_and_si128(ov[2], cl); // 2,3->3
    ov[3] = _mm_unpacklo_epi8(ov[3], _mm_srli_epi16(ov[3],4)); ov[3] = _mm_and_si128(ov[3], cl);
    iv[3] = _mm_or_si128(_mm_slli_epi16(ov[3],4), ov[2]);
        #endif
        #if ESIZE > 4
    ov[0] = _mm_loadl_epi64((__m128i *)SID(p,8));
    ov[1] = _mm_loadl_epi64((__m128i *)SID(p,9));
    ov[2] = _mm_loadl_epi64((__m128i *)SID(p,10));
    ov[3] = _mm_loadl_epi64((__m128i *)SID(p,11));

    ov[0] = _mm_unpacklo_epi8(ov[0], _mm_srli_epi16(ov[0],4)); ov[0] = _mm_and_si128(ov[0], cl); // 0,1->4
    ov[1] = _mm_unpacklo_epi8(ov[1], _mm_srli_epi16(ov[1],4)); ov[1] = _mm_and_si128(ov[1], cl);
    iv[4] = _mm_or_si128(_mm_slli_epi16(ov[1],4), ov[0]);

    ov[2] = _mm_unpacklo_epi8(ov[2], _mm_srli_epi16(ov[2],4)); ov[2] = _mm_and_si128(ov[2], cl); // 2,3->5
    ov[3] = _mm_unpacklo_epi8(ov[3], _mm_srli_epi16(ov[3],4));
    ov[3] = _mm_and_si128(ov[3], cl);
    iv[5] = _mm_or_si128(_mm_slli_epi16(ov[3],4), ov[2]);

    ov[0] = _mm_loadl_epi64((__m128i *)SID(p,12));
    ov[1] = _mm_loadl_epi64((__m128i *)SID(p,13));
    ov[2] = _mm_loadl_epi64((__m128i *)SID(p,14));
    ov[3] = _mm_loadl_epi64((__m128i *)SID(p,15));

    ov[0] = _mm_unpacklo_epi8(ov[0], _mm_srli_epi16(ov[0],4)); ov[0] = _mm_and_si128(ov[0], cl); // 0,1->6
    ov[1] = _mm_unpacklo_epi8(ov[1], _mm_srli_epi16(ov[1],4)); ov[1] = _mm_and_si128(ov[1], cl);
    iv[6] = _mm_or_si128(_mm_slli_epi16(ov[1],4), ov[0]);

    ov[2] = _mm_unpacklo_epi8(ov[2], _mm_srli_epi16(ov[2],4)); ov[2] = _mm_and_si128(ov[2], cl); // 2,3->7
    ov[3] = _mm_unpacklo_epi8(ov[3], _mm_srli_epi16(ov[3],4)); ov[3] = _mm_and_si128(ov[3], cl);
    iv[7] = _mm_or_si128(_mm_slli_epi16(ov[3],4), ov[2]);
        #endif
      #else // --------------------------- Byte transpose -------------------
    iv[0] = _mm_loadu_si128((__m128i *)    p   );
    iv[1] = _mm_loadu_si128((__m128i *)SID(p,1));
        #if ESIZE > 2
    iv[2] = _mm_loadu_si128((__m128i *)SID(p,2));
    iv[3] = _mm_loadu_si128((__m128i *)SID(p,3));
          #if ESIZE > 4
    iv[4] = _mm_loadu_si128((__m128i *)SID(p,4));
    iv[5] = _mm_loadu_si128((__m128i *)SID(p,5));
    iv[6] = _mm_loadu_si128((__m128i *)SID(p,6));
    iv[7] = _mm_loadu_si128((__m128i *)SID(p,7));
          #endif
        #endif
      #endif
      #if ESIZE == 2
        #ifdef __ARM_NEON
    uint8x16x2_t w; w.val[0] = (uint8x16_t)iv[0];
                    w.val[1] = (uint8x16_t)iv[1]; vst2q_u8(op, w);
        #else
    ov[0] = _mm_unpacklo_epi8(iv[0], iv[1]); ov[1] = _mm_unpackhi_epi8(iv[0], iv[1]);//i(0,1)->o(0,1)
    VD128(ov[0],sv); ST128(op,   ov[0]);
	VD128(ov[1],sv); ST128(op+16,ov[1]);
        #endif
      #elif ESIZE == 4
        #ifdef __ARM_NEON
    uint8x16x4_t w; w.val[0] = (uint8x16_t)iv[0];
                    w.val[1] = (uint8x16_t)iv[1];
                    w.val[2] = (uint8x16_t)iv[2];
                    w.val[3] = (uint8x16_t)iv[3]; vst4q_u8(op,w);
        #else
    ov[0] = _mm_unpacklo_epi8( iv[0], iv[1]); ov[1] = _mm_unpackhi_epi8(iv[0], iv[1]); //i(0,1)->o(0,1)
    ov[2] = _mm_unpacklo_epi8( iv[2], iv[3]); ov[3] = _mm_unpackhi_epi8(iv[2], iv[3]); //i(2,3)->o(2,3)

    iv[0] = _mm_unpacklo_epi16(ov[0], ov[2]); iv[1] = _mm_unpackhi_epi16(ov[0], ov[2]);//o(0,2)->i(0,1)
    iv[2] = _mm_unpacklo_epi16(ov[1], ov[3]); iv[3] = _mm_unpackhi_epi16(ov[1], ov[3]);//o(1,3)->i(2,3)
    VD128(iv[0],sv); ST128(op,   iv[0]);
	VD128(iv[1],sv); ST128(op+16,iv[1]);
	VD128(iv[2],sv); ST128(op+32,iv[2]);
	VD128(iv[3],sv); ST128(op+48,iv[3]);
        #endif
      #else
    ov[0] = _mm_unpacklo_epi8( iv[0], iv[1]); ov[1] = _mm_unpackhi_epi8( iv[0], iv[1]);//i(0,1)->o(0,1)
    ov[2] = _mm_unpacklo_epi8( iv[2], iv[3]); ov[3] = _mm_unpackhi_epi8( iv[2], iv[3]);//i(2,3)->o(2,3)
    ov[4] = _mm_unpacklo_epi8( iv[4], iv[5]); ov[5] = _mm_unpackhi_epi8( iv[4], iv[5]);//i(4,5)->o(4,5)
    ov[6] = _mm_unpacklo_epi8( iv[6], iv[7]); ov[7] = _mm_unpackhi_epi8( iv[6], iv[7]);//i(6,7)->o(6,7)

    iv[0] = _mm_unpacklo_epi16(ov[0], ov[2]); iv[1] = _mm_unpackhi_epi16(ov[0], ov[2]);
    iv[2] = _mm_unpacklo_epi16(ov[1], ov[3]); iv[3] = _mm_unpackhi_epi16(ov[1], ov[3]);
    iv[4] = _mm_unpacklo_epi16(ov[4], ov[6]); iv[5] = _mm_unpackhi_epi16(ov[4], ov[6]);
    iv[6] = _mm_unpacklo_epi16(ov[5], ov[7]); iv[7] = _mm_unpackhi_epi16(ov[5], ov[7]);

    ov[0] = _mm_unpacklo_epi32(iv[0], iv[4]); ov[1] = _mm_unpackhi_epi32(iv[0], iv[4]);
    ov[2] = _mm_unpacklo_epi32(iv[1], iv[5]); ov[3] = _mm_unpackhi_epi32(iv[1], iv[5]);
    ov[4] = _mm_unpacklo_epi32(iv[2], iv[6]); ov[5] = _mm_unpackhi_epi32(iv[2], iv[6]);
    ov[6] = _mm_unpacklo_epi32(iv[3], iv[7]); ov[7] = _mm_unpackhi_epi32(iv[3], iv[7]);

    VD128(ov[0],sv); ST128(op,    ov[0]);
	VD128(ov[1],sv); ST128(op+16, ov[1]);
	VD128(ov[2],sv); ST128(op+32, ov[2]);
	VD128(ov[3],sv); ST128(op+48, ov[3]);
    VD128(ov[4],sv); ST128(op+64, ov[4]);
	VD128(ov[5],sv); ST128(op+80, ov[5]);
	VD128(ov[6],sv); ST128(op+96, ov[6]);
	VD128(ov[7],sv); ST128(op+112,ov[7]);
      #endif
  }
  T2(tpdec,ESIZE)(in+v, n-v, out+v);
}
    #endif // SSE3

    //--------------------------------------- plain -------------------------------------------------------------------
    #if STRIDE == ESIZE // bytes only, no nibble version
      #if (ESIZE == 2 || ESIZE == 4 || ESIZE == 8) && !defined(ISDELTA)
#define uint_t T3(uint, USIZE, _t)

#define ODX2 (x + y * nx)
#define O2D(_i_) (x + (y+_i_) * nx)
void T2(tp2denc,ESIZE)(unsigned char *in, unsigned nx, unsigned ny, unsigned char *out) {
  unsigned x,y;
  uint_t *op = (uint_t *)out, *ip = (uint_t *)in;

  for(  x = 0; x < nx; x++)
    for(y = 0; y < ny; y++)
      op[ODX2] = *ip++;
}

void T2(tp2ddec,ESIZE)(unsigned char *in, unsigned nx, unsigned ny, unsigned char *out) {
  unsigned x, y;
  uint_t   *op = (uint_t *)out, *ip = (uint_t *)in;

  for(  x = 0; x < nx; x++)
    for(y=0; y != ny; y++)
      *op++ = ip[ODX2];
}
#undef ODX2

#define ODX3 (x + y * nx + z * ny * nx)
void T2(tp3denc,ESIZE)(unsigned char *in, unsigned nx, unsigned ny, unsigned nz, unsigned char *out) {
  unsigned x, y, z;
  uint_t   *op = (uint_t *)out, *ip = (uint_t *)in;

  for(    x = 0; x < nx; x++)
    for(  y = 0; y < ny; y++)
      for(z = 0; z < nz; z++)
        op[ODX3] = *ip++;
}

void T2(tp3ddec,ESIZE)(unsigned char *in, unsigned nx, unsigned ny, unsigned nz, unsigned char *out) {
  unsigned x,y,z;
  uint_t   *op = (uint_t *)out, *ip = (uint_t *)in;

  for(x = 0; x < nx; ++x)
    for(y = 0; y < ny; ++y)
      for(z = 0; z < nz; ++z)
        *op++ = ip[ODX3];
}
#undef ODX3

#define ODX4 (w + x * nw + y * nx * nw + z * nx * ny * nw)
void T2(tp4denc,ESIZE)(unsigned char *in, unsigned nw, unsigned nx, unsigned ny, unsigned nz, unsigned char *out) {
  unsigned w,x,y,z;
  uint_t *op = (uint_t *)out, *ip = (uint_t *)in;

  for(      w = 0; w < nw; w++)
    for(    x = 0; x < nx; x++)
      for(  y = 0; y < ny; y++)
        for(z = 0; z < nz; z++)
          op[ODX4] = *ip++;
}

void T2(tp4ddec,ESIZE)(unsigned char *in, unsigned nw, unsigned nx, unsigned ny, unsigned nz, unsigned char *out) {
  unsigned w,x,y,z;
  uint_t *op = (uint_t *)out, *ip = (uint_t *)in;

  for(      w = 0; w < nw; ++w)
    for(    x = 0; x < nx; ++x)
      for(  y = 0; y < ny; ++y)
        for(z = 0; z < nz; ++z)
          *op++= ip[ODX4];
}
#undef ODX4
      #endif // ISDELTA

void T2(TPENC, ESIZE)(unsigned char *in, unsigned n, unsigned char *out) {
  unsigned char *op,*ip,*e;
  unsigned stride = n/STRIDE;

    #if powof2(ESIZE)
  e = in+(n&~(ESIZE-1));
    #else
  e = in+stride*ESIZE;
    #endif

  for(ip = in,op = out; ip < e; op++, ip+=ESIZE) { unsigned char *p = op;
    p[0]      = ip[ 0];
    *SIE(p, 1) = ip[ 1];
      #if ESIZE > 2
    *SIE(p, 2) = ip[ 2];
        #if ESIZE > 3
    *SIE(p, 3) = ip[ 3];
          #if ESIZE > 4
    uint32_t u = ctou32(p);
    *SIE(p, 4) = ip[ 4];
    *SIE(p, 5) = ip[ 5];
    *SIE(p, 6) = ip[ 6];
    *SIE(p, 7) = ip[ 7];
            #if ESIZE > 8
    *SIE(p, 8) = ip[ 8];
    *SIE(p, 9) = ip[ 9];
    *SIE(p,10) = ip[10];
    *SIE(p,11) = ip[11];
    *SIE(p,12) = ip[12];
    *SIE(p,13) = ip[13];
    *SIE(p,14) = ip[14];
    *SIE(p,15) = ip[15];
            #endif
          #endif
        #endif
      #endif
  }
  for(op = out+stride*ESIZE;ip < in+n;)
    *op++ = *ip++;
}

void T2(TPDEC, ESIZE)(unsigned char *in, unsigned n, unsigned char *out) {
  unsigned char *op,*ip,*e;
  unsigned      stride = n/STRIDE;

    #if powof2(ESIZE)
  e = out+(n&~(ESIZE-1));
    #else
  e = out+stride*ESIZE;
    #endif
  for(op = out,ip = in; op < e; ip++,op += ESIZE) { unsigned char *p = ip;
    op[ 0] = *p;
    op[ 1] = *SID(p,1);
      #if ESIZE > 2
    op[ 2] = *SID(p,2);
        #if ESIZE > 3
    op[ 3] = *SID(p,3);
          #if ESIZE > 4
    op[ 4] = *SID(p,4);
    op[ 5] = *SID(p,5);
    op[ 6] = *SID(p,6);
    op[ 7] = *SID(p,7);
            #if ESIZE > 8
    op[ 8] = *SID(p,8);
    op[ 9] = *SID(p,9);
    op[10] = *SID(p,10);
    op[11] = *SID(p,11);
    op[12] = *SID(p,12);
    op[13] = *SID(p,13);
    op[14] = *SID(p,14);
    op[15] = *SID(p,15);
            #endif
          #endif
        #endif
      #endif
  }
  for(ip = in+stride*ESIZE; op < out+n; )
    *op++ = *ip++;
}
    #endif // STRIDE = ESIZE

  #endif // avx2
#endif // template
