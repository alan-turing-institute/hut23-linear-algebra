/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdbool.h>
#include <stdio.h>

#ifndef __MATRIX_BENCHMARKS_H
#define __MATRIX_BENCHMARKS_H (1)

typedef struct _Benchmark Benchmark;

Benchmark * new_benchmark(sycl::queue &Q);
Benchmark * delete_benchmark(Benchmark *benchmark);

void benchmarks_start(Benchmark *benchmark, uint32_t operations);
void benchmarks_end(Benchmark *benchmark);
void benchmark_set_quiet(Benchmark *benchmark, bool quiet);
void benchmarks_multiply_big(sycl::queue &Q);
void benchmarks_multiply_small(sycl::queue &Q, Matrices *a, Matrices *b, Matrices *d);
void benchmark_multiply_square(sycl::queue &Q);

#endif /* __MATRIX_BENCHMARKS_H */

