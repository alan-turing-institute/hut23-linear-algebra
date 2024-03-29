# vim: noet:ts=2:sts=2:sw=2

# SPDX-License-Identifier: MIT
# Copyright © 2024 David Llewellyn-Jones

CC      = gcc
CFLAGS  = -g -Wall -Werror -O3 -Iinclude -I../matmul-c/include
RM      = rm -f
CLIBS   = -larchive
UNAME   = $(shell uname -s)

ifeq ($(UNAME),Darwin)
	CFLAGS += -I/opt/homebrew/opt/libarchive/include
endif

default: all

all: matmul-asm

test: matmul-asm
	./matmul-asm

matmul-asm: \
	../matmul-c/main.c \
	../matmul-c/src/load.c \
	../matmul-c/src/matrix.c \
	src/operations.c \
	src/operations.S \
	../matmul-c/src/parse_header.c \
	../matmul-c/src/tests.c
	$(CC) $(CFLAGS) -o$@ $^ $(CLIBS)

clean veryclean:
	$(RM) matmul-asm
