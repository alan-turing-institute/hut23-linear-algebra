/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdint.h>
#include <cmath>
#include <sycl/sycl.hpp>

#include "utils.hpp"

#ifndef __MATRIX_MATRIX_H
#define __MATRIX_MATRIX_H (1)

// Column major
typedef struct _Matrix {
	uint32_t height;
	uint32_t width;
	uint32_t stride;
	double *elements;
} Matrix;

Matrix * new_matrix(sycl::queue &Q, uint16_t height, uint16_t width);
Matrix * delete_matrix(Matrix *A, sycl::queue &Q);
Matrix * new_matrix_identity(sycl::queue &Q, uint16_t height, uint16_t width);
void matrix_print(Matrix *A, sycl::queue &Q);
void matrix_fill(Matrix *A, sycl::queue &Q, Rand * const rand);
void matrix_entries_set(Matrix *A, sycl::queue &Q, double *entries, uint32_t size);

#endif /* __MATRIX_MATRIX_H */
