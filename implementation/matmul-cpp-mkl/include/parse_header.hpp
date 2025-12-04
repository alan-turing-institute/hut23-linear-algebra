/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef __MATRIX_PARSE_HEADER_H
#define __MATRIX_PARSE_HEADER_H (1)

typedef struct _Header {
	uint16_t height;
	uint16_t width;
} Header;

bool read_header(Header *result, char *header, size_t length);

#endif /* __MATRIX_PARSE_HEADER_H */

