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
// vint.c - "Integer Compression" variable byte
  #ifndef USIZE
#include <stdio.h>
#include <string.h>
#include "include_/conf.h"
#include "include_/bitutil.h"
#include "include_/vint.h"
#undef VB_MAX
#define VB_MAX 0xfd  // reserved : 0xfe=all zeros, 0xff=overflow
#include "include_/vlcbyte.h"

#include "include_/bitutil_.h"

#if defined(_MSC_VER) && !defined(__clang__)
#pragma warning(disable: 4005 4068 4090)
#endif

size_t vbbound8( size_t n) { return n; }
size_t vbbound16(size_t n) { return n*(2+1)+3; }
size_t vbbound32(size_t n) { return n*(4+1)+5; }
size_t vbbound64(size_t n) { return n*(8+1)+9; }

//----------------------------------------------------------------
#define OVERFLOWD(in,n,out)    if(*in == 0xff) { memcpy(out, in+1, n*(USIZE/8)); return in+1+n*(USIZE/8); }
#define OVERFLOWE(in,n,out,op, _goto_) if(op+32 > out + (uint64_t)n*(USIZE/8)) { *out = 0xff; memcpy(out+1, in, n*(USIZE/8)); op = out+1+n*(USIZE/8); _goto_; }

#define UN 8 // 4 //

#define VDELTA    0
#define VBDENC    vbdenc
#define VBDDEC    vbddec
#define VBDGETX   vbdgetx
#define VBDGETGEQ vbdgetgeq

#define USIZE 32
#include "vint.c"
#undef USIZE

#define USIZE 64
#include "vint.c"
#undef USIZE

#define USIZE 16
#include "vint.c"
#undef USIZE

#define USIZE 8
#include "vint.c"
#undef USIZE
#undef VDELTA
#undef VBDENC
#undef VBDDEC
#undef VBDGETX
#undef VBDGETGEQ

#define VDELTA 1
#define VBDENC    vbd1enc
#define VBDDEC    vbd1dec
#define VBDGETX   vbd1getx
#define VBDGETGEQ vbd1getgeq

#define USIZE 32
#include "vint.c"
#undef USIZE

#define USIZE 64
#include "vint.c"
#undef USIZE

#define USIZE 16
#include "vint.c"
#undef USIZE

#define USIZE 8
#include "vint.c"
#undef USIZE

#undef UN
#undef VDELTA
#undef VBDENC
#undef VBDDEC
#undef VBDGETX
#undef VBDGETGEQ
#undef VB_MAX

  #else
#define uint_t T3(uint, USIZE, _t)

    #if VDELTA == 0

const unsigned char *T2(vbdec, USIZE)(const unsigned char  *__restrict in, unsigned n, uint_t *__restrict out) {
  register uint_t x, *op;
  OVERFLOWD(in, n, out);

  #define VBE(_i_) T2(_vbget, USIZE)(in, x, op[_i_] = x)
  for(op = out; op != out+(n&~(UN-1)); op += UN) {
    VBE(0); VBE(1); VBE(2); VBE(3);
      #if UN > 4
    VBE(4); VBE(5); VBE(6); VBE(7);
      #endif
                                                    PREFETCH(in+16*USIZE, 0);
  }
  while(op != out+n)
    T2(_vbget, USIZE)(in, x, *op++ = x );
  return in;
}
#undef VBE

unsigned char *T2(vbenc, USIZE)(uint_t *__restrict in, unsigned n, unsigned char *__restrict out) {
  uint_t x, *ip;
  unsigned char *op = out;

  #define VBD(_i_) x = ip[_i_]; T2(_vbput, USIZE)(op, x, ;);
  for(ip = in; ip != in+(n&~(UN-1)); ip += UN) {        PREFETCH(ip+USIZE*8, 0);
    VBD(0); VBD(1); VBD(2); VBD(3);
      #if UN > 4
    VBD(4); VBD(5); VBD(6); VBD(7);
      #endif
  }
  while(ip != in+n) {
    x = *ip++;
    T2(_vbput, USIZE)(op, x, ;);
  }

  OVERFLOWE(in,n,out,op,;);
  return op;
}
#undef VBD

uint_t T2(vbgetx, USIZE)(unsigned char  *__restrict in, unsigned idx) {
  unsigned char *ip;
  unsigned i;
  uint_t x;
  if(*in == 255)
    return T2(ctou, USIZE)(in+1+idx*(USIZE/8));
  for(ip = in,i = 0; i <= idx; i++)
    ip += T2(vbvlen, USIZE)(*ip);
  T2(_vbget, USIZE)(in, x, ;);
  return x;
}

/*unsigned T2(vbgeteq, USIZE)(unsigned char *__restrict in, unsigned n, uint_t key, unsigned char **__restrict _ip) {
  unsigned i;
  unsigned char *ip;
  uint_t x;
  if(*in == 255) {
    for(ip = (*_ip==in)?in:*ip; ip < in+n; ip+USIZE/8) {
      T2(_vbget, USIZE)(ip, x, ;);
      if((x = T2(ctou, USIZE)(ip)) == key) break;
    }
  } else for(ip = *_ip,i=idx; i < n; i++) {
    T2(_vbget, USIZE)(ip, x, ;);
    if(x == key) break;
  }
  *_ip = ip;
  return i;
}*/
#define BITS 8
#define BIT_SET(  p, n) (p[(n)/BITS] |=  (0x80>>((n)%BITS)))
#define BIT_CLEAR(p, n) (p[(n)/BITS] &= ~(0x80>>((n)%BITS)))
#define BIT_ISSET(p, n) (p[(n)/BITS] &   (0x80>>((n)%BITS)))
unsigned char *T2(vbddenc, USIZE)(uint_t *__restrict in, unsigned n, unsigned char *__restrict out, uint_t start) {
  uint_t *ip,v,pd=0,*p;
  unsigned char *bp=out; out += (n+7)/8;
  #define VBDDE(i) { uint_t x; start = ip[i]-start; x = start-pd; pd = start;  \
    if(!x) BIT_CLEAR(bp,i); else { BIT_SET(bp,i); x = T2(zigzagenc, USIZE)(x); T2(_vbput, USIZE)(out, x, ;); } start = ip[i]; }

  for(ip = in; ip != in+(n&~(8-1)); ip+=8,bp++) { VBDDE(0);VBDDE(1);VBDDE(2);VBDDE(3);VBDDE(4);VBDDE(5);VBDDE(6);VBDDE(7);}
  for(p=ip; p != in+n; p++) VBDDE(p-ip);
  return out;
}

unsigned char *T2(vbdddec, USIZE)(unsigned char *__restrict in, unsigned n, uint_t *__restrict out, uint_t start) {
  uint_t *op,pd=0,*p;
  unsigned i;
  #define VBDDD(i) { uint_t x=0; if(BIT_ISSET(bp,i)) { T2(_vbget, USIZE)(in, x, ;); pd += T2(zigzagdec, USIZE)(x); } op[i] = (start += pd); }
  unsigned char *bp=in; in+=(n+7)/8;
  for(op = out; op != out+(n&~(8-1)); op+=8,bp++) {
    if(!bp[0]) { op[0]=(start+=pd); op[1]=(start+=pd); op[2]=(start+=pd); op[3]=(start+=pd); op[4]=(start+=pd); op[5]=(start+=pd); op[6]=(start+=pd); op[7]=(start+=pd); continue; }
    VBDDD(0); VBDDD(1); VBDDD(2); VBDDD(3); VBDDD(4); VBDDD(5); VBDDD(6); VBDDD(7);                                         PREFETCH(in+16*USIZE, 0);
  }
  for(p=op; p != out+n; p++) VBDDD(p-op);
  return in;
}
#undef VBDDE
#undef VBDDD

unsigned char *T2(vbzenc, USIZE)(uint_t *__restrict in, unsigned n, unsigned char *__restrict out, uint_t start) {
  uint_t *ip,v;
  unsigned char *op = out;

  #define VBZE { v = T2(zigzagenc, USIZE)((T3(int, USIZE, _t))(*ip)-(T3(int, USIZE, _t))start); start=*ip++; T2(_vbput, USIZE)(op, v, ;); }
  for(ip = in; ip != in+(n&~(UN-1)); ) { VBZE;VBZE;VBZE;VBZE; }
  while(ip != in+n) VBZE;                         //OVERFLOWE(in,n,out,op);
  return op;
}
#undef VBZE

unsigned char *T2(vbzdec, USIZE)(unsigned char *__restrict in, unsigned n, uint_t *__restrict out, uint_t start) {
  uint_t x,*op;

  #define VBZD { T2(_vbget, USIZE)(in, x, ;); *op++ = (start += T2(zigzagdec, USIZE)(x)); }
  for(op = out; op != out+(n&~(UN-1)); ) { VBZD; VBZD; VBZD; VBZD;
      #if UN > 4
    VBZD; VBZD; VBZD; VBZD;
      #endif
                                            PREFETCH(in+16*USIZE, 0);
  }
  while(op != out+n) VBZD;

  return in;
}
#undef VBZD

uint_t T2(vbzgetx, USIZE)(unsigned char  *__restrict in, unsigned idx, uint_t start) {
  unsigned char *ip;
  unsigned i;
  uint_t x;

  for(ip = in,i = 0; i <= idx; i++) {
    T2(_vbget, USIZE)(ip, x, ;);
    start += x+VDELTA;
  }
  return start;
}

unsigned T2(vbzgeteq, USIZE)(unsigned char **__restrict in, unsigned n, unsigned idx, uint_t key, uint_t start ) {
  unsigned i;
  unsigned char *ip;
  uint_t x;
  for(ip = *in,i=idx; i < n; i++) {
    T2(_vbget, USIZE)(ip, x, ;);
    if((start += x+VDELTA) == key)
      break;
  }
  *in = ip;
  return i;
}

unsigned char *T2(vbxenc, USIZE)(uint_t *__restrict in, unsigned n, unsigned char *__restrict out, uint_t start) {
  uint_t *ip,v;
  unsigned char *op = out;

  #define VBXE { v = (*ip)^start; start=*ip++; T2(_vbput, USIZE)(op, v, ;); }
  for(ip = in; ip != in+(n&~(UN-1)); ) { VBXE;VBXE;VBXE;VBXE; }
  while(ip != in+n) VBXE;                         //OVERFLOWE(in,n,out,op);
  return op;
}
#undef VBZE

unsigned char *T2(vbxdec, USIZE)(unsigned char *__restrict in, unsigned n, uint_t *__restrict out, uint_t start) {
  uint_t x,*op;

  #define VBXD { T2(_vbget, USIZE)(in, x, ;); *op++ = (start ^= x); }
  for(op = out; op != out+(n&~(UN-1)); ) { VBXD; VBXD; VBXD; VBXD;
      #if UN > 4
    VBXD; VBXD; VBXD; VBXD;
      #endif
                                            PREFETCH(in+16*USIZE, 0);
  }
  while(op != out+n) VBXD;

  return in;
}
#undef VBZD

uint_t T2(vbxgetx, USIZE)(unsigned char  *__restrict in, unsigned idx, uint_t start) {
  unsigned char *ip;
  unsigned i;
  uint_t x;

  for(ip = in,i = 0; i <= idx; i++) {
    T2(_vbget, USIZE)(ip, x, ;);
    start ^= x;
  }
  return start;
}

unsigned T2(vbxgeteq, USIZE)(unsigned char **__restrict in, unsigned n, unsigned idx, uint_t key, uint_t start ) {
  unsigned i;
  unsigned char *ip;
  uint_t x;
  for(ip = *in,i=idx; i < n; i++) {
    T2(_vbget, USIZE)(ip, x, ;);
    if((start ^= x) == key)
      break;
  }
  *in = ip;
  return i;
}
  #endif

unsigned char *T2(VBDENC, USIZE)(uint_t *__restrict in, unsigned n, unsigned char *__restrict out, uint_t start) {
  unsigned char *op = out;
  uint_t        *ip, b = 0,v;
  if(!n) return out;
  #define VBDE { v = ip[0]-start-VDELTA; start = *ip++; T2(_vbput, USIZE)(op, v, ;); b |= (v /*^ x*/); }
  for(ip = in; ip != in + (n&~(UN-1)); ) { VBDE; VBDE; VBDE; VBDE;
      #if UN > 4
    VBDE; VBDE; VBDE; VBDE;
      #endif
  }
  while(ip != in+n) VBDE;
  if(!b) { op = out; *op++ = 0xfe; } // if (x) { op = out; *op++ = VB_MAX-2; T2(_vbput, USIZE)(op, x, ;); }
    #if USIZE < 64
  OVERFLOWE(in,n,out,op, ;);
    #endif
  return op;
}
#undef VBDE

unsigned char *T2(VBDDEC, USIZE)(unsigned char *__restrict in, unsigned n, uint_t *__restrict out, uint_t start) {
  uint_t x,*op;
  if(!n) return in;

    #if USIZE < 64
  OVERFLOWD(in,n,out);
    #endif

  if(in[0] == 0xfe) {
    in++;
      #if (defined(__SSE2__) || defined(__ARM_NEON)) && USIZE == 32
        #if VDELTA == 0
    if(n) T2(BITZERO, USIZE)(out, n, start);
        #else
    if(n) T2(BITDIZERO,USIZE)(out, n, start, VDELTA);
        #endif
      #else
        #if VDELTA == 0
    for(x = 0; x < n; x++) out[x] = start;
        #else
    for(x = 0; x < n; x++) out[x] = start+x*VDELTA;
        #endif
      #endif
    return in;
  }
    #if 0 //USIZE < 64
  else if(in[0] == 0xfe) { in++;
    uint_t z;
    T2(_vbget, USIZE)(in, z, ;);
      #if VDELTA == 0
    for(x = 0; x < n; x++) out[x] = start+z;
      #else
    for(x = 0; x < n; x++) out[x] = start+x+z;
      #endif
    return in;
  }
    #endif
 #define VBDD(i) { T2(_vbget, USIZE)(in, x, x+=VDELTA); op[i] = (start += x); }
  for(op = out; op != out+(n&~(UN-1)); op+=UN) {
    VBDD(0); VBDD(1); VBDD(2); VBDD(3);
      #if UN > 4
    VBDD(4); VBDD(5); VBDD(6); VBDD(7);
      #endif
                                                PREFETCH(in+16*USIZE, 0);
  }
  for(;op != out+n;op++) VBDD(0);
  return in;
}
#undef VBDD

uint_t T2(VBDGETX, USIZE)(unsigned char  *__restrict in, unsigned idx, uint_t start) {
  unsigned char *ip;
  unsigned i=0;
  uint_t x;

    #if USIZE > 64
  unsigned long long u;
  _vbget64(in, u, ;); x = u>>1; start += x+VDELTA;
  if(u & 1) return start + VDELTA;
    #endif
  for(ip = in; i <= idx; i++) {
    T2(_vbget, USIZE)(ip, x, ;);
    start += x+VDELTA;
  }
  return start;
}

unsigned T2(VBDGETGEQ, USIZE)(unsigned char **__restrict in, unsigned n, unsigned idx, uint_t *key, uint_t start ) {
  unsigned i=0;
  unsigned char *ip=*in;
  uint_t x;
    #if USIZE < 64
  if(!idx) {
    unsigned long long u; _vbget64(ip, u, ;); x = u>>1; start += x+VDELTA;
    if((u & 1) && start == *key) { *in = ip; return 0; }
    i++;
  }
    #endif
  for(ip = *in; i < n; i++) {
    T2(_vbget, USIZE)(ip, x, ;);
    if((start += x+VDELTA) == *key)
      break;
  }
  *in = ip;
  return i;
}
#undef uint_t
#endif
