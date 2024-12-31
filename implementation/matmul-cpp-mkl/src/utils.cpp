/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdlib.h>

#include "matrix.hpp"

#include "utils.hpp"

#define A (16807)
#define C (0)
#define M (2147483647)

struct _Rand {
	uint32_t state;
};

Rand * new_rand() {
	Rand *rand = static_cast<Rand *>(calloc(sizeof(Rand), sizeof(char)));

	return rand;
}

Rand * delete_rand(Rand *rand) {
	if (rand) {
		free(rand);
	}
	return NULL;
}

// Seed the random number generator
void rand_seed(Rand *rand, uint32_t seed) {
	rand->state = seed;
}

// A decimal between 0.0 and 1.0
// See https://www.math.arizona.edu/~tgk/mc/book_chap3.pdf
inline double rand_next(Rand *rand) {
	rand->state = ((A * rand->state) + C) % M;
	return (double)rand->state / (double)M;
}

// A value between 0.0 and 100.0
double rand_value(Rand *rand) {
	double result;
	result = rand_next(rand);
	result = ((int)(result * 1000.0)) / 10.0;
	return result;
}

