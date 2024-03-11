/* vim: noet:ts=2:sts=2:sw=2 */ 

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

Matrix * new_matrix(uint16_t height, uint16_t width) {
	Matrix *A = malloc(sizeof(Matrix));

	if (A) {
		A->height = height;
		A->width = width;
		A->elements = calloc(width * height, sizeof(double));
	}
	return A;
}

Matrix * delete_matrix(Matrix *A) {
	if (A) {
		if (A->elements) {
			free(A->elements);
		}
		free(A);
	}
	return NULL;
}

Matrix * new_matrix_identity(uint16_t height, uint16_t width) {
	Matrix *A = new_matrix(height, width);
	uint32_t diag = width <= height ? width : height;

	if (A) {
		double *pos = A->elements;
		for (uint32_t step = 0; step < diag; ++step) {
			*pos = 1;
			pos += A->width + 1;
		}
	}
	return A;
}

void matrix_print(Matrix *A) {
	printf("Size: %d, %d\n", A->height, A->width);
	if (A) {
		for (uint32_t row = 0; row < A->height; ++row) {
			for (uint32_t col = 0; col < A->width; ++col) {
				printf("%8.0f ", A->elements[(row * A->width) + col]);
			}
			printf("\n");
		}
		printf("\n");
	}
}



