/* vim: noet:ts=2:sts=2:sw=2 */ 

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdbool.h>
#include <stdio.h>

#include "load.h"

#ifndef __MATRIX_TESTS_H
#define __MATRIX_TESTS_H (1)

uint32_t tests_load_matrices(Matrices *a, Matrices *b, Matrices *c);
bool tests_allocate_results(Matrices *c, Matrices *d);

#endif /* __MATRIX_TESTS_H */

