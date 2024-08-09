/* vim: noet:ts=2:sts=2:sw=2 */ 

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdlib.h>

#include "operations.h"

#include "tests.h"

uint32_t tests_load_matrices(Matrices *a, Matrices *b, Matrices *c) {
	uint32_t total = 0;

	printf("Reading test matrices from file\n");	

	Matrices *matrices = new_matrices(0);
	matrix_npz_load("../testdata/matrices.npz", matrices);
	if ((matrices->count % 3) == 0) {
		total = matrices->count / 3;
	}
	else {
		printf("Test matrices must come in A, B, C triplets\n");
	}

	a->matrices = realloc(a->matrices, sizeof(NamedMatrix) * total);
	a->count = total;
	b->matrices = realloc(b->matrices, sizeof(NamedMatrix) * total);
	b->count = total;
	c->matrices = realloc(c->matrices, sizeof(NamedMatrix) * total);
	c->count = total;

	NamedMatrix *from;
	NamedMatrix *to;
	for (uint32_t index = 0; index < matrices->count; ++index) {
		from = &matrices->matrices[index];
		to = NULL;
		int read = 0;
		uint32_t count = 0;
		read = sscanf(from->name, "a_%d.npy", &count);
		if ((read == 1) && (count < total)) {
			to = &a->matrices[count];
		}
		read = sscanf(from->name, "b_%d.npy", &count);
		if ((read == 1) && (count < total)) {
			to = &b->matrices[count];
		}
		read = sscanf(from->name, "c_%d.npy", &count);
		if ((read == 1) && (count < total)) {
			to = &c->matrices[count];
		}
		if (to) {
			to->name = from->name;
			from->name = NULL;
			to->matrix = from->matrix;
			from->matrix = NULL;
		}
	}

	matrices = delete_matrices(matrices);

	for (uint32_t index = 0; index < total; ++index) {
		if (!a->matrices[index].matrix || !b->matrices[index].matrix || !c->matrices[index].matrix) {
			printf("Missing matrix: %u\n", index);
		}
	}

	return total;
}

bool tests_allocate_results(Matrices *c, Matrices *d) {
	for (uint32_t index = 0; index < c->count; ++index) {
		d->matrices[index].matrix = new_matrix(c->matrices[index].matrix->height, c->matrices[index].matrix->width);
	}
	return true;
}

// Perform 512 multiplications and compare against the results from NumPy
void tests_compare(Matrices *a, Matrices *b, Matrices *c, Matrices *d, ThreadPool *pool) {
	printf("Performing unit tests...\n");
	uint32_t passed = 0;
	uint32_t total = d->count;
	bool result;

	for (uint32_t index = 0; index < total; ++index) {
		result = multiply(d->matrices[index].matrix, a->matrices[index].matrix, b->matrices[index].matrix);
		result = result && equals(c->matrices[index].matrix, d->matrices[index].matrix);
		if (result) {
			passed += 1;
		}
		else {
			printf("Incorrect result\n");
			matrix_print(c->matrices[index].matrix);
			matrix_print(d->matrices[index].matrix);
		}
	}
	for (uint32_t index = 0; index < total; ++index) {
		result = multiply_parallel(pool, d->matrices[index].matrix, a->matrices[index].matrix, b->matrices[index].matrix);
		result = result && equals(c->matrices[index].matrix, d->matrices[index].matrix);
		if (result) {
			passed += 1;
		}
		else {
			printf("Incorrect result\n");
			matrix_print(c->matrices[index].matrix);
			matrix_print(d->matrices[index].matrix);
		}
	}
	printf("Multiplication tests passed: %u out of %u\n", passed, total * 2);
}


