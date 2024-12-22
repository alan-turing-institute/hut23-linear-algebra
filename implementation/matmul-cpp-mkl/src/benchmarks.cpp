/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdlib.h>
#include <inttypes.h>

#include "matrix.hpp"
#include "load.hpp"
#include "operations.hpp"
#include "threadpool.hpp"
#include "store.hpp"

#include "benchmarks.hpp"

#define BENCHMARK_REPEAT_SMALL (32768)
#define BENCHMARK_REPEAT_LARGE (1)

#define HEIGHT (2048)
#define WIDTH (2048)

#define ALLOC_CHUNK (1024)

struct _Benchmark {
	struct timespec start_time;
	struct timespec end_time;
	uint64_t operations;
	double elapsed;
	double ops_per_sec;
	bool quiet;
};

Benchmark * new_benchmark() {
	Benchmark *benchmark = calloc(sizeof(Benchmark), sizeof(char));
	
	return benchmark;
}

Benchmark * delete_benchmark(Benchmark *benchmark) {
	if (benchmark) {
		free(benchmark);
	}
	return NULL;
}

void benchmark_set_quiet(Benchmark *benchmark, bool quiet) {
	benchmark->quiet = quiet;
}

void benchmarks_start(Benchmark *benchmark, uint32_t operations) {
	if (benchmark) {
		if (!benchmark->quiet) {
			printf("Benchmarking...\n");
		}
		benchmark->operations = operations;
		clock_gettime(CLOCK_MONOTONIC, &benchmark->start_time);
	}
}

void benchmarks_end(Benchmark *benchmark) {
	if (benchmark) {
		clock_gettime(CLOCK_MONOTONIC, &benchmark->end_time);
		benchmark->elapsed = (benchmark->end_time.tv_sec - benchmark->start_time.tv_sec);
		benchmark->elapsed += (benchmark->end_time.tv_nsec - benchmark->start_time.tv_nsec) / 1000000000.0;
		benchmark->ops_per_sec = benchmark->operations / benchmark->elapsed;

		if (!benchmark->quiet) {
			printf("Time taken to perform %" PRIu64 " operations: %.02f seconds\n", benchmark->operations, benchmark->elapsed);
			printf("Equivalent to %.02f operations per second\n", benchmark->ops_per_sec);
		}
	}
}

void benchmarks_multiply_big(ThreadPool *pool) {
	Benchmark *benchmark;
	Matrix *A;
	Matrix *B;
	Matrix *D;
	Rand *rand;

	printf("\n");
	printf("## Large matrix multiplication\n");

	benchmark = new_benchmark();
	benchmark_set_quiet(benchmark, true);
	rand = new_rand();

	for (uint32_t width = 128; width <= 2048; width += 128) {
		uint32_t diag = width;
		uint32_t height = width;
		uint32_t const repeat = BENCHMARK_REPEAT_LARGE * (width < 512 ? 1024 : width < 1024 ? 16 : 1);

		A = new_matrix(width, diag);
		B = new_matrix(diag, height);
		D = new_matrix(width, height);
		rand_seed(rand, 8);
		matrix_fill(A, rand);
		rand_seed(rand, 16);
		matrix_fill(B, rand);

		benchmarks_start(benchmark, repeat);
		for (uint32_t count = 0; count < repeat; ++count) {
			multiply(D, A, B);
		}
		benchmarks_end(benchmark);
		printf("Size: (%d, %d, %d), time per operation: %.02f seconds\n", width, diag, height, benchmark->elapsed / benchmark->operations);
		uint64_t order = (uint64_t)width * (uint64_t)diag * (uint64_t)height;
		double speed = (double)order / (benchmark->elapsed / benchmark->operations);
		printf("Order: %" PRIu64 ", elements per second: %.02f\n", order, speed);

		A = delete_matrix(A);
		B = delete_matrix(B);
		D = delete_matrix(D);
	}

	printf("\n");
	printf("## Large parallel matrix multiplication\n");

	for (uint32_t width = 128; width <= 2048; width += 128) {
		uint32_t diag = width;
		uint32_t height = width;
		uint32_t const repeat = BENCHMARK_REPEAT_LARGE * (width < 512 ? 1024 : width < 1024 ? 16 : 1);

		A = new_matrix(width, diag);
		B = new_matrix(diag, height);
		D = new_matrix(width, height);
		rand_seed(rand, 8);
		matrix_fill(A, rand);
		rand_seed(rand, 16);
		matrix_fill(B, rand);

		benchmarks_start(benchmark, repeat);
		for (uint32_t count = 0; count < repeat; ++count) {
			multiply_parallel(pool, D, A, B);
		}
		benchmarks_end(benchmark);
		printf("Size: (%d, %d, %d), time per operation: %.02f seconds\n", width, diag, height, benchmark->elapsed / benchmark->operations);
		uint64_t order = (uint64_t)width * (uint64_t)diag * (uint64_t)height;
		double speed = (double)order / (benchmark->elapsed / benchmark->operations);
		printf("Order: %" PRIu64 ", elements per second: %.02f\n", order, speed);

		A = delete_matrix(A);
		B = delete_matrix(B);
		D = delete_matrix(D);
	}

	rand = delete_rand(rand);
	benchmark = delete_benchmark(benchmark);
}

void benchmarks_multiply_small(Matrices *a, Matrices *b, Matrices *d) {
	Benchmark *benchmark;
	uint32_t total;

	benchmark = new_benchmark();
	total = d->count;

	printf("\n");
	printf("## Small matrix multiplication\n");
	benchmarks_start(benchmark, total * BENCHMARK_REPEAT_SMALL);

	for (uint32_t count = 0; count < BENCHMARK_REPEAT_SMALL; ++count) {
		for (uint32_t index = 0; index < total; ++index) {
			multiply(d->matrices[index].matrix, a->matrices[index].matrix, b->matrices[index].matrix);
		}
	}

	benchmarks_end(benchmark);

	benchmark = delete_benchmark(benchmark);
}

char const * get_cell(char const * const line, size_t *length) {
	char const * start = line;
	char delimeter;
	size_t pos;

	if (start[0] == '\"') {
		delimeter = '\"';
		++start;
	}
	else {
		delimeter = ',';
	}
	pos = 0;
	while (start[pos] != 0 && start[pos] != delimeter && start[pos] != '\n') {
		++pos;
	}

	if (length) {
		*length = pos;
	}
	return start;
}

void export_data(char const * const filename, char const * const method, double const * const data, uint32_t const size) {
	FILE * fh;
	uint32_t pos;
	char * line;
	size_t len;
	ssize_t read;
	size_t length;
	char const * line_method;
	Store * store;

	store = new_store(ALLOC_CHUNK);

	// Read the existing data from file
	fh = fopen(filename, "r");
	if (fh) {
		line = NULL;
		while (!feof(fh)) {
			read = getline(&line, &len, fh);
			if (read > 0) {
				line_method = get_cell(line, &length);
				if (strlen(method) != length || strncmp(method, line_method, length) != 0) {
					store_append(store, line, read);
				}
			}
		}
		free(line);
		fclose(fh);
	}

	// Append the new data
	store_printf_append(store, "\"%s\"", method);
	for (pos = 0; pos < size; ++pos) {
		store_printf_append(store, ",%g", data[pos]);
	}
	store_printf_append(store, "\n");

	printf("Exporting results to: %s\n", filename);
	fh = fopen(filename, "w");

	if (fh) {
		fwrite(store->data, sizeof(char), store->length, fh);
		fclose(fh);
		printf("Export complete\n");
	}
	else {
		printf("Export failed\n");
	}
}

void benchmark_multiply_square(ThreadPool *pool) {
	Benchmark *benchmark;
	uint32_t const dims[] = {2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192, 256, 384, 512, 768, 1024};
	uint32_t const dim_num = sizeof(dims) / sizeof(dims[0]);
	double times[dim_num];
	uint64_t const base_num_pairs = 2l << 31;
	Rand * rand;
	uint64_t pos;
	uint64_t index;
	Matrix * result;
	uint32_t dim;

	rand = new_rand();
	rand_seed(rand, 42);
	benchmark = new_benchmark();

	// Loop through the matrix sizes
	for (pos = 0; pos < dim_num; ++pos) {
		dim = dims[pos];

		printf("\nBenchmarking scaling with matrices of dimension %u\n", dim);

		// All square matrices
		uint64_t const dim1 = dim;
		uint64_t const dim2 = dim;
		uint64_t const dim3 = dim;

		uint64_t num_pairs = base_num_pairs / (dim * dim * dim);

		// Use fewer pairs for small matrices
		if (dim <= 2) {
			num_pairs = num_pairs / 16;
		}
		else if (dim <= 8) {
			num_pairs = num_pairs / 8;
		}
		else if (dim <= 2) {
			num_pairs = num_pairs / 4;
		}
		printf("Using %" PRIu64 " pairs of matrices\n", num_pairs);

		// Create random matrices for our calculations
		Matrix **as = calloc(num_pairs, sizeof(Matrix*));
		for (index = 0; index < num_pairs; ++index) {
			as[index] = new_matrix(dim1, dim2);
			matrix_fill(as[index], rand);
		}
		Matrix **bs = calloc(num_pairs, sizeof(Matrix*));
		for (index = 0; index < num_pairs; ++index) {
			bs[index] = new_matrix(dim2, dim3);
			matrix_fill(bs[index], rand);
		}
		printf("Matrices generated\n");

		// Create a temporary array to store the result in
		result = new_matrix(dim1, dim3);

		// Start benchmark
		if (pool) {
			benchmarks_start(benchmark, num_pairs);
			for (index = 0; index < num_pairs; ++index) {
				multiply_parallel(pool, result, as[index], bs[index]);
			}
			benchmarks_end(benchmark);
		}
		else {
			benchmarks_start(benchmark, num_pairs);
			for (index = 0; index < num_pairs; ++index) {
				multiply(result, as[index], bs[index]);
			}
			benchmarks_end(benchmark);
		}
		// End benchmark

		double per_matrix_time = benchmark->elapsed / (double)benchmark->operations;
		printf("Raw timing: %g\n", benchmark->elapsed);
		printf("Per matrix time: %g\n", per_matrix_time);
		times[pos] = per_matrix_time;

		// Clean up
		result = delete_matrix(result);
		for (index = 0; index < num_pairs; ++index) {
			as[index] = delete_matrix(as[index]);
			bs[index] = delete_matrix(bs[index]);
		}
		free(as);
		free(bs);
	}
	benchmark = delete_benchmark(benchmark);

	Store *method = new_store(ALLOC_CHUNK);
	if (pool) {
		store_printf_append(method, "C naive, %u threads", threadpool_threads(pool));
	}
	else {
		store_printf_append(method, "C naive, single threaded");
	}
	export_data("../results.csv", method->data, times, dim_num);
	method = delete_store(method);
}

