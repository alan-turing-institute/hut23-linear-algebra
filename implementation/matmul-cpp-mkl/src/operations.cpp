/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <sycl/sycl.hpp>
#include <oneapi/mkl.hpp>

#include "operations.hpp"

#define COMPARISON_ACCURACY (0.0000001)

bool equals(sycl::queue &Q, Matrix *A, Matrix *B) {
	// There's no oneMKL implementation so we do it the hard way
	bool result = A && B && (A->width == B->width) && (A->height == B->height);
	uint32_t size = A->stride * A->height;
	uint32_t offset_A = 0;
	uint32_t offset_B = 0;
	double difference;

  double *host_A = sycl::malloc_host<double>(size, Q);
  double *host_B = sycl::malloc_host<double>(size, Q);
	Q.copy(A->elements, host_A, size);
	Q.wait();
	Q.copy(B->elements, host_B, size);
	Q.wait();

	for (uint32_t row = 0; (row < A->height) && result; ++row) {
		for (uint32_t col = 0; (col < A->width) && result; ++col) {
			difference = fabs((host_A[offset_A + col] - host_B[offset_B + col]));
			result = (difference < COMPARISON_ACCURACY);
			if (!result) {
				printf("Difference: %f - %f = %f\n", host_A[offset_A + col], host_B[offset_B + col], difference);
			}
		}
		offset_A += A->stride;
		offset_B += B->stride;
	}

	sycl::free(host_A, Q);
	sycl::free(host_B, Q);
	return result;
}

/**
 * @brief Multiplies two matrices together
 *
 * @param result matrix to return the result in (should be pre-allocated)
 * @param A left-hand side of the matrix multiplication
 * @param B right-hand side of the matrix multiplication
 *
 * @return true if the matrices could be multiplied, false o/w
 */
bool multiply(sycl::queue &Q, Matrix *result, Matrix *A, Matrix *B) {
	// Ensure the matrices exist and have suitable sizes
	bool success = A && B && result && (A->width == B->height) && (result->width == B->width) && (result->height == A->height);

	if (success) {
		oneapi::mkl::blas::row_major::gemm(Q, oneapi::mkl::transpose::N, oneapi::mkl::transpose::N, A->height, B->width, A->width, 1.0, A->elements, A->stride, B->elements, B->stride, 0.0, result->elements, result->stride);
	}
	return success;
}

bool add(sycl::queue &Q, Matrix *result, Matrix *A, Matrix *B) {
	// Ensure the matrices exist and have suitable sizes
	bool success = A && B && result && (A->height == B->height) && (A->width == B->width) && (result->height == A->height) && (result->width == A->width);

	if (success) {
		oneapi::mkl::blas::column_major::omatadd(Q, oneapi::mkl::transpose::N, oneapi::mkl::transpose::N, result->height, result->width, 1.0, A->elements, A->stride, 1.0, B->elements, B->stride, result->elements, result->stride);
	}
	return success;
}

bool scalar_multiply(sycl::queue &Q, Matrix *result, double scalar, Matrix *A) {
	// Ensure the matrices exist and have suitable sizes
	bool success = A && result && (result->height == A->height) && (result->width == A->width);

	if (success) {
		oneapi::mkl::blas::column_major::omatadd(Q, oneapi::mkl::transpose::N, oneapi::mkl::transpose::N, result->height, result->width, scalar, A->elements, A->stride, 0.0, A->elements, A->stride, result->elements, result->stride);
	}
	return success;
}

