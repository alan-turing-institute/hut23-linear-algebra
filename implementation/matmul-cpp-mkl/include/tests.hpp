/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdbool.h>
#include <stdio.h>

#include "matrix.hpp"
#include "load.hpp"

#ifndef __MATRIX_TESTS_H
#define __MATRIX_TESTS_H (1)

uint32_t tests_load_matrices(sycl::queue &Q, Matrices *a, Matrices *b, Matrices *c);
bool tests_allocate_results(sycl::queue &Q, Matrices *c, Matrices *d);

void tests_compare(sycl::queue &Q, Matrices *a, Matrices *b, Matrices *c, Matrices *d);

#endif /* __MATRIX_TESTS_H */

