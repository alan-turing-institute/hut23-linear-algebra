/* vim: noet:ts=2:sts=2:sw=2 */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#include "../matmul-c/operations.h"

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
#if defined(__aarch64__) || defined(_M_ARM64)
	// All registers are temporary but we still need to keep track of them
	uint32_t awidth, bwidth, rwidth, aheight, bheight, rheight;
	uint32_t bstart, pos, apos, bpos, cpos, size;
	void *adata, *bdata, *rdata;
	double element, e0, e1;

	__asm__ goto (
		// Ensure the matrices exist
		// bool success = A && B && result;
		"cmp %w[result], #0x0\n\t"
		"ccmp %w[A], #0x0, #0x4, ne\n\t"
		"ccmp %w[B], #0x0, #0x4, ne\n\t"
		"beq %l[failure]\n\t"
		:
		: [result] "r" (result), [A] "r" (A), [B] "r" (B)
		: "cc"
		: failure
	);

	__asm__ volatile (
		// Load matrix dimensions from the data structure
		"ldr %w[awidth], [%[A], #4]\n\t"
		"ldr %w[bwidth], [%[B], #4]\n\t"
		"ldr %w[rwidth], [%[result], #4]\n\t"
		"ldr %w[aheight], [%[A], #0]\n\t"
		"ldr %w[bheight], [%[B], #0]\n\t"
		"ldr %w[rheight], [%[result], #0]\n\t"
		// Load pointer to the matrix elements from the data structure
		"ldr %x[adata], [%[A], #8]\n\t"
		"ldr %x[bdata], [%[B], #8]\n\t"
		"ldr %x[rdata], [%[result], #8]\n\t"
		// size = result->height * result->width;
		"mul %w[size], %w[bwidth], %w[aheight]\n\t"
		: [awidth] "=r" (awidth), [aheight] "=r" (aheight), [adata] "=r" (adata),
		  [bwidth] "=r" (bwidth), [bheight] "=r" (bheight), [bdata] "=r" (bdata),
		  [rwidth] "=r" (rwidth), [rheight] "=r" (rheight), [rdata] "=r" (rdata),
		  [size] "=r" (size)
		: [A] "r" (A), [B] "r" (B), [result] "r" (result)
	);

	__asm__ goto (
		// Ensure the matrices have suitable sizes
		// bool success = (A->width == B->height)
		//   && (result->width == B->width)
		//   && (result->height == A->height);
		"cmp %w[awidth], #0x0\n\t"
		"ccmp %w[bwidth], #0x0, #0x4, ne\n\t"
		"ccmp %w[aheight], #0x0, #0x4, ne\n\t"
		"beq %l[failure]\n\t"
		"cmp %w[awidth], %w[bheight]\n\t"
		"ccmp %w[rwidth], %w[bwidth], #0x0, eq\n\t"
		"ccmp %w[rheight], %w[aheight], #0x0, eq\n\t"
		"bne %l[failure]\n\t"
		:
		: [awidth] "r" (awidth), [aheight] "r" (aheight),
		  [bwidth] "r" (bwidth), [bheight] "r" (bheight),
		  [rwidth] "r" (rwidth), [rheight] "r" (rheight)
		: "cc"
		: failure
	);

	__asm__ volatile (
		"mov %w[apos], #0x0\n\t"
		"mov %w[bpos], #0x0\n\t"
		// Start outer loop
		// Step through all the entries in the result matrix
		// for (uint32_t cpos = 0; cpos < size; ++cpos) {
		"mov %w[cpos], #0x0\n\t"
		"mov %w[bstart], #0x0\n\t"
		: [apos] "=r" (apos), [bpos] "=r" (bpos), [cpos] "=r" (cpos),
		  [bstart] "=r" (bstart)
	);

start_outer:

	__asm__ volatile (
		// For A start at the beginning of the row
		// apos = (cpos / B->width) * A->width;
		"udiv %w[apos], %w[cpos], %w[bwidth]\n\t"
		"mul %w[apos], %w[apos], %w[awidth]\n\t"
		//"mov %w[apos], %w[astart]\n\t"
		// For B start at the top of a column
		// bpos = cpos % B->width;
		//"msub %w[bpos], %w[bpos], %w[bwidth], %w[cpos]\n\t"
		"mov %w[bpos], %w[bstart]\n\t"
		// Accumulator for the products
		// double element = 0;
		"movi %[element].4h, #0x0\n\t"
		// Start inner loop
		// For each entry in the result, sum the product of row/column pairs
		// for (uint32_t pos = 0; pos < A->width; ++pos) {
		"mov %w[pos], %w[awidth]\n\t"
		: [apos] "=r" (apos), [bpos] "+r" (bpos),
		  [pos] "=r" (pos), [element] "=w" (element)
		: [awidth] "r" (awidth), [bwidth] "r" (bwidth),
		  [cpos] "r" (cpos), [bstart] "r" (bstart)
	);

start_inner:

	__asm__ volatile (
		// Accumulate the products
		// element += A->elements[apos] * B->elements[bpos];
		"ldr %d[e0], [%x[adata], %w[apos], uxtw #3]\n\t"
		"ldr %d[e1], [%x[bdata], %w[bpos], uxtw #3]\n\t"
		"fmadd %d[element], %d[e0], %d[e1], %d[element]\n\t"
		// Row stride of 1
		// apos += 1;
		"add %w[apos], %w[apos], #1\n\t"
		// Column stride of "width of B"
		// bpos += B->width;
		"add %w[bpos], %w[bpos], %w[bwidth]\n\t"
		: [element] "+w" (element), [e0] "=w" (e0), [e1] "=w" (e1),
		  [bpos] "+r" (bpos)
		: [A] "r" (A), [B] "r" (B), [apos] "r" (apos), [bwidth] "r" (bwidth),
		  [adata] "r" (adata), [bdata] "r" (bdata)
	);

	__asm__ goto (
		// End inner loop
		// for (uint32_t pos = 0; pos < A->width; ++pos) {
		"subs %w[pos], %w[pos], #0x1\n\t"
		"bgt %l[start_inner]\n\t"
		// Write out the resulting element
		// result->elements[cpos] = element;
		"str %d[element], [%x[rdata], %w[cpos], uxtw #3]\n\t"

		// For B start at the top of a column
		// bpos = cpos % B->width;
		"add %w[bstart], %w[bstart], #0x1\n\t"
		"cmp %w[bstart], %w[bwidth]\n\t"
		"csel %w[bstart], %w[pos], %w[bstart], ge\n\t"

		// Note: we've run out of registers, so using this slows things down;
		// we perform the calculation each time at the top of the loop instead
		// For A start at the beginning of the row
		// apos = (cpos / B->width) * A->width;
		//"add %w[pos], %w[astart], %w[awidth]\n\t"
		//"csel %w[astart], %w[pos], %w[astart], ge\n\t"

		// End outer loop
		// for (uint32_t cpos = 0; cpos < size; ++cpos) {
		"add %w[cpos], %w[cpos], 0x1\n\t"
		"cmp %w[cpos], %w[size] \n\t"
		"blt %l[start_outer]\n\t"
		:
		: [pos] "r" (pos), [cpos] "r" (cpos), [bstart] "r" (bstart),
		  [awidth] "r" (awidth), [bwidth] "r" (bwidth),
		  [result] "r" (result), [element] "w" (element),
		  [rdata] "r" (rdata), [size] "r" (size)
		: "cc"
		: start_inner, start_outer
	);

	return true;
failure:
#else
	#error Only aarch64 asm supported
#endif
	return false;
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

