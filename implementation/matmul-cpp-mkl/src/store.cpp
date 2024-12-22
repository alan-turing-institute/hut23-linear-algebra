/* vim: set noet ts=2 sts=2 sw=2: */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "store.hpp"

Store * new_store(size_t chunk_size) {
	Store *store = malloc(sizeof(Store));
	
	if (store) {
		// Ensure the buffer is null terminated even for size 0
		store->data = calloc(sizeof(char), 1);
		store->size = 1;
		store->length = 0;
		store->chunk_size = chunk_size;
	}
	return store;
}

Store * delete_store(Store *store) {
	if (store) {
		if (store->data) {
			free(store->data);
		}
		free(store);
	}	
	return NULL;
}

bool store_append(Store * const store, char const * const data, size_t length) {
	bool success = false;
	size_t size;

	size = store->length + length;
	success = store_setsize(store, size);
	if (success) {
		memcpy(store->data + store->length, data, length);
		store->length = size;
		store->data[size] = 0;
	}
	return success;
}

bool store_setsize(Store * const store, size_t size) {
	bool success = false;

	if (store) {
		// Ensure there's always space for a null terminator
		size = size + 1;
		// Quantize the size
		size = ((size_t)(size / store->chunk_size) + 1) * store->chunk_size;
		if (size != store->size) {
			store->data = realloc(store->data, size);
			if (store->data) {
				store->size = size - 1;
				if (store->length > store->size) {
					store->length = store->size;
					store->data[store->size] = 0;
					printf("Set size to: %lu\n", store->size);
				}
				success = true;
			}
		}
		else {
			success = true;
		}
	}
	return success;
}

size_t store_printf (Store * const store, char const * const format, ...) {
	int result;
	size_t length;

	result = 0;
	if (store) {
		store->length = 0;
		store->data[0] = 0;
		va_list args;

		va_start (args, format);
		length = vsnprintf(NULL, 0, format, args);
		va_end (args);

		store_setsize(store, length);

		// This will be automatically null terminated
		va_start (args, format);
		result = vsnprintf(store->data, length + 1, format, args);
		store->length += result;
		va_end (args);
	}
	
	return result;
}

size_t store_printf_append (Store * const store, char const * const format, ...) {
	int result;
	size_t length;

	result = 0;
	if (store) {
		va_list args;

		va_start (args, format);
		length = vsnprintf(NULL, 0, format, args);
		va_end (args);

		store_setsize(store, store->length + length);

		// This will be automatically null terminated
		va_start (args, format);
		result = vsnprintf(store->data + store->length, length + 1, format, args);
		store->length += result;
		va_end (args);
	}
	
	return result;
}


