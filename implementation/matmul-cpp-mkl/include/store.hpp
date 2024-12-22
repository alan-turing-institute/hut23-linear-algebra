/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdint.h>
#include <stdbool.h>

#ifndef __MATRIX_STORE_H
#define __MATRIX_STORE_H (1)

typedef struct _Store {
	// Pointer to the data
	char * data;
	// The allocated size
	size_t size;
	// The size of the data store in the allocation
	size_t length;
	// The chunk size to allocate blocks in
	size_t chunk_size;
} Store;

Store * new_store(size_t chunk_size);
Store * delete_store(Store *store);
bool store_append(Store * const store, char const * const data, size_t length);
bool store_setsize(Store * const store, size_t size);
size_t store_printf (Store * const store, char const * const format, ...);
size_t store_printf_append (Store * const store, char const * const format, ...);

#endif /* __MATRIX_STORE_H */
