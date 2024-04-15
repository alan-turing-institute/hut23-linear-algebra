/* vim: noet:ts=2:sts=2:sw=2 */ 

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <time.h>

#include "matrix.h"
#include "operations.h"
#include "load.h"
#include "tests.h"

#define BENCHMARK_REPEAT (32768)

int main(int argc, char *argv[]) {
	Matrix *A;
	Matrix *B;
	Matrix *C;
	Matrix *D;
	bool result;
	uint32_t total;

	// Play around with the API
	printf("Example matrix manipulation...\n");	
	A = matrix_load("../testdata/matrix-a.npy");
	B = matrix_load("../testdata/matrix-b.npy");
	C = matrix_load("../testdata/matrix-c.npy");
	D = new_matrix(4, 4);
	result = multiply(D, A, B);
	result = equals(C, D);
	printf("Result of A * B:\n");
	matrix_print(C);
	printf("Matches expected result: %s\n", result ? "Yes" : "No");

	A = delete_matrix(A);
	B = delete_matrix(B);
	C = delete_matrix(C);
	D = delete_matrix(D);

	Matrices *a = new_matrices(0);
	Matrices *b = new_matrices(0);
	Matrices *c = new_matrices(0);

	total = tests_load_matrices(a, b, c);
	Matrices *d = new_matrices(total);
	result = tests_allocate_results(c, d);

	// Perform 512 multiplications and compare against the results from NumPy
	printf("Performing unit tests...\n");
	uint32_t passed = 0;
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
	printf("Multiplication tests passed: %u out of %u\n", passed, total);

	// Measure time taken to perform 16777216 multiplications
	printf("Benchmarking...\n");
	clock_t start_time = clock();
	for (uint32_t count = 0; count < BENCHMARK_REPEAT; ++count) {
		for (uint32_t index = 0; index < total; ++index) {
			multiply(d->matrices[index].matrix, a->matrices[index].matrix, b->matrices[index].matrix);
		}
	}
	clock_t end_time = clock();
	double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	uint32_t operations = total * BENCHMARK_REPEAT;
	printf("Time taken to perform %u multiply operations: %.02f seconds\n", operations, elapsed);
	double ops_per_sec = operations / elapsed;
	printf("Equivalent to %.02f operations per second\n", ops_per_sec);

	a = delete_matrices(a);
	b = delete_matrices(b);
	c = delete_matrices(c);
	d = delete_matrices(d);

	return EXIT_SUCCESS;
}


