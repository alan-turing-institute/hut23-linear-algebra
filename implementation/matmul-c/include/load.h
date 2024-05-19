/* vim: noet:ts=2:sts=2:sw=2 */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include "matrix.h"

#ifndef __MATRIX_LOAD_H
#define __MATRIX_LOAD_H (1)

typedef struct _NamedMatrix {
	char *name;
	Matrix *matrix;
} NamedMatrix;

typedef struct _Matrices {
	uint32_t count;
	NamedMatrix *matrices;
} Matrices;

Matrix * matrix_load(char *filename);
void matrix_npz_load(char *filename, Matrices *matrices);
Matrices *new_matrices(uint32_t count);
Matrices *delete_matrices(Matrices *matrices);

#endif /* __MATRIX_LOAD_H */
