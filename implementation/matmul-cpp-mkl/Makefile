# vim: set noet ts=2 sts=2 sw=2:

# SPDX-License-Identifier: MIT
# Copyright © 2024 David Llewellyn-Jones

CC      = gcc
CFLAGS  = -g -Wall -Werror -O3 -Iinclude -x c
RM      = rm -f
CLIBS   = -larchive
UNAME   = $(shell uname -s)

ifeq ($(UNAME),Darwin)
	CFLAGS += -I/opt/homebrew/opt/libarchive/include
endif

default: all

all: matmul-c

test: matmul-c
	./matmul-c

matmul-c: \
	main.cpp \
	src/load.cpp \
	src/matrix.cpp \
	src/operations.cpp \
	src/parse_header.cpp \
	src/threadpool.cpp \
	src/utils.cpp \
	src/benchmarks.cpp \
	src/store.cpp \
	src/tests.cpp
	$(CC) $(CFLAGS) -o$@ $^ $(CLIBS)

clean veryclean:
	$(RM) matmul-c
