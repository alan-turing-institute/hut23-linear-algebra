/* vim: noet:ts=2:sts=2:sw=2 */ 

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#ifndef __MATRIX_UTILS_H
#define __MATRIX_UTILS_H (1)

#include <stdint.h>

typedef struct _Rand Rand;

Rand * new_rand();
Rand * delete_rand(Rand *rand);
void rand_seed(Rand *rand, uint32_t seed);
double rand_next(Rand *rand);
double rand_digit(Rand *rand);

#endif /* __MATRIX_UTILS_H */
