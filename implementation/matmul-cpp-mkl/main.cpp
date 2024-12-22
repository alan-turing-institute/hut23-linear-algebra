/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <time.h>

#include "matrix.hpp"
#include "operations.hpp"
#include "load.hpp"
#include "tests.hpp"
#include "threadpool.hpp"
#include "benchmarks.hpp"

int main(int argc, char *argv[]) {
	Matrix *A;
	Matrix *B;
	Matrix *C;
	Matrix *D;
	bool result;
	uint32_t total;

	ThreadPool *pool = new_threadpool(10);

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
	tests_compare(a, b, c, d, pool);

	// Benchmark square matrix multiplications single-threaded
	printf("Square matrix benchmark single-threaded\n");
	benchmark_multiply_square(NULL);

	// Benchmark square matrix multiplications using threads
	printf("Square matrix benchmark multi-threaded\n");
	benchmark_multiply_square(pool);

	// Benchmark large matrix multiplications
	//benchmarks_multiply_big(pool);

	// Measure time taken to perform 16777216 multiplications
	//benchmarks_multiply_small(a, b, d);

	a = delete_matrices(a);
	b = delete_matrices(b);
	c = delete_matrices(c);
	d = delete_matrices(d);

	pool = delete_threadpool(pool);

	return EXIT_SUCCESS;
}


