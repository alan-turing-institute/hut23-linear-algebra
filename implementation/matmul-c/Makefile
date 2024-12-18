# vim: noet:ts=2:sts=2:sw=2

# SPDX-License-Identifier: MIT
# Copyright © 2024 David Llewellyn-Jones

CC      = gcc
CFLAGS  = -g -Wall -Werror -O3 -Iinclude
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
	main.c \
	src/load.c \
	src/matrix.c \
	src/operations.c \
	src/parse_header.c \
	src/threadpool.c \
	src/utils.c \
	src/benchmarks.c \
	src/store.c \
	src/tests.c
	$(CC) $(CFLAGS) -o$@ $^ $(CLIBS)

clean veryclean:
	$(RM) matmul-c
