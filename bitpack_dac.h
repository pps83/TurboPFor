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
//     bitpack.h - "Integer Compression" Binary Packing header file
#ifndef BITPACK_DAC_H_
#define BITPACK_DAC_H_

// ---------------- Direct Access to a single packed integer array entry --------------------------------------------------------------
#include "conf.h"

static ALWAYS_INLINE unsigned  bitgetx32(const unsigned char *__restrict in, unsigned  idx, unsigned b) { unsigned bidx = b*idx; return bzhi64( ctou64((uint32_t *)in+(bidx>>5)) >> (bidx&0x1f), b ); }
//static ALWAYS_INLINE unsigned  bitgetx32(const unsigned char *__restrict in, unsigned  idx, unsigned b) { unsigned bidx = b*idx;
 //return (ctou64((uint32_t *)in+(bidx>>5)) << 32+(bidx&0x1f)) >> (64-b);
// return bzhi64( ctou64((uint32_t *)in+(bidx>>5)) >> (bidx&0x1f), b ); }
static ALWAYS_INLINE unsigned _bitgetx32(const unsigned char *__restrict in, uint64_t bidx, unsigned b) {                        return bzhi64( ctou64((uint32_t *)in+(bidx>>5)) >> (bidx&0x1f), b ); }

// like  bitgetx32 but for 16 bits integer array
static ALWAYS_INLINE unsigned  bitgetx8( const unsigned char *__restrict in, unsigned  idx, unsigned b) { unsigned bidx = b*idx; return bzhi32( ctou16((uint16_t *)in+(bidx>>4)) >> (bidx& 0xf), b ); }
static ALWAYS_INLINE unsigned _bitgetx8( const unsigned char *__restrict in, unsigned bidx, unsigned b) {                        return bzhi32( ctou16((uint16_t *)in+(bidx>>4)) >> (bidx& 0xf), b ); }
static ALWAYS_INLINE unsigned  bitgetx16(const unsigned char *__restrict in, unsigned  idx, unsigned b) { unsigned bidx = b*idx; return bzhi32( ctou32((uint32_t *)in+(bidx>>4)) >> (bidx& 0xf), b ); }
static ALWAYS_INLINE unsigned _bitgetx16(const unsigned char *__restrict in, unsigned bidx, unsigned b) {                        return bzhi32( ctou32((uint32_t *)in+(bidx>>4)) >> (bidx& 0xf), b ); }

// Set a single value with index "idx"
static ALWAYS_INLINE void      bitsetx16(const unsigned char *__restrict in, unsigned  idx, unsigned v, unsigned b) { unsigned bidx = b*idx;  unsigned           *p = (unsigned           *)             in+(bidx>>4) ; *p = ( *p & ~(((1u  <<b)-1) << (bidx& 0xf)) ) |                     v<<(bidx& 0xf);}
static ALWAYS_INLINE void      bitsetx32(const unsigned char *__restrict in, unsigned  idx, unsigned v, unsigned b) { unsigned bidx = b*idx;  unsigned long long *p = (unsigned long long *)((unsigned *)in+(bidx>>5)); *p = ( *p & ~(((1ull<<b)-1) << (bidx&0x1f)) ) | (unsigned long long)v<<(bidx&0x1f);}

#endif
