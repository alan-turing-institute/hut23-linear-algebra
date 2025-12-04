/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <sycl/sycl.hpp>

#include "matrix.hpp"

#ifndef __MATRIX_OPERATIONS_H
#define __MATRIX_OPERATIONS_H (1)

bool equals(sycl::queue &Q, Matrix *A, Matrix *B);
bool multiply(sycl::queue &Q, Matrix *result, Matrix *A, Matrix *B);
bool add(sycl::queue &Q, Matrix *result, Matrix *A, Matrix *B);
bool scalar_multiply(sycl::queue &Q, Matrix *result, double scalar, Matrix *A);

#endif /* __MATRIX_OPERATIONS_H */
