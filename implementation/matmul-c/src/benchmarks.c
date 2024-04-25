/* vim: noet:ts=2:sts=2:sw=2 */ 

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdlib.h>
#include <inttypes.h>

#include "matrix.h"
#include "load.h"
#include "operations.h"
#include "threadpool.h"

#include "benchmarks.h"

#define BENCHMARK_REPEAT_SMALL (32768)
#define BENCHMARK_REPEAT_LARGE (1)

#define HEIGHT (2048)
#define WIDTH (2048)

struct _Benchmark {
	struct timespec start_time;
	struct timespec end_time;
	uint32_t operations;
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
			printf("Time taken to perform %u operations: %.02f seconds\n", benchmark->operations, benchmark->elapsed);
			printf("Equivalent to %.02f operations per second\n", benchmark->ops_per_sec);
		}
	}
}

void benchmarks_multiply_big(ThreadPool *pool) {
	Benchmark *benchmark;
	Matrix *A;
	Matrix *B;
	Matrix *D;

	printf("\n");
	printf("## Large matrix multiplication\n");

	benchmark = new_benchmark();
	benchmark_set_quiet(benchmark, true);

	for (uint32_t width = 128; width <= 2048; width += 128) {
		uint32_t diag = width;
		uint32_t height = width;
		uint32_t const repeat = BENCHMARK_REPEAT_LARGE * (width < 512 ? 1024 : width < 1024 ? 16 : 1);

		A = new_matrix(width, diag);
		B = new_matrix(diag, height);
		D = new_matrix(width, height);
		matrix_fill(A, 8);
		matrix_fill(B, 16);

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
		matrix_fill(A, 8);
		matrix_fill(B, 16);

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

