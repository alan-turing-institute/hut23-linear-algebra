/* vim: noet:ts=2:sts=2:sw=2 */ 

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdint.h>

#ifndef __MATRIX_MATRIX_H
#define __MATRIX_MATRIX_H (1)

typedef struct _Matrix {
	uint32_t height;
	uint32_t width;
	double *elements;
} Matrix;

Matrix * new_matrix(uint16_t height, uint16_t width);
Matrix * delete_matrix(Matrix *A);
Matrix * new_matrix_identity(uint16_t height, uint16_t width);
void matrix_print(Matrix *A);
void matrix_fill(Matrix *A, uint32_t seed);

#endif /* __MATRIX_MATRIX_H */
