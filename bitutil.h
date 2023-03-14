/**
    Copyright (C) powturbo 2013-2019
    GPL v2 License

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
//     "Integer Compression: max.bits, delta, zigzag, xor"

#ifndef _BITUTIL_H_
#define _BITUTIL_H_

//---------- max. bit length + transform for sorted/unsorted arrays, delta,delta 1, delta > 1, zigzag, zigzag of delta, xor, FOR,----------------
#ifdef __cplusplus
extern "C" {
#endif
//------ ORed array, used to determine the maximum bit length of the elements in an unsorted integer array ---------------------
uint8_t  bit8( uint8_t  *in, unsigned n, uint8_t  *px);
uint16_t bit16(uint16_t *in, unsigned n, uint16_t *px);
uint32_t bit32(uint32_t *in, unsigned n, uint32_t *px);
uint64_t bit64(uint64_t *in, unsigned n, uint64_t *px);

//-------------- delta = 0: Sorted integer array w/ mindelta = 0 ----------------------------------------------
//-- ORed array, maximum bit length of the non decreasing integer array. out[i] = in[i] - in[i-1]
uint8_t  bitd8( uint8_t  *in, unsigned n, uint8_t  *px, uint8_t  start);
uint16_t bitd16(uint16_t *in, unsigned n, uint16_t *px, uint16_t start);
uint32_t bitd32(uint32_t *in, unsigned n, uint32_t *px, uint32_t start);
uint64_t bitd64(uint64_t *in, unsigned n, uint64_t *px, uint64_t start);

//-- in-place reverse delta 0
void bitddec8(  uint8_t  *p,  unsigned n, uint8_t  start); // non decreasing (out[i] = in[i] - in[i-1])
void bitddec16( uint16_t *p,  unsigned n, uint16_t start);
void bitddec32( uint32_t *p,  unsigned n, uint32_t start);
void bitddec64( uint64_t *p,  unsigned n, uint64_t start);

//-- vectorized fast delta4 one: out[0] = in[4]-in[0], out[1]=in[5]-in[1], out[2]=in[6]-in[2], out[3]=in[7]-in[3],...
uint16_t bits128v16(   uint16_t *in, unsigned n, uint16_t *px, uint16_t start);
uint32_t bits128v32(   uint32_t *in, unsigned n, uint32_t *px, uint32_t start);

//------------- delta = 1: Sorted integer array w/ mindelta = 1 ---------------------------------------------
//-- get delta maximum bit length of the non strictly decreasing integer array. out[i] = in[i] - in[i-1] - 1
uint8_t  bitd18( uint8_t  *in, unsigned n, uint8_t  *px, uint8_t  start);
uint16_t bitd116(uint16_t *in, unsigned n, uint16_t *px, uint16_t start);
uint32_t bitd132(uint32_t *in, unsigned n, uint32_t *px, uint32_t start);
uint64_t bitd164(uint64_t *in, unsigned n, uint64_t *px, uint64_t start);

//-- in-place reverse delta one
void bitd1dec8(     uint8_t  *p,  unsigned n, uint8_t  start); // non strictly decreasing (out[i] = in[i] - in[i-1] - 1)
void bitd1dec16(    uint16_t *p,  unsigned n, uint16_t start);
void bitd1dec32(    uint32_t *p,  unsigned n, uint32_t start);
void bitd1dec64(    uint64_t *p,  unsigned n, uint64_t start);

//------------- delta > 1: Sorted integer array w/ mindelta > 1 ---------------------------------------------
//-- ORed array, for max. bit length get min. delta ()
uint8_t  bitdi8(    uint8_t  *in, unsigned n, uint8_t  *px,  uint8_t  start);
uint16_t bitdi16(   uint16_t *in, unsigned n, uint16_t *px,  uint16_t start);
uint32_t bitdi32(   uint32_t *in, unsigned n, uint32_t *px,  uint32_t start);
uint64_t bitdi64(   uint64_t *in, unsigned n, uint64_t *px,  uint64_t start);
//-- transform sorted integer array to delta array: out[i] = in[i] - in[i-1] - mindelta
uint8_t  bitdienc8( uint8_t  *in, unsigned n, uint8_t  *out, uint8_t  start, uint8_t  mindelta);
uint16_t bitdienc16(uint16_t *in, unsigned n, uint16_t *out, uint16_t start, uint16_t mindelta);
uint32_t bitdienc32(uint32_t *in, unsigned n, uint32_t *out, uint32_t start, uint32_t mindelta);
uint64_t bitdienc64(uint64_t *in, unsigned n, uint64_t *out, uint64_t start, uint64_t mindelta);
//-- in-place reverse delta
void     bitdidec8( uint8_t  *in, unsigned n,                uint8_t  start, uint8_t  mindelta);
void     bitdidec16(uint16_t *in, unsigned n,                uint16_t start, uint16_t mindelta);
void     bitdidec32(uint32_t *in, unsigned n,                uint32_t start, uint32_t mindelta);
void     bitdidec64(uint64_t *in, unsigned n,                uint64_t start, uint64_t mindelta);

//------------- FOR : array bit length: ---------------------------------------------------------------------
//------ ORed array, for max. bit length of the non decreasing integer array.  out[i] = in[i] - start
uint8_t  bitf8( uint8_t  *in, unsigned n, uint8_t  *px, uint8_t  start);
uint16_t bitf16(uint16_t *in, unsigned n, uint16_t *px, uint16_t start);
uint32_t bitf32(uint32_t *in, unsigned n, uint32_t *px, uint32_t start);
uint64_t bitf64(uint64_t *in, unsigned n, uint64_t *px, uint64_t start);

//------ ORed array, for max. bit length of the non strictly decreasing integer array out[i] = in[i] - 1 - start
uint8_t  bitf18( uint8_t  *in, unsigned n, uint8_t  *px, uint8_t  start);
uint16_t bitf116(uint16_t *in, unsigned n, uint16_t *px, uint16_t start);
uint32_t bitf132(uint32_t *in, unsigned n, uint32_t *px, uint32_t start);
uint64_t bitf164(uint64_t *in, unsigned n, uint64_t *px, uint64_t start);

//------ ORed array, for max. bit length for usorted array
uint8_t  bitfm8( uint8_t  *in, unsigned n, uint8_t  *px, uint8_t  *pmin);  // unsorted
uint16_t bitfm16(uint16_t *in, unsigned n, uint16_t *px, uint16_t *pmin);
uint32_t bitfm32(uint32_t *in, unsigned n, uint32_t *px, uint32_t *pmin);
uint64_t bitfm64(uint64_t *in, unsigned n, uint64_t *px, uint64_t *pmin);

//------------- Zigzag encoding for unsorted integer lists: out[i] = in[i] - in[i-1] ------------------------
//-- ORed array, to get maximum zigzag bit length integer array
uint8_t  bitz8(    uint8_t  *in, unsigned n, uint8_t  *px, uint8_t  start);
uint16_t bitz16(   uint16_t *in, unsigned n, uint16_t *px, uint16_t start);
uint32_t bitz32(   uint32_t *in, unsigned n, uint32_t *px, uint32_t start);
uint64_t bitz64(   uint64_t *in, unsigned n, uint64_t *px, uint64_t start);
//-- Zigzag transform
uint8_t  bitzenc8( uint8_t  *in, unsigned n, uint8_t  *out, uint8_t  start, uint8_t  mindelta);
uint16_t bitzenc16(uint16_t *in, unsigned n, uint16_t *out, uint16_t start, uint16_t mindelta);
uint32_t bitzenc32(uint32_t *in, unsigned n, uint32_t *out, uint32_t start, uint32_t mindelta);
uint64_t bitzenc64(uint64_t *in, unsigned n, uint64_t *out, uint64_t start, uint64_t mindelta);
//-- in-place zigzag reverse transform
void bitzdec8(     uint8_t  *in, unsigned n,                uint8_t  start);
void bitzdec16(    uint16_t *in, unsigned n,                uint16_t start);
void bitzdec32(    uint32_t *in, unsigned n,                uint32_t start);
void bitzdec64(    uint64_t *in, unsigned n,                uint64_t start);

//------------- Zigzag of zigzag/delta : unsorted/sorted integer array ----------------------------------------------------
//-- get delta maximum bit length of the non strictly decreasing integer array. out[i] = in[i] - in[i-1] - 1
uint8_t  bitzz8(    uint8_t  *in, unsigned n, uint8_t  *px, uint8_t  start);
uint16_t bitzz16(   uint16_t *in, unsigned n, uint16_t *px, uint16_t start);
uint32_t bitzz32(   uint32_t *in, unsigned n, uint32_t *px, uint32_t start);
uint64_t bitzz64(   uint64_t *in, unsigned n, uint64_t *px, uint64_t start);

uint8_t  bitzzenc8( uint8_t  *in, unsigned n, uint8_t  *out, uint8_t  start, uint8_t  mindelta);
uint16_t bitzzenc16(uint16_t *in, unsigned n, uint16_t *out, uint16_t start, uint16_t mindelta);
uint32_t bitzzenc32(uint32_t *in, unsigned n, uint32_t *out, uint32_t start, uint32_t mindelta);
uint64_t bitzzenc64(uint64_t *in, unsigned n, uint64_t *out, uint64_t start, uint64_t mindelta);

//-- in-place reverse zigzag of delta (encoded w/ bitdiencNN and parameter mindelta = 1)
void bitzzdec8(     uint8_t  *in,  unsigned n, uint8_t  start); // non strictly decreasing (out[i] = in[i] - in[i-1] - 1)
void bitzzdec16(    uint16_t *in,  unsigned n, uint16_t start);
void bitzzdec32(    uint32_t *in,  unsigned n, uint32_t start);
void bitzzdec64(    uint64_t *in,  unsigned n, uint64_t start);

//------------- XOR encoding for unsorted integer lists: out[i] = in[i] - in[i-1] -------------
//-- ORed array, to get maximum zigzag bit length integer array
uint8_t  bitx8(    uint8_t  *in, unsigned n, uint8_t  *px, uint8_t  start);
uint16_t bitx16(   uint16_t *in, unsigned n, uint16_t *px, uint16_t start);
uint32_t bitx32(   uint32_t *in, unsigned n, uint32_t *px, uint32_t start);
uint64_t bitx64(   uint64_t *in, unsigned n, uint64_t *px, uint64_t start);

//-- XOR transform
uint8_t  bitxenc8(  uint8_t  *in, unsigned n, uint8_t  *out, uint8_t  start);
uint16_t bitxenc16( uint16_t *in, unsigned n, uint16_t *out, uint16_t start);
uint32_t bitxenc32( uint32_t *in, unsigned n, uint32_t *out, uint32_t start);
uint64_t bitxenc64( uint64_t *in, unsigned n, uint64_t *out, uint64_t start);

//-- XOR in-place reverse transform
void bitxdec8(      uint8_t  *p,  unsigned n, uint8_t  start);
void bitxdec16(     uint16_t *p,  unsigned n, uint16_t start);
void bitxdec32(     uint32_t *p,  unsigned n, uint32_t start);
void bitxdec64(     uint64_t *p,  unsigned n, uint64_t start);

//------- Lossy floating point transform: pad the trailing mantissa bits with zeros according to the error e (ex. e=0.00001)
  #ifdef USE_FLOAT16
void fppad16(_Float16 *in, size_t n, _Float16  *out, float  e);
  #endif
void fppad32(float  *in, size_t n, float  *out, float  e);
void fppad64(double *in, size_t n, double *out, double e);

#ifdef __cplusplus
}
#endif

#endif // _BITUTIL_H_
