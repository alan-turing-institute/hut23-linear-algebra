/* vim: noet:ts=2:sts=2:sw=2 */ 

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#include "threadpool.h"

#define MAX_THREADS (8)

typedef struct _ThreadContext {
	pthread_mutex_t *working_mutex;
	pthread_cond_t *working_cond;
	pthread_mutex_t *begin_mutex;
	pthread_cond_t *begin_cond;
	uint32_t *working;
	bool live;

	Matrix *result;
	Matrix *A;
	Matrix *B;
	uint32_t start;
	uint32_t end;
} ThreadContext;

struct _ThreadPool {
	pthread_t thread_id[MAX_THREADS];
	ThreadContext *context[MAX_THREADS];

	pthread_mutex_t working_mutex;
	pthread_cond_t working_cond;
	pthread_mutex_t begin_mutex;
	pthread_cond_t begin_cond;
	uint32_t working;
};

void *thread_runner(void *vargp);

inline void multiply_work(Matrix *result, Matrix *A, Matrix *B, uint32_t start, uint32_t end) {
	uint32_t apos = 0;
	uint32_t bpos = 0;
	// Step through all the entries in the result matrix
	for (uint32_t cpos = start; cpos < end; ++cpos) {
		// For A start at the beginning of the row
		apos = (cpos / result->width) * A->width;
		// For B start at the top of a column
		bpos = cpos % result->width;
		// Accumulator for the products
		double element = 0.0f;
		// For each entry in the result, sum the product of row/column pairs
		for (uint32_t pos = 0; pos < A->width; ++pos) {
			// Accumulate the products
			element += A->elements[apos] * B->elements[bpos];
			// Row stride of 1
			apos += 1;
			// Column stride of "width of B"
			bpos += B->width;
		}
		// Write out the resulting element
		result->elements[cpos] = element;
	}
}

ThreadPool * new_threadpool() {
	ThreadPool *pool = calloc(sizeof(ThreadPool), sizeof(char));

	if (pool) {
		// Initialise the pool context
		pthread_mutex_init(&pool->working_mutex, NULL);
		pthread_cond_init(&pool->working_cond, NULL);
		pthread_mutex_init(&pool->begin_mutex, NULL);
		pthread_cond_init(&pool->begin_cond, NULL);
		pool->working = MAX_THREADS;

		// Initialise the threads
		for (uint32_t thread = 0; thread < MAX_THREADS; ++thread) {
			pool->context[thread] = calloc(sizeof(ThreadContext), sizeof(char));
			pool->context[thread]->working_mutex = &pool->working_mutex;
			pool->context[thread]->working_cond = &pool->working_cond;
			pool->context[thread]->begin_mutex = &pool->begin_mutex;
			pool->context[thread]->begin_cond = &pool->begin_cond;
			pool->context[thread]->working = &pool->working;
			pool->context[thread]->live = true;

			pthread_create(&pool->thread_id[thread], NULL, thread_runner, pool->context[thread]);
		}

		// Wait for the threads to initialise
		pthread_mutex_lock(&pool->working_mutex);
		while (pool->working > 0) {
			pthread_cond_wait(&pool->working_cond, &pool->working_mutex);
		}
		pthread_mutex_unlock(&pool->working_mutex);
	}
	return pool;
}

ThreadPool * delete_threadpool(ThreadPool *pool) {
	if (pool) {
		// Remove all work
		pthread_mutex_lock(&pool->begin_mutex);
		for (uint32_t thread = 0; thread < MAX_THREADS; ++thread) {
			pool->context[thread]->live = false;
		}
		pthread_cond_broadcast(&pool->begin_cond);
		pthread_mutex_unlock(&pool->begin_mutex);

		// Wait for the threads to complete
		for (uint32_t thread = 0; thread < MAX_THREADS; ++thread) {
			pthread_join(pool->thread_id[thread], NULL);
			free(pool->context[thread]);
		}

		pthread_mutex_destroy(&pool->working_mutex);
		pthread_cond_destroy(&pool->working_cond);
		pthread_mutex_destroy(&pool->begin_mutex);
		pthread_cond_destroy(&pool->begin_cond);

		free(pool);
	}
	return NULL;
}

void *thread_runner(void *vargp) {
	ThreadContext *context = (ThreadContext*)vargp;

	while (context->live) {
		// Signal that the work is done
		pthread_mutex_lock(context->working_mutex);
		pthread_mutex_lock(context->begin_mutex);
		--(*context->working);
		pthread_cond_signal(context->working_cond);
		pthread_mutex_unlock(context->working_mutex);

		// Wait for some work to arrive
		pthread_cond_wait(context->begin_cond, context->begin_mutex);
		pthread_mutex_unlock(context->begin_mutex);

		if (context->live) {
			// Do the work
			multiply_work(context->result, context->A, context->B, context->start, context->end);
			context->start = 0;
			context->end = 0;
		}
	}
	// No more work to do

	return NULL;
}

bool multiply_parallel(ThreadPool *pool, Matrix *result, Matrix *A, Matrix *B) {
	uint32_t size = result->height * result->width;

	uint32_t chunk = (size + (MAX_THREADS - 1)) / MAX_THREADS;
	uint32_t allocated = 0;
	uint32_t thread = 0;

	// Allocate the work
	while (allocated < size) {
		pool->context[thread]->result = result;
		pool->context[thread]->A = A;
		pool->context[thread]->B = B;
		pool->context[thread]->start = allocated;
		allocated += chunk;
		if (allocated > size) {
			allocated = size;
		}
		pool->context[thread]->end = allocated;
		thread += 1;
	}

	// Trigger the runners to work
	pthread_mutex_lock(&pool->begin_mutex);
	pool->working = MAX_THREADS;
	pthread_cond_broadcast(&pool->begin_cond);
	pthread_mutex_unlock(&pool->begin_mutex);

	// Wait for the work to complete
	pthread_mutex_lock(&pool->working_mutex);
	while (pool->working > 0) {
		pthread_cond_wait(&pool->working_cond, &pool->working_mutex);
	}
	pthread_mutex_unlock(&pool->working_mutex);

	return true;
}

