/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

#include "matrix.hpp"

#ifndef __MATRIX_THREADPOOL_H
#define __MATRIX_THREADPOOL_H (1)

typedef struct _ThreadPool ThreadPool;

ThreadPool * new_threadpool(uint32_t threads);
ThreadPool * delete_threadpool(ThreadPool *pool);
bool multiply_parallel(ThreadPool *pool, Matrix *result, Matrix *A, Matrix *B);
uint32_t threadpool_threads(ThreadPool *pool);

#endif /* __MATRIX_THREADPOOL_H */
