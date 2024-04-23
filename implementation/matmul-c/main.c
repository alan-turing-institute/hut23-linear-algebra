/* vim: noet:ts=2:sts=2:sw=2 */ 

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <time.h>

#include "matrix.h"
#include "operations.h"
#include "load.h"
#include "tests.h"
#include "threadpool.h"

#define BENCHMARK_REPEAT_SMALL (32768)
#define BENCHMARK_REPEAT_LARGE (1)

#define HEIGHT (2048)
#define WIDTH (2048)

int main(int argc, char *argv[]) {
	Matrix *A;
	Matrix *B;
	Matrix *C;
	Matrix *D;
	bool result;
	uint32_t total;

	ThreadPool *pool = new_threadpool();

	// Play around with the API
	printf("Example matrix manipulation...\n");	
	A = matrix_load("../testdata/matrix-a.npy");
	B = matrix_load("../testdata/matrix-b.npy");
	C = matrix_load("../testdata/matrix-c.npy");
	D = new_matrix(4, 4);

	printf("pre multiply\n");
	result = multiply_parallel(pool, D, A, B);
	printf("Post multiply\n");

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

	// Measure time taken to perform 16777216 multiplications
	struct timespec start_time, end_time;
	uint32_t operations;
	double elapsed;
	double ops_per_sec;

	// Create a pair of big random matrices
	A = new_matrix(HEIGHT, WIDTH);
	B = new_matrix(WIDTH, HEIGHT);
	D = new_matrix(HEIGHT, HEIGHT);
	matrix_fill(A, 8);
	matrix_fill(B, 16);
	operations = BENCHMARK_REPEAT_LARGE;

	printf("Benchmarking...\n");

	clock_gettime(CLOCK_MONOTONIC, &start_time);
	for (uint32_t count = 0; count < operations; ++count) {
		multiply(D, A, B);
	}
	clock_gettime(CLOCK_MONOTONIC, &end_time);
	elapsed = (end_time.tv_sec - start_time.tv_sec);
	elapsed += (end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;

	printf("Time taken to perform %u standard large multiply operations: %.02f seconds\n", operations, elapsed);
	ops_per_sec = operations / elapsed;
	printf("Equivalent to %.02f operations per second\n", ops_per_sec);

	clock_gettime(CLOCK_MONOTONIC, &start_time);
	for (uint32_t count = 0; count < operations; ++count) {
		multiply_parallel(pool, D, A, B);
	}
	clock_gettime(CLOCK_MONOTONIC, &end_time);
	elapsed = (end_time.tv_sec - start_time.tv_sec);
	elapsed += (end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;

	printf("Time taken to perform %u standard large parallel multiply operations: %.02f seconds\n", operations, elapsed);
	ops_per_sec = operations / elapsed;
	printf("Equivalent to %.02f operations per second\n", ops_per_sec);

	A = delete_matrix(A);
	B = delete_matrix(B);
	D = delete_matrix(D);

	clock_gettime(CLOCK_MONOTONIC, &start_time);
	for (uint32_t count = 0; count < BENCHMARK_REPEAT_SMALL; ++count) {
		for (uint32_t index = 0; index < total; ++index) {
			multiply(d->matrices[index].matrix, a->matrices[index].matrix, b->matrices[index].matrix);
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end_time);

	elapsed = (end_time.tv_sec - start_time.tv_sec);
	elapsed += (end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;

	operations = total * BENCHMARK_REPEAT_SMALL;
	printf("Time taken to perform %u multiply operations: %.02f seconds\n", operations, elapsed);
	ops_per_sec = operations / elapsed;
	printf("Equivalent to %.02f operations per second\n", ops_per_sec);

	a = delete_matrices(a);
	b = delete_matrices(b);
	c = delete_matrices(c);
	d = delete_matrices(d);

	pool = delete_threadpool(pool);

	return EXIT_SUCCESS;
}


