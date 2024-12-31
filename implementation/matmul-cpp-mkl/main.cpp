/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <time.h>
#include <sycl/sycl.hpp>

#include "matrix.hpp"
#include "operations.hpp"
#include "load.hpp"
#include "tests.hpp"
#include "benchmarks.hpp"

#define BENCHMARK_REPEAT (32768)

int main(int argc, char *argv[]) {
	Matrix *A;
	Matrix *B;
	Matrix *C;
	Matrix *D;
	bool result;
	uint32_t total;

	sycl::queue Q;

	printf("Device: %s\n", Q.get_device().get_info<sycl::info::device::name>().c_str());
	printf("Compute units: %d\n", Q.get_device().get_info<sycl::info::device::max_compute_units>());

	// Play around with the API
	printf("Example matrix manipulation...\n");
	A = matrix_load(Q, "../testdata/matrix-a.npy");
	B = matrix_load(Q, "../testdata/matrix-b.npy");
	C = matrix_load(Q, "../testdata/matrix-c.npy");
	D = new_matrix(Q, 4, 4);

	printf("pre multiply\n");
	result = multiply(Q, D, A, B);
	result = equals(Q, C, D);
	printf("Post multiply\n");

	printf("Result of A * B:\n");
	matrix_print(D, Q);
	printf("Matches expected result: %s\n", result ? "Yes" : "No");

	A = delete_matrix(A, Q);
	B = delete_matrix(B, Q);
	C = delete_matrix(C, Q);
	D = delete_matrix(D, Q);

	Matrices *a = new_matrices(0);
	Matrices *b = new_matrices(0);
	Matrices *c = new_matrices(0);

	total = tests_load_matrices(Q, a, b, c);
	Matrices *d = new_matrices(total);
	result = tests_allocate_results(Q, c, d);

	// Perform 512 multiplications and compare ag	ainst the results from NumPy
	tests_compare(Q, a, b, c, d);

	// Benchmark square matrix multiplications using threads
	printf("Square matrix benchmark oneMKL\n");
	benchmark_multiply_square(Q);

	// Benchmark large matrix multiplications
	//benchmarks_multiply_big(Q);

	// Measure time taken to perform 16777216 multiplications
	benchmarks_multiply_small(Q, a, b, d);

	a = delete_matrices(a, Q);
	b = delete_matrices(b, Q);
	c = delete_matrices(c, Q);
	d = delete_matrices(d, Q);

	return EXIT_SUCCESS;
}


