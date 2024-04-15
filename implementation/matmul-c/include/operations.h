/* vim: noet:ts=2:sts=2:sw=2 */ 

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "matrix.h"

#ifndef __MATRIX_OPERATIONS_H
#define __MATRIX_OPERATIONS_H (1)

inline double entry_get(Matrix *A, uint16_t col, uint16_t row) {
	double element = NAN;

	if ((col < A->width) && (row < A->height)) {
		element = A->elements[(row * A->width) + col];
	}
	
	return element;
}

inline void entry_set(Matrix *A, uint16_t col, uint16_t row, double value) {
	if ((col < A->width) && (row < A->height)) {
		A->elements[(row * A->width) + col] = value;
	}
}

bool equals(Matrix *A, Matrix *B);
bool multiply(Matrix *result, Matrix *A, Matrix *B);
bool add(Matrix *result, Matrix *A, Matrix *B);
bool scalar_multiply(Matrix *result, double scalar, Matrix *A);

#endif /* __MATRIX_OPERATIONS_H */
