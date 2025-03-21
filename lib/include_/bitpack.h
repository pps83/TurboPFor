//-- bitpack -------------------------------------------------------------------------------------------------------
#pragma once

#include "conf.h"

IC_EXTERN_C_BEGIN

size_t bitnbound8(     size_t n);
size_t bitnbound16(    size_t n);
size_t bitnbound32(    size_t n);
size_t bitnbound64(    size_t n);

size_t bitnbound128v8( size_t n);
size_t bitnbound128v16(size_t n);
size_t bitnbound128v32(size_t n);
size_t bitnbound128v64(size_t n);

size_t bitnbound256v8( size_t n);
size_t bitnbound256v16(size_t n);
size_t bitnbound256v32(size_t n);
size_t bitnbound256v64(size_t n);

//******************** Bit Packing High Level API - n unlimited ****************************
size_t bitnpack8(         uint8_t  *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnpack16(        uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnpack32(        uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnpack64(        uint64_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnpack128v16(    uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnpack128v32(    uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnpack128v64(    uint64_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnpack256v32(    uint32_t *__restrict in, size_t n, unsigned char *__restrict out);

size_t bitndpack8(        uint8_t  *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitndpack16(       uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitndpack32(       uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitndpack64(       uint64_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitndpack128v16(   uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitndpack128v32(   uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitndpack256v32(   uint32_t *__restrict in, size_t n, unsigned char *__restrict out);

size_t bitnd1pack8(       uint8_t  *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnd1pack16(      uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnd1pack32(      uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnd1pack64(      uint64_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnd1pack128v16(  uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnd1pack128v32(  uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnd1pack256v32(  uint32_t *__restrict in, size_t n, unsigned char *__restrict out);

size_t bitnzpack8(        uint8_t  *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnzpack16(       uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnzpack32(       uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnzpack64(       uint64_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnzpack128v16(   uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnzpack128v32(   uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnzpack256v32(   uint32_t *__restrict in, size_t n, unsigned char *__restrict out);

size_t bitnxpack8(        uint8_t  *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnxpack16(       uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnxpack32(       uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnxpack64(       uint64_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnxpack128v16(   uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnxpack128v32(   uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnxpack256v32(   uint32_t *__restrict in, size_t n, unsigned char *__restrict out);

size_t bitnfpack8(        uint8_t  *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnfpack16(       uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnfpack32(       uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnfpack64(       uint64_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnfpack128v16(   uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnfpack128v32(   uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitnfpack256v32(   uint32_t *__restrict in, size_t n, unsigned char *__restrict out);

size_t bitnunpack8(       const unsigned char *__restrict in, size_t n, uint8_t  *__restrict out);
size_t bitnunpack16(      const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitnunpack32(      const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);
size_t bitnunpack64(      const unsigned char *__restrict in, size_t n, uint64_t *__restrict out);
size_t bitnunpack128v16(  const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitnunpack128v32(  const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);
size_t bitnunpack128v64(  const unsigned char *__restrict in, size_t n, uint64_t *__restrict out);
size_t bitnunpack256v32(  const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);

size_t bitndunpack8(      const unsigned char *__restrict in, size_t n, uint8_t  *__restrict out);
size_t bitndunpack16(     const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitndunpack32(     const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);
size_t bitndunpack64(     const unsigned char *__restrict in, size_t n, uint64_t *__restrict out);
size_t bitndunpack128v16( const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitndunpack128v32( const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);
size_t bitndunpack256v32( const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);

size_t bitnd1unpack8(     const unsigned char *__restrict in, size_t n, uint8_t  *__restrict out);
size_t bitnd1unpack16(    const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitnd1unpack32(    const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);
size_t bitnd1unpack64(    const unsigned char *__restrict in, size_t n, uint64_t *__restrict out);
size_t bitnd1unpack128v16(const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitnd1unpack128v32(const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);
size_t bitnd1unpack256v32(const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);

size_t bitnzunpack8(      const unsigned char *__restrict in, size_t n, uint8_t  *__restrict out);
size_t bitnzunpack16(     const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitnzunpack32(     const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);
size_t bitnzunpack64(     const unsigned char *__restrict in, size_t n, uint64_t *__restrict out);
size_t bitnzunpack128v16( const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitnzunpack128v32( const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);
size_t bitnzunpack256v32( const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);

size_t bitnxunpack8(      const unsigned char *__restrict in, size_t n, uint8_t  *__restrict out);
size_t bitnxunpack16(     const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitnxunpack32(     const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);
size_t bitnxunpack64(     const unsigned char *__restrict in, size_t n, uint64_t *__restrict out);
size_t bitnxunpack128v16( const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitnxunpack128v32( const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);
size_t bitnxunpack256v32( const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);

size_t bitnfunpack8(      const unsigned char *__restrict in, size_t n, uint8_t  *__restrict out);
size_t bitnfunpack16(     const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitnfunpack32(     const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);
size_t bitnfunpack64(     const unsigned char *__restrict in, size_t n, uint64_t *__restrict out);
size_t bitnfunpack128v16( const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitnfunpack128v32( const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);
size_t bitnfunpack256v32( const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);

size_t bitns1pack128v16(  uint16_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitns1pack128v32(  uint32_t *__restrict in, size_t n, unsigned char *__restrict out);
size_t bitns1unpack128v16(const unsigned char *__restrict in, size_t n, uint16_t *__restrict out);
size_t bitns1unpack128v32(const unsigned char *__restrict in, size_t n, uint32_t *__restrict out);


//******** Bit Packing Low level API ****************************************************************
// bipackNN: Pack array with n unsigned (NN bits in[n]) values to the buffer out using nbits per value. Return value = end of compressed buffer out
unsigned char *bitpack8(    uint8_t  *__restrict in, unsigned n, unsigned char *__restrict out , unsigned b);
unsigned char *bitpack16(   uint16_t *__restrict in, unsigned n, unsigned char *__restrict out , unsigned b);
unsigned char *bitpack32(   uint32_t *__restrict in, unsigned n, unsigned char *__restrict out , unsigned b);
unsigned char *bitpack64(   uint64_t *__restrict in, unsigned n, unsigned char *__restrict out , unsigned b);

// delta bit packing
unsigned char *bitdpack8(   uint8_t  *__restrict in, unsigned n, unsigned char *__restrict out, uint8_t  start, unsigned b);
unsigned char *bitdpack16(  uint16_t *__restrict in, unsigned n, unsigned char *__restrict out, uint16_t start, unsigned b);
unsigned char *bitdpack32(  uint32_t *__restrict in, unsigned n, unsigned char *__restrict out, uint32_t start, unsigned b);
unsigned char *bitdpack64(  uint64_t *__restrict in, unsigned n, unsigned char *__restrict out, uint64_t start, unsigned b);

unsigned char *bitd1pack8(  uint8_t  *__restrict in, unsigned n, unsigned char *__restrict out, uint8_t  start, unsigned b);
unsigned char *bitd1pack16( uint16_t *__restrict in, unsigned n, unsigned char *__restrict out, uint16_t start, unsigned b);
unsigned char *bitd1pack32( uint32_t *__restrict in, unsigned n, unsigned char *__restrict out, uint32_t start, unsigned b);
unsigned char *bitd1pack64( uint64_t *__restrict in, unsigned n, unsigned char *__restrict out, uint64_t start, unsigned b);

// FOR bit packing : sorted integer array
unsigned char *bitfpack8(   uint8_t  *__restrict in, unsigned n, unsigned char *__restrict out, uint8_t  start, unsigned b);
unsigned char *bitfpack16(  uint16_t *__restrict in, unsigned n, unsigned char *__restrict out, uint16_t start, unsigned b);
unsigned char *bitfpack32(  uint32_t *__restrict in, unsigned n, unsigned char *__restrict out, uint32_t start, unsigned b);
unsigned char *bitfpack64(  uint64_t *__restrict in, unsigned n, unsigned char *__restrict out, uint64_t start, unsigned b);

unsigned char *bitf1pack8(  uint8_t  *__restrict in, unsigned n, unsigned char *__restrict out, uint8_t  start, unsigned b);
unsigned char *bitf1pack16( uint16_t *__restrict in, unsigned n, unsigned char *__restrict out, uint16_t start, unsigned b);
unsigned char *bitf1pack32( uint32_t *__restrict in, unsigned n, unsigned char *__restrict out, uint32_t start, unsigned b);
unsigned char *bitf1pack64( uint64_t *__restrict in, unsigned n, unsigned char *__restrict out, uint64_t start, unsigned b);

// zigzag : unsorted integer array
unsigned char *bitzpack8(   uint8_t  *__restrict in, unsigned n, unsigned char *__restrict out, uint8_t  start, unsigned b);
unsigned char *bitzpack16(  uint16_t *__restrict in, unsigned n, unsigned char *__restrict out, uint16_t start, unsigned b);
unsigned char *bitzpack32(  uint32_t *__restrict in, unsigned n, unsigned char *__restrict out, uint32_t start, unsigned b);
unsigned char *bitzpack64(  uint64_t *__restrict in, unsigned n, unsigned char *__restrict out, uint64_t start, unsigned b);

// xor : unsorted integer array
unsigned char *bitxpack8(   uint8_t  *__restrict in, unsigned n, unsigned char *__restrict out, uint8_t  start, unsigned b);
unsigned char *bitxpack16(  uint16_t *__restrict in, unsigned n, unsigned char *__restrict out, uint16_t start, unsigned b);
unsigned char *bitxpack32(  uint32_t *__restrict in, unsigned n, unsigned char *__restrict out, uint32_t start, unsigned b);
unsigned char *bitxpack64(  uint64_t *__restrict in, unsigned n, unsigned char *__restrict out, uint64_t start, unsigned b);

//-------------------------------------- SIMD ------------------------------------------------------------------------------------------
// Pack array with 128 unsigned (32 bits in[n]) values to the buffer out using nbits per value. Return value = end of compressed buffer out
unsigned char *bitpack128v16(  unsigned short    *__restrict in, unsigned n, unsigned char *__restrict out                      , unsigned b);
unsigned char *bitdpack128v16( unsigned short    *__restrict in, unsigned n, unsigned char *__restrict out, unsigned short start, unsigned b);
unsigned char *bitd1pack128v16(unsigned short    *__restrict in, unsigned n, unsigned char *__restrict out, unsigned short start, unsigned b);
unsigned char *bitfpack128v16( unsigned short    *__restrict in, unsigned n, unsigned char *__restrict out, unsigned short start, unsigned b);
unsigned char *bitf1pack128v16(unsigned short    *__restrict in, unsigned n, unsigned char *__restrict out, unsigned short start, unsigned b);
unsigned char *bitzpack128v16( unsigned short    *__restrict in, unsigned n, unsigned char *__restrict out, unsigned short start, unsigned b);
unsigned char *bitxpack128v16( unsigned short    *__restrict in, unsigned n, unsigned char *__restrict out, unsigned short start, unsigned b);

unsigned char *bitpack128v32(  unsigned          *__restrict in, unsigned n, unsigned char *__restrict out,                       unsigned b);
unsigned char *bitdpack128v32( unsigned          *__restrict in, unsigned n, unsigned char *__restrict out, unsigned       start, unsigned b);
unsigned char *bitd1pack128v32(unsigned          *__restrict in, unsigned n, unsigned char *__restrict out, unsigned       start, unsigned b);
unsigned char *bitfpack128v32( unsigned          *__restrict in, unsigned n, unsigned char *__restrict out, unsigned       start, unsigned b);
unsigned char *bitf1pack128v32(unsigned          *__restrict in, unsigned n, unsigned char *__restrict out, unsigned       start, unsigned b);
unsigned char *bitzpack128v32( unsigned          *__restrict in, unsigned n, unsigned char *__restrict out, unsigned       start, unsigned b);
unsigned char *bitxpack128v32( unsigned          *__restrict in, unsigned n, unsigned char *__restrict out, unsigned       start, unsigned b);

//unsigned char *bitpack256w32(  unsigned          *__restrict in, unsigned n, unsigned char *__restrict out                  , unsigned b);
unsigned char *bitpack128v64(  uint64_t          *__restrict in, unsigned n, unsigned char *__restrict out,                       unsigned b);

unsigned char *bitpack256v32(  unsigned          *__restrict in, unsigned n, unsigned char *__restrict out,                       unsigned b);
unsigned char *bitdpack256v32( unsigned          *__restrict in, unsigned n, unsigned char *__restrict out, unsigned       start, unsigned b);
unsigned char *bitd1pack256v32(unsigned          *__restrict in, unsigned n, unsigned char *__restrict out, unsigned       start, unsigned b);
unsigned char *bitfpack256v32( unsigned          *__restrict in, unsigned n, unsigned char *__restrict out, unsigned       start, unsigned b);
unsigned char *bitf1pack256v32(unsigned          *__restrict in, unsigned n, unsigned char *__restrict out, unsigned       start, unsigned b);
unsigned char *bitzpack256v32( unsigned          *__restrict in, unsigned n, unsigned char *__restrict out, unsigned       start, unsigned b);
unsigned char *bitxpack256v32( unsigned          *__restrict in, unsigned n, unsigned char *__restrict out, unsigned       start, unsigned b);

unsigned char *bits1pack128v16(unsigned short *__restrict in, unsigned n, unsigned char *__restrict out, unsigned short start, unsigned b);
unsigned char *bits1pack128v32(unsigned       *__restrict in, unsigned n, unsigned char *__restrict out, unsigned start, unsigned b);
const unsigned char *bits1unpack128v16( const unsigned char *__restrict in, unsigned n, uint16_t *__restrict out, uint16_t start, unsigned b);
const unsigned char *bits1unpack128v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
//********************************** Bit Packing : Unpack ****************************************************************

// ---------------- Unpack a b-bits packed integer array -------------------------------------------------------------------------------
// unpack a bitpacked integer array. Return value = end of packed buffer in
const unsigned char *bitunpack8(  const unsigned char *__restrict in, unsigned n, uint8_t  *__restrict out, unsigned b);
const unsigned char *bitunpack16( const unsigned char *__restrict in, unsigned n, uint16_t *__restrict out, unsigned b);
const unsigned char *bitunpack32( const unsigned char *__restrict in, unsigned n, uint32_t *__restrict out, unsigned b);
const unsigned char *bitunpack64( const unsigned char *__restrict in, unsigned n, uint64_t *__restrict out, unsigned b);

// ---------------- Direct Access to a single packed integer array entry --------------------------------------------------------------
  #ifdef TURBOPFOR_DAC
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
static ALWAYS_INLINE void      bitsetx16(unsigned char *__restrict in, unsigned  idx, unsigned v, unsigned b) { unsigned bidx = b*idx;  unsigned           *p = (unsigned           *)             in+(bidx>>4) ; *p = ( *p & ~(((1u  <<b)-1) << (bidx& 0xf)) ) |                     v<<(bidx& 0xf);}
static ALWAYS_INLINE void      bitsetx32(unsigned char *__restrict in, unsigned  idx, unsigned v, unsigned b) { unsigned bidx = b*idx;  unsigned long long *p = (unsigned long long *)((unsigned *)in+(bidx>>5)); *p = ( *p & ~(((1ull<<b)-1) << (bidx&0x1f)) ) | (unsigned long long)v<<(bidx&0x1f);}
   #endif
// ---------------- DFOR : integrated bitpacking, for delta packed SORTED array (Ex. DocId in inverted index) -------------------------------
// start <= out[0] <= out[1] <= ... <= out[n-2] <= out[n-1] <= (1<<N)-1  N=8,16,32 or 64
// out[0] = start + in[0];  out[1] = out[0] + in[1]; ... ;  out[i] = out[i-1] + in[i]
const unsigned char *bitdunpack8(  const unsigned char *__restrict in, unsigned n, uint8_t  *__restrict out, uint8_t  start, unsigned b);
const unsigned char *bitdunpack16( const unsigned char *__restrict in, unsigned n, uint16_t *__restrict out, uint16_t start, unsigned b);
const unsigned char *bitdunpack32( const unsigned char *__restrict in, unsigned n, uint32_t *__restrict out, uint32_t start, unsigned b);
const unsigned char *bitdunpack64( const unsigned char *__restrict in, unsigned n, uint64_t *__restrict out, uint64_t start, unsigned b);

// start < out[0] < out[1] < ... < out[n-2] < out[n-1] < (1<<N)-1,    N=8,16,32 or 64
// out[0] = start + in[0] + 1;  out[1] = out[0] + in[1] + 1; ... ;  out[i] = out[i-1] + in[i] +  1
const unsigned char *bitd1unpack8( const unsigned char *__restrict in, unsigned n, uint8_t  *__restrict out, uint8_t  start, unsigned b);
const unsigned char *bitd1unpack16(const unsigned char *__restrict in, unsigned n, uint16_t *__restrict out, uint16_t start, unsigned b);
const unsigned char *bitd1unpack32(const unsigned char *__restrict in, unsigned n, uint32_t *__restrict out, uint32_t start, unsigned b);
const unsigned char *bitd1unpack64(const unsigned char *__restrict in, unsigned n, uint64_t *__restrict out, uint64_t start, unsigned b);

// ---------------- ZigZag : integrated bitpacking, for zigzag packed unsorted
const unsigned char *bitzunpack8(  const unsigned char *__restrict in, unsigned n, uint8_t  *__restrict out, uint8_t  start, unsigned b);
const unsigned char *bitzunpack16( const unsigned char *__restrict in, unsigned n, uint16_t *__restrict out, uint16_t start, unsigned b);
const unsigned char *bitzunpack32( const unsigned char *__restrict in, unsigned n, uint32_t *__restrict out, uint32_t start, unsigned b);
const unsigned char *bitzunpack64( const unsigned char *__restrict in, unsigned n, uint64_t *__restrict out, uint64_t start, unsigned b);

// ---------------- Xor : integrated bitpacking, for xor packed unsorted
const unsigned char *bitxunpack8(  const unsigned char *__restrict in, unsigned n, uint8_t  *__restrict out, uint8_t  start, unsigned b);
const unsigned char *bitxunpack16( const unsigned char *__restrict in, unsigned n, uint16_t *__restrict out, uint16_t start, unsigned b);
const unsigned char *bitxunpack32( const unsigned char *__restrict in, unsigned n, uint32_t *__restrict out, uint32_t start, unsigned b);
const unsigned char *bitxunpack64( const unsigned char *__restrict in, unsigned n, uint64_t *__restrict out, uint64_t start, unsigned b);

// ---------------- For : Direct Access for packed SORTED array  --------------------------------------------
// out[i] = start + in[i] + i
const unsigned char *bitfunpack8(  const unsigned char *__restrict in, unsigned n, uint8_t  *__restrict out, uint8_t  start, unsigned b);
const unsigned char *bitfunpack16( const unsigned char *__restrict in, unsigned n, uint16_t *__restrict out, uint16_t start, unsigned b);
const unsigned char *bitfunpack32( const unsigned char *__restrict in, unsigned n, uint32_t *__restrict out, uint32_t start, unsigned b);
const unsigned char *bitfunpack64( const unsigned char *__restrict in, unsigned n, uint64_t *__restrict out, uint64_t start, unsigned b);

// out[i] = start + in[i] + i + 1
const unsigned char *bitf1unpack8( const unsigned char *__restrict in, unsigned n, uint8_t  *__restrict out, uint8_t  start, unsigned b);
const unsigned char *bitf1unpack16(const unsigned char *__restrict in, unsigned n, uint16_t *__restrict out, uint16_t start, unsigned b);
const unsigned char *bitf1unpack32(const unsigned char *__restrict in, unsigned n, uint32_t *__restrict out, uint32_t start, unsigned b);
const unsigned char *bitf1unpack64(const unsigned char *__restrict in, unsigned n, uint64_t *__restrict out, uint64_t start, unsigned b);

// ---------------- SIMD : unpack a SIMD bit packed integer array -------------------------------------------------------------------------------
// SIMD unpack a 128/256 bitpacked integer array. Return value = end of packed buffer in
const unsigned char *bitunpack128v16(  const unsigned char *__restrict in, unsigned n, unsigned short *__restrict out,                       unsigned b);
const unsigned char *bitzunpack128v16( const unsigned char *__restrict in, unsigned n, unsigned short *__restrict out, unsigned short start, unsigned b);
const unsigned char *bitxunpack128v16( const unsigned char *__restrict in, unsigned n, unsigned short *__restrict out, unsigned short start, unsigned b);
const unsigned char *bitdunpack128v16( const unsigned char *__restrict in, unsigned n, unsigned short *__restrict out, unsigned short start, unsigned b);
const unsigned char *bitd1unpack128v16(const unsigned char *__restrict in, unsigned n, unsigned short *__restrict out, unsigned short start, unsigned b);
const unsigned char *bitfunpack128v16( const unsigned char *__restrict in, unsigned n, unsigned short *__restrict out, unsigned short start, unsigned b);
const unsigned char *bitf1unpack128v16(const unsigned char *__restrict in, unsigned n, unsigned short *__restrict out, unsigned short start, unsigned b);

const unsigned char *bitunpack128v32(  const unsigned char *__restrict in, unsigned n, unsigned *__restrict out,                 unsigned b);
const unsigned char *bitzunpack128v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
const unsigned char *bitxunpack128v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
const unsigned char *bitdunpack128v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
const unsigned char *bitd1unpack128v32(const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
const unsigned char *bitfunpack128v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
const unsigned char *bitf1unpack128v32(const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);

const unsigned char *bitunpack256w32(  const unsigned char *__restrict in, unsigned n, unsigned *__restrict out,                 unsigned b);
const unsigned char *bitunpack128v64(  const unsigned char *__restrict in, unsigned n, uint64_t *__restrict out,                 unsigned b);

const unsigned char *bitunpack256v32(  const unsigned char *__restrict in, unsigned n, unsigned *__restrict out,                 unsigned b);
const unsigned char *bitzunpack256v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
const unsigned char *bitxunpack256v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
const unsigned char *bitdunpack256v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
const unsigned char *bitd1unpack256v32(const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
const unsigned char *bitfunpack256v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
const unsigned char *bitf1unpack256v32(const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);

const unsigned char *bitunpack128h32(  const unsigned char *__restrict in, unsigned n, unsigned *__restrict out,                 unsigned b);
const unsigned char *bitzunpack128h32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
const unsigned char *bitdunpack128h32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);
const unsigned char *bitd1unpack128h32(const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b);

// internal TurboPFor functions: masked unpack
const unsigned char *_bitunpack128v16(  const unsigned char *__restrict in, unsigned n, unsigned short *__restrict out,                       unsigned b, unsigned short *__restrict pex, const unsigned char *bb);
const unsigned char *_bitdunpack128v16( const unsigned char *__restrict in, unsigned n, unsigned short *__restrict out, unsigned short start, unsigned b, unsigned short *__restrict pex, const unsigned char *bb);
const unsigned char *_bitd1unpack128v16(const unsigned char *__restrict in, unsigned n, unsigned short *__restrict out, unsigned short start, unsigned b, unsigned short *__restrict pex, const unsigned char *bb);
const unsigned char *_bitzunpack128v16( const unsigned char *__restrict in, unsigned n, unsigned short *__restrict out, unsigned short start, unsigned b, unsigned short *__restrict pex, const unsigned char *bb);

const unsigned char *_bitunpack128v32(  const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned b, unsigned *__restrict pex, const unsigned char *bb);
const unsigned char *_bitdunpack128v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b, unsigned *__restrict pex, const unsigned char *bb);
const unsigned char *_bitd1unpack128v32(const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b, unsigned *__restrict pex, const unsigned char *bb);
const unsigned char *_bitzunpack128v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b, unsigned *__restrict pex, const unsigned char *bb);

const unsigned char *_bitunpack128h32(  const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned b, unsigned *__restrict pex, const unsigned char *bb);
const unsigned char *_bitdunpack128h32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b, unsigned *__restrict pex, const unsigned char *bb);
const unsigned char *_bitd1unpack128h32(const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b, unsigned *__restrict pex, const unsigned char *bb);

const unsigned char *_bitunpack256w32(  const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned b, unsigned *__restrict pex, const unsigned char *bb);
const unsigned char *_bitunpack128v64(  const unsigned char *__restrict in, unsigned n, uint64_t *__restrict out, unsigned b, uint32_t *__restrict pex, const unsigned char *bb);

const unsigned char *_bitunpack256v32(  const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned b, unsigned *__restrict pex, const unsigned char *bb);
const unsigned char *_bitdunpack256v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b, unsigned *__restrict pex, const unsigned char *bb);
const unsigned char *_bitd1unpack256v32(const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b, unsigned *__restrict pex, const unsigned char *bb);
const unsigned char *_bitzunpack256v32( const unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start, unsigned b, unsigned *__restrict pex, const unsigned char *bb);

IC_EXTERN_C_END
