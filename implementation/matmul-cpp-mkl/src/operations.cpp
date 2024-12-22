/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#include "operations.hpp"

#define COMPARISON_ACCURACY (0.0000001)

bool equals(Matrix *A, Matrix *B) {
	bool result = A && B && (A->width == B->width) && (A->height == B->height);
	uint32_t size = A->width * A->height;
	uint32_t offset = 0;	
	double difference;

	while ((offset < size) && result) {
		difference = fabs((A->elements[offset] - B->elements[offset]));
		result = (difference < COMPARISON_ACCURACY);
		++offset;
	}
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
bool multiply(Matrix *result, Matrix *A, Matrix *B) {
	// Ensure the matrices exist and have suitable sizes
	bool success = A && B && result && (A->width == B->height) && (result->width == B->width) && (result->height == A->height);
	
	if (success) {
		uint32_t apos = 0;
		uint32_t bpos = 0;
		uint32_t size = result->height * result->width;
		// Step through all the entries in the result matrix
		for (uint32_t cpos = 0; cpos < size; ++cpos) {
			// For A start at the beginning of the row
			apos = (cpos / result->width) * A->width;
			// For B start at the top of a column
			bpos = cpos % result->width;
			// Accumulator for the products
			double element = 0.0f;
			// For each entry in the result, sum the product of row/column pairs
			for (uint32_t pos = 0; pos < A->width; ++pos) {
				// Accumulate the products
				element += A->elements[apos] * B->elements[bpos];
				// Row stride of 1
				apos += 1;
				// Column stride of "width of B"
				bpos += B->width;
			}
			// Write out the resulting element
			result->elements[cpos] = element;
		}
	}
	return success;
}

bool add(Matrix *result, Matrix *A, Matrix *B) {
	bool success = A && B && result && (A->height == B->height) && (A->width == B->width) && (result->height == A->height) && (result->width == A->width);
	
	if (success) {
		uint32_t size = A->height * A->width;
		for (uint32_t index = 0; index < size; ++index) {
			result->elements[index] = A->elements[index] + B->elements[index];
		}
	}
	return success;
}

bool scalar_multiply(Matrix *result, double scalar, Matrix *A) {
	bool success = A && result && (result->height == A->height) && (result->width == A->width);
	
	if (success) {
		uint32_t size = A->height * A->width;
		for (uint32_t index = 0; index < size; ++index) {
			result->elements[index] *= scalar;
		}
	}
	return success;
}

