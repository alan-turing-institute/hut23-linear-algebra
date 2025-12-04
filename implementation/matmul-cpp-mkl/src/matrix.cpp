/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdio.h>
#include <stdlib.h>
#include <sycl/sycl.hpp>
#include <oneapi/mkl.hpp>

#include "matrix.hpp"

// Testing with STRIDE I didn't see a noticeable difference to the timings
// while at the same time it increases memory usage substantially
// So the benchmarks run better if it's disabled
//#define STRIDE 1
#undef STRIDE

Matrix * new_matrix(sycl::queue &Q, uint16_t height, uint16_t width) {
	Matrix *A = static_cast<Matrix *>(malloc(sizeof(Matrix)));
	uint32_t size;
	double *host_elements;

	if (A) {
		A->height = height;
		A->width = width;
		A->stride = width;

#ifdef STRIDE
		// Quantize the stride to increase performance
		A->stride *= sizeof(double);
		A->stride = ((A->stride + 511) & ~511) + 256;
		A->stride /= sizeof(double);
#endif

		size = height * A->stride;
		A->elements = sycl::malloc_device<double>(size, Q);

		host_elements = sycl::malloc_host<double>(size, Q);
		for (uint32_t index = 0; index < size; ++index) {
			host_elements[index] = 0;
		}
		Q.copy(host_elements, A->elements, size).wait();
		sycl::free(host_elements, Q);
	}
	return A;
}

Matrix * delete_matrix(Matrix *A, sycl::queue &Q) {
	if (A) {
		if (A->elements) {
			sycl::free(A->elements, Q);
			Q.wait();
		}
		free(A);
	}
	return NULL;
}

Matrix * new_matrix_identity(sycl::queue &Q, uint16_t height, uint16_t width) {
	Matrix *A = new_matrix(Q, height, width);
	uint32_t size;
	double *host_elements;

	if (A) {
		size = height * A->stride;
		host_elements = sycl::malloc_host<double>(size, Q);

		for (uint32_t index = 0; index < size; ++index) {
			host_elements[index] = (index % A->stride == index / A->stride) ? 1 : 0;
		}
		Q.copy(host_elements, A->elements, size).wait();
		sycl::free(host_elements, Q);
	}
	return A;
}

void matrix_print(Matrix *A, sycl::queue &Q) {
	printf("Size: %d, %d\n", A->height, A->width);
	if (A) {
		uint32_t size = A->height * A->stride;
		double *host_elements = sycl::malloc_host<double>(size, Q);
		Q.copy(A->elements, host_elements, size).wait();

		for (uint32_t row = 0; row < A->height; ++row) {
			for (uint32_t col = 0; col < A->width; ++col) {
				printf("%4.4f ", host_elements[(row * A->stride) + col]);
			}
			printf("\n");
		}
		printf("\n");
		sycl::free(host_elements, Q);
	}
}

void matrix_fill(Matrix *A, sycl::queue &Q, Rand * const rand) {
	if (A) {
		uint32_t size = A->height * A->stride;
		double *host_elements = sycl::malloc_host<double>(size, Q);
		uint32_t offset = 0;

		for (uint32_t row = 0; row < A->height; ++row) {
			for (uint32_t col = 0; col < A->width; ++col) {
				host_elements[offset + col] = rand_value(rand);
			}
			for (uint32_t col = A->width; col < A->stride; ++col) {
				host_elements[offset + col] = 0;
			}
			offset += A->stride;
		}
		Q.copy(host_elements, A->elements, size).wait();
		sycl::free(host_elements, Q);
	}
	Q.wait();
}

void matrix_entries_set(Matrix *A, sycl::queue &Q, double *entries, uint32_t size) {
	if (A->width == A->stride) {
		Q.copy(entries, A->elements, size);
	}
	else {
		uint32_t host_offset = 0;
		uint32_t device_offset = 0;
		for (uint32_t row = 0; row < A->height; ++row) {
			Q.copy(entries + host_offset, A->elements + device_offset, A->width);
			host_offset += A->width;
			device_offset += A->stride;
		}
	}
	Q.wait();
}

