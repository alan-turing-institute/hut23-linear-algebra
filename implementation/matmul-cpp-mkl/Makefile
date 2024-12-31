# vim: set noet ts=2 sts=2 sw=2:

# SPDX-License-Identifier: MIT
# Copyright © 2024 David Llewellyn-Jones

# See the following page for compiler and linker flags:
# https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-link-line-advisor.html

CC      = icpx
CFLAGS  = -fsycl -I../../../common -Iinclude -O3 -DMKL_ILP64 -qmkl-ilp64=parallel
RM      = rm -f
CLIBS   = -lsycl -lOpenCL -lpthread -lm -ldl -larchive
UNAME   = $(shell uname -s)

ifeq ($(UNAME),Darwin)
	CFLAGS += -I/opt/homebrew/opt/libarchive/include
endif

default: all

all: matmul-cpp-mkl

test: matmul-cpp-mkl
	KMP_AFFINITY=compact MKL_NUM_THREADS=10 ./matmul-cpp-mkl

matmul-cpp-mkl: \
	main.cpp \
	src/load.cpp \
	src/matrix.cpp \
	src/operations.cpp \
	src/parse_header.cpp \
	src/utils.cpp \
	src/benchmarks.cpp \
	src/store.cpp \
	src/tests.cpp
	$(CC) $(CFLAGS) -o$@ $^ $(CLIBS)

clean veryclean:
	$(RM) matmul-cpp-mkl
