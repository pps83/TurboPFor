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
//  "TurboPFor: Integer Compression" PFor/PForDelta  + Direct access
#ifndef VP4_DAC_H_
#define VP4_DAC_H_

//---------------- Direct Access functions to compressed TurboPFor array p4encx16/p4encx32 -------------------------------------------------------
#include "vp4.h"
#include "conf.h"
#include "bitpack_dac.h"

#ifdef __cplusplus
extern "C" {
#endif

#define P4D_PAD8(_x_)       ( (((_x_)+8-1)/8) )
#define P4D_B(_x_)          ((_x_) & 0x7f)
#define P4D_XB(_x_)         (((_x_) & 0x80)?((_x_) >> 8):0)
#define P4D_ININC(_in_, _x_) _in_ += 1+((_x_) >> 7)

static inline unsigned p4bits(unsigned char *__restrict in, int *bx) { unsigned i = ctou16(in); *bx = P4D_XB(i); return P4D_B(i); }

struct p4 {
  unsigned long long *xmap;
  unsigned char *ex;
  unsigned isx,bx,cum[P4D_MAX/64+1];
  int oval,idx;
};

static unsigned long long p4xmap[P4D_MAX/64+1] = { 0 };

// prepare direct access usage
static inline void p4ini(struct p4 *p4, unsigned char **pin, unsigned n, unsigned *b) { unsigned char *in = *pin;
  unsigned p4i  = ctou16(in);
  p4->isx       = p4i&0x80;
  *b            = P4D_B(p4i);
  p4->bx        = P4D_XB(p4i);              //printf("p4i=%x,b=%d,bx=%d ", p4->i, *b, p4->bx);                        //assert(n <= P4D_MAX);
  *pin = p4->ex = ++in;
  if(p4->isx) {
    unsigned num=0,j;
    unsigned char *p;
    ++in;
    p4->xmap = (unsigned long long *)in;
    for(j=0; j < n/64; j++) { p4->cum[j] = num; num += popcnt64(ctou64(in+j*8)); }
    if(n & 0x3f) num += popcnt64(ctou64(in+j*8) & ((1ull<<(n&0x3f))-1) );
    p4->ex = p = in + (n+7)/8;
    *pin   = p = p4->ex+(((uint64_t)num*p4->bx+7)/8);
  } else p4->xmap = p4xmap;
  p4->oval = p4->idx  = -1;
}

//---------- Get a single value with index "idx" from a "p4encx32" packed array
static ALWAYS_INLINE uint8_t  p4getx8( struct p4 *p4, unsigned char *in, unsigned idx, unsigned b) { unsigned bi, cl, u = bitgetx8( in, idx, b);
  if(p4->xmap[bi=idx>>6] & (1ull<<(cl=idx&63))) u += bitgetx8(p4->ex, p4->cum[bi] + popcnt64(p4->xmap[bi] & ~(~0ull<<cl)), p4->bx) << b;
  return u;
}

static ALWAYS_INLINE uint16_t p4getx16(struct p4 *p4, unsigned char *in, unsigned idx, unsigned b) { unsigned bi, cl, u = bitgetx16(in, idx, b);
  if(p4->xmap[bi=idx>>6] & (1ull<<(cl=idx&63))) u += bitgetx16(p4->ex, p4->cum[bi] + popcnt64(p4->xmap[bi] & ~(~0ull<<cl)), p4->bx) << b;
  return u;
}
static ALWAYS_INLINE uint32_t p4getx32(struct p4 *p4, unsigned char *in, unsigned idx, unsigned b) { unsigned bi, cl, u = bitgetx32(in, idx, b);
  if(p4->xmap[bi=idx>>6] & (1ull<<(cl=idx&63))) u += bitgetx32(p4->ex, p4->cum[bi] + popcnt64(p4->xmap[bi] & ~(~0ull<<cl)), p4->bx) << b;
  return u;
}

// Get the next single value greater of equal to val
static ALWAYS_INLINE uint16_t p4geqx8( struct p4 *p4, unsigned char *in, unsigned b, uint8_t  val) { do p4->oval += p4getx8( p4, in, ++p4->idx, b)+1; while(p4->oval < val); return p4->oval; }
static ALWAYS_INLINE uint16_t p4geqx16(struct p4 *p4, unsigned char *in, unsigned b, uint16_t val) { do p4->oval += p4getx16(p4, in, ++p4->idx, b)+1; while(p4->oval < val); return p4->oval; }
static ALWAYS_INLINE uint32_t p4geqx32(struct p4 *p4, unsigned char *in, unsigned b, uint32_t val) { do p4->oval += p4getx32(p4, in, ++p4->idx, b)+1; while(p4->oval < val); return p4->oval; }

/* DO NOT USE : like p4dec32 but using direct access. This is only a demo showing direct access usage. Use p4dec32 instead for decompressing entire blocks */
unsigned char *p4decx32(   unsigned char *in, unsigned n, uint32_t *out);  // unsorted
unsigned char *p4fdecx32(  unsigned char *in, unsigned n, uint32_t *out, uint32_t start); // FOR increasing
unsigned char *p4f1decx32( unsigned char *in, unsigned n, uint32_t *out, uint32_t start); // FOR strictly increasing

#ifdef __cplusplus
}
#endif

#endif
