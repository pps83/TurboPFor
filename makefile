# powturbo (c) Copyright 2013-2019
# Download or clone TurboPFor:
# git clone git://github.com/powturbo/TurboPFor.git
# make
#
# To benchmark external libraries:
# git clone --recursive git://github.com/powturbo/TurboPFor.git
#        make: "make CODEC1=1 CODEC2=1 LZ=1"
# on arm make: "make CODEC1=1 LZ=1"

CC ?= gcc
CXX ?= g++

#CC=powerpc64le-linux-gnu-gcc
CL = $(CC)
#DEBUG=-DDEBUG -g
DEBUG=-DNDEBUG -s

JAVA_HOME ?= /usr/lib/jvm/java-8-openjdk-amd64
PREFIX ?= /usr/local
DIRBIN ?= $(PREFIX)/bin
DIRINC ?= $(PREFIX)/include
DIRLIB ?= $(PREFIX)/lib
SRC ?= lib/

OPT=-fstrict-aliasing -fPIC
ifeq (,$(findstring clang, $(CC)))
OPT+=-falign-loops
endif

#------- OS/ARCH -------------------
ifneq (,$(filter Windows%,$(OS)))
  OS := Windows
  CC=gcc
  CXX=g++
  ARCH=x86_64
else
  OS := $(shell uname -s)
  ARCH := $(shell uname -m)

ifneq (,$(findstring aarch64,$(CC)))
  ARCH = aarch64
else ifneq (,$(findstring powerpc64le,$(CC)))
  ARCH = ppc64le
endif
endif

ifeq ($(ARCH),ppc64le)
  SSE=-D__SSSE3__
  CFLAGS=-mcpu=power9 -mtune=power9 $(SSE)
else ifeq ($(ARCH),aarch64)
  CFLAGS=-march=armv8-a
ifneq (,$(findstring clang, $(CC)))
  OPT+=-fomit-frame-pointer
#-fmacro-backtrace-limit=0
endif
  SSE=-march=armv8-a
else ifeq ($(ARCH),$(filter $(ARCH),x86_64))
# set minimum arch sandy bridge SSE4.1 + AVX
  SSE=-march=corei7-avx -mtune=corei7-avx
# SSE+=-mno-avx -mno-aes
  CFLAGS=$(SSE)
  AVX2=-march=haswell
#  SSE=$(AVX2)
endif

CFLAGS+=-w -Wall $(DEBUG) $(OPT)

ifeq ($(OS),$(filter $(OS),Linux GNU/kFreeBSD GNU OpenBSD FreeBSD DragonFly NetBSD MSYS_NT Haiku))
LDFLAGS+=-lrt -lm
endif

# compiler supports float16
ifeq ($(FLOAT16),1)
CFLAGS+=-DUSE_FLOAT16
endif
ifeq ($(STATIC),1)
LDFLAGS+=-static
endif

all: icapp

$(SRC)vp4c_sse.o: $(SRC)vp4c.c
	$(CC) -O3 -w $(SSE) -DSSE2_ON $(OPT) -c $(SRC)vp4c.c -o $(SRC)vp4c_sse.o

$(SRC)vp4c_avx2.o: $(SRC)vp4c.c
	$(CC) -O3 -w $(AVX2) -DAVX2_ON $(OPT) -c $(SRC)vp4c.c -o $(SRC)vp4c_avx2.o

$(SRC)vp4d_sse.o: $(SRC)vp4d.c
	$(CC) -O3 -w $(SSE) -DSSE2_ON $(OPT) -c $(SRC)vp4d.c -o $(SRC)vp4d_sse.o

$(SRC)vp4d_avx2.o: $(SRC)vp4d.c
	$(CC) -O3 -w $(AVX2) -DAVX2_ON $(OPT) -c $(SRC)vp4d.c -o $(SRC)vp4d_avx2.o

$(SRC)bitpack_sse.o: $(SRC)bitpack.c
	$(CC) -O3 -w $(SSE) -DSSE2_ON $(OPT) -c $(SRC)bitpack.c -o $(SRC)bitpack_sse.o

$(SRC)bitpack_avx2.o: $(SRC)bitpack.c
	$(CC) -O3 -w $(AVX2) -DAVX2_ON $(OPT) -c $(SRC)bitpack.c -o $(SRC)bitpack_avx2.o

$(SRC)bitunpack_sse.o: $(SRC)bitunpack.c
	$(CC) -O3 -w $(SSE) -DSSE2_ON $(OPT) -c $(SRC)bitunpack.c -o $(SRC)bitunpack_sse.o

$(SRC)bitunpack_avx2.o: $(SRC)bitunpack.c
	$(CC) -O3 -w $(AVX2) -DAVX2_ON $(OPT) -c $(SRC)bitunpack.c -o $(SRC)bitunpack_avx2.o

$(SRC)transpose_sse.o: $(SRC)transpose.c
	$(CC) -O3 -w $(SSE) -DSSE2_ON $(OPT) -c $(SRC)transpose.c -o $(SRC)transpose_sse.o

$(SRC)transpose_avx2.o: $(SRC)transpose.c
	$(CC) -O3 -w $(AVX2) -DAVX2_ON $(OPT) -c $(SRC)transpose.c -o $(SRC)transpose_avx2.o

-include ext/libext.mak

LIB=$(SRC)bitpack.o $(SRC)bitpack_sse.o $(SRC)bitunpack.o $(SRC)bitunpack_sse.o \
    $(SRC)vp4c.o $(SRC)vp4c_sse.o $(SRC)vp4d.o $(SRC)vp4d_sse.o \
	$(SRC)bitutil.o $(SRC)fp.o $(SRC)v8.o $(SRC)vint.o $(SRC)transpose.o $(SRC)transpose_sse.o $(SRC)trlec.o $(SRC)trled.o $(SRC)vsimple.o $(SRC)eliasfano.o
#bic.o
ifeq ($(ARCH),x86_64)
LIB+=$(SRC)bitpack_avx2.o $(SRC)bitunpack_avx2.o $(SRC)vp4c_avx2.o $(SRC)vp4d_avx2.o $(SRC)transpose_avx2.o
endif

libic.a: $(LIB)
	ar cr $@ $+

libic.so : $(LIB)
	$(CC) -shared $+ -o $@

JAVA_SUBDIR = java

jic.h: $(JAVA_SUBDIR)/jic.java
	# cp jic.h ..
	cd $(JAVA_SUBDIR) && javah -jni jic && cp jic.h ..

# $(JAVA_SUBDIR)/jic.class : $(JAVA_SUBDIR)/jic.java
# 	cd $(JAVA_SUBDIR) && javac jic.java

$(JAVA_SUBDIR)/libic.so : libic.a jic.h jic.c
	$(CC) -shared $(CFLAGS) -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux jic.c libic.a -o $(JAVA_SUBDIR)/libic.so

$(JAVA_SUBDIR)/jicbench : $(JAVA_SUBDIR)/jicbench.java $(JAVA_SUBDIR)/libic.so
	cd $(JAVA_SUBDIR) && javac jicbench.java && java -Djava.library.path=. jicbench

icapp: $(SRC)icapp.o libic.a $(OB)
	$(CL) $^ $(LDFLAGS) -o icapp

myapp: myapp.o libic.a
	$(CC) $^ $(LDFLAGS) -o myapp

mycpp: mycpp.o libic.a
	$(CXX) $^ $(LDFLAGS) -o mycpp

.c.o:
	$(CC) -O3 $(CFLAGS) $< -c -o $@

.cc.o:
	$(CXX) -O2 $(CXXFLAGS) $< -c -o $@

.cpp.o:
	$(CXX) -O2 $(CXXFLAGS) $< -c -o $@

ifeq ($(OS),Windows_NT)
clean:
	del /S *.o
	del /S *~
else
clean:
	@find . -type f -name "*\.o" -delete -or -name "*\~" -delete -or -name "core" -delete -or -name "icbench" -delete -or -name "libic.a" -delete
	@find . -type f -name "icbench" -delete -or -name "idxqry" -delete -or -name "idxseg" -delete -or -name "idxcr" -delete -or -name "icapp" -delete
endif
