//-- codec: general purpose compression (lz, entropy coder, bwt,....)---------------------------------------------------------------------------------------------------
#include "conf.h"

IC_EXTERN_C_BEGIN

enum {
  ICC_NONE,
  ICC_LZTURBO,
  ICC_LZ4,
  ICC_ZLIB,
  ICC_DEFLATE,

  ICC_ZSTD,
  ICC_FSE,
  ICC_FSEH,
  ICC_LZTANS,
  ICC_TURBORC,
  ICC_MEMCPY,
  ICC_LAST,
};

//------------------- codecs -----------------------------------------------------------------------------------------------
size_t codecenc(unsigned char *in, size_t inlen, unsigned char *out, unsigned outsize, int codid, int codlev, unsigned char *codprm);
size_t codecdec(unsigned char *in, size_t inlen, unsigned char *out, unsigned outlen,  int codec, int codlev, unsigned char *codprm);

//------------------- TurboByte + lz ---------------------------------------------------------------------------------------------------------------------------------
unsigned lzv8enc(    unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
unsigned lzv8dec(    unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
unsigned lzv8zenc(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
unsigned lzv8zdec(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
unsigned lzv8xenc(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm); // TurboVByte
unsigned lzv8xdec(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);

//------------------ Byte transpose  + Lz --------------------------------------------------------------------------------------------------------------------------------------------
unsigned lztpenc(    unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm, unsigned bsize);
unsigned lztpdec(    unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm, unsigned bsize);
unsigned lztpxenc(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm, unsigned bsize); // XOR
unsigned lztpxdec(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm, unsigned bsize);
unsigned lztpzenc(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm, unsigned bsize); // Zigzag
unsigned lztpzdec(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm, unsigned bsize);

//------- rle -------------------------------------------------------------------------------------------------------------------
unsigned tprleenc(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp);
unsigned tprledec(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp);
unsigned tprlexenc(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp); // xor rle
unsigned tprlexdec(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp);
unsigned tprlezenc(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp); // Zigzag rle
unsigned tprlezdec(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp);

//------- rle + lz ---------------------------------------------------------------------------------------------------------------------------------------------------
unsigned lztprleenc( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm); // Zigzag rle
unsigned lztprledec( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
unsigned lztprlexenc(unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm); // Zigzag rle
unsigned lztprlexdec(unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
unsigned lztprlezenc(unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm); // Zigzag rle
unsigned lztprlezdec(unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);

//----------------- Nibble transpose  + codec (Lz, entropy coding, bwt,... -------------------------------------------------------------------------------------
unsigned lztp4enc(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm, unsigned bsize);
unsigned lztpd4ec(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm, unsigned bsize);
unsigned lztp4xenc(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm, unsigned bsize); //XOR
unsigned lztp4xdec(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm, unsigned bsize);
unsigned lztp4zenc(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm, unsigned bsize);
unsigned lztp4zdec(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm, unsigned bsize);

//----------------- bitshuffle ---------------------------------------------------------------------------------------------------------------------------------------
unsigned lztp1enc(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
unsigned lztp1dec(   unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
unsigned lztp1xenc(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
unsigned lztp1xdec(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
unsigned lztp1zenc(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
unsigned lztp1zdec(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);

//----------------- 2 D + codec (Lz, entropy coding, bwt,... ---------------------------------------------------------------------------------------------------------------------------------
unsigned lztpd2enc(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, unsigned x, unsigned y, int codid, int codlev, unsigned char *codprm);
unsigned lztpd2dec(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, unsigned x, unsigned y, int codid, int codlev, unsigned char *codprm);
unsigned lztpd2xenc( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, unsigned x, unsigned y, int codid, int codlev, unsigned char *codprm);
unsigned lztpd2xdec( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, unsigned x, unsigned y, int codid, int codlev, unsigned char *codprm);
unsigned lztpd2zenc( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, unsigned x, unsigned y, int codid, int codlev, unsigned char *codprm);
unsigned lztpd2zdec( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, unsigned x, unsigned y, int codid, int codlev, unsigned char *codprm);

//----------------- 3 D + codec (Lz, entropy coding, bwt,... ---------------------------------------------------------------------------------------------------------------------------------------------
unsigned lztpd3enc(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, unsigned x, unsigned y, unsigned z, int codid, int codlev, unsigned char *codprm);
unsigned lztpd3dec(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, unsigned x, unsigned y, unsigned z, int codid, int codlev, unsigned char *codprm);
unsigned lztpd3xenc( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, unsigned x, unsigned y, unsigned z, int codid, int codlev, unsigned char *codprm);
unsigned lztpd3xdec( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, unsigned x, unsigned y, unsigned z, int codid, int codlev, unsigned char *codprm);
unsigned lztpd3zenc( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, unsigned x, unsigned y, unsigned z, int codid, int codlev, unsigned char *codprm);
unsigned lztpd3zdec( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, unsigned x, unsigned y, unsigned z, int codid, int codlev, unsigned char *codprm);

//----------------- 4 D + codec (Lz, entropy coding, bwt,... -------------------------------------------------------------------------------------
unsigned lztpd4enc(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, unsigned w, unsigned x, unsigned y, unsigned z, int codid, int codlev, unsigned char *codprm);
unsigned lztpd4dec(  unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, unsigned w, unsigned x, unsigned y, unsigned z, int codid, int codlev, unsigned char *codprm);
unsigned lztpd4xenc( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, unsigned w, unsigned x, unsigned y, unsigned z, int codid, int codlev, unsigned char *codprm);
unsigned lztpd4xdec( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, unsigned w, unsigned x, unsigned y, unsigned z, int codid, int codlev, unsigned char *codprm);
unsigned lztpd4zenc( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outsize, unsigned esize, unsigned char *tmp, unsigned w, unsigned x, unsigned y, unsigned z, int codid, int codlev, unsigned char *codprm);
unsigned lztpd4zdec( unsigned char *in, unsigned inlen, unsigned char *out, unsigned outlen,  unsigned esize, unsigned char *tmp, unsigned w, unsigned x, unsigned y, unsigned z, int codid, int codlev, unsigned char *codprm);

typedef size_t(*codec_func)(const void* in, size_t inlen, void* out, size_t outlen); // secondary compression function

//-- TurboVLC : Novel Variable Length Coding for large integers with exponent + mantissa ------------------------
size_t vlccomp32(  unsigned char *_in, size_t _inlen, unsigned char *out,  size_t outsize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
size_t vlcdecomp32(unsigned char *in,  size_t inlen,  unsigned char *_out, size_t _outlen, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
size_t   vlccomp32x(const unsigned char* in, size_t inlen, unsigned char* out, size_t outlen, unsigned char* tmp, codec_func enc);
size_t vlcdecomp32x(const unsigned char* in, size_t inlen, unsigned char* out, size_t outlen, unsigned char* tmp, codec_func dec);
//-- Hybrid integer ------
size_t vhicomp32(  unsigned char *_in, size_t _inlen, unsigned char *out,  size_t outsize, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
size_t vhidecomp32(unsigned char *in,  size_t inlen,  unsigned char *_out, size_t _outlen, unsigned char *tmp, int codid, int codlev, unsigned char *codprm);
size_t   vhicomp32x(const unsigned char* in, size_t inlen, unsigned char* out, size_t outlen, unsigned char* tmp, codec_func enc);
size_t vhidecomp32x(const unsigned char* in, size_t inlen, unsigned char* out, size_t outlen, unsigned char* tmp, codec_func dec);

void tpmodeset(unsigned _tpmode);

void tpsizeset(unsigned _tpsize);
int  lzidget(const char *scmd);
const char *codstr(unsigned cid);
unsigned* getAvailableLzs(void); // ICC_LAST will be the last entry

IC_EXTERN_C_END
