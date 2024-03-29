/* vim: noet:ts=2:sts=2:sw=2 */ 

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <archive.h>
#include <archive_entry.h>

#include "parse_header.h"
#include "load.h"

#define MAGIC "\x93NUMPY"

Matrix *matrix_npz_load_entry(struct archive *a);

Matrix * matrix_load(char *filename) {
	FILE *fh = fopen(filename, "rb");
	uint16_t header_size;
	bool result = true;
	Matrix *A = NULL;
	size_t len = 0;
	char *header_text = NULL;
	Header header;
	uint32_t height = 0;
	uint32_t width = 0;
	
	if (result) {
		char magic[6];
		len = fread(magic, 6, 1, fh);
		result = (len == 1) && (strncmp(magic, MAGIC, 6) == 0);
	}

	if (result) {
		uint8_t major;
		uint8_t minor;
		len = fread(&major, sizeof(major), 1, fh);
		result = (len == 1);
		len = fread(&minor, sizeof(minor), 1, fh);
		result = result && (len == 1) && (major == 1) && (minor == 0);
	}

	if (result) {
		len = fread(&header_size, sizeof(header_size), 1, fh);
		result = (len == 1);
	}

	if (result) {
		header_text = calloc(header_size, sizeof(char));
		len = fread(header_text, sizeof(char), header_size, fh);
		result = (len == header_size);
	}

	if (result) {
		result = read_header(&header, header_text, header_size);
		if (!result) {
			printf("Unable to read header: %s\n", header_text);
		}
	}

	if (result) {
		height = header.height;
		width = header.width;
		A = new_matrix(height, width);
		result = (A != NULL);
	}
	
	if (result) {
		len = fread(A->elements, sizeof(double), height * width, fh);
		result = (len == height * width);
	}
	
	if (header_text) {
		free(header_text);
	}

	fclose(fh);
	return A;
}

Matrix *matrix_npz_load_entry(struct archive *a) {
	char magic[6];
	uint16_t header_size = 0;
	uint8_t major = 0;
	uint8_t minor = 0;
	char *header_text = NULL;
	Header header;
	bool result = true;
	Matrix *A = NULL;
	size_t len = 0;

	if (result) {
		len = archive_read_data(a, magic, 6);
		result = (len == 6);
	}

	if (result) {
		result = (strncmp(magic, MAGIC, 6) == 0);
	}
	
	if (result) {
		archive_read_data(a, &major, sizeof(major));
		archive_read_data(a, &minor, sizeof(minor));
		result = ((major == 1) && (minor == 0));
	}
	
	if (result) {
		len = archive_read_data(a, &header_size, sizeof(header_size));
		result = (len == sizeof(header_size));
	}
	
	if (result) {
		header_text = calloc(header_size, sizeof(char));
		result = (header_text != NULL);
	}

	if (result) {
		len = archive_read_data(a, header_text, sizeof(char) * header_size);
		result = (len == header_size);
	}

	if (result) {
		result = read_header(&header, header_text, header_size);
		if (!result) {
			printf("Unable to read header: %s\n", header_text);
		}
		result = result && (header.height > 0) && (header.width > 0);
	}
	
	if (result) {
		A = new_matrix(header.height, header.width);
		result = (A != NULL);
	}

	if (result) {
		const uint32_t size = sizeof(double) * header.height * header.width;
		len = archive_read_data(a, A->elements, size);
		result = (len == size);
	}
	
	if (header_text) {
		free(header_text);
	}
	return A;
}

void matrix_npz_load(char *filename, Matrices *matrices) {
	struct archive *a;
	struct archive_entry *entry;
	int r;
	uint32_t count = 0;
	bool result = true;

	if (result) {
		a = archive_read_new();
		archive_read_support_filter_all(a);
		archive_read_support_format_all(a);
		r = archive_read_open_filename(a, filename, 10240);
		result = (r == ARCHIVE_OK);
	}
	
	if (result) {
		while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
			count += 1;
			archive_read_data_skip(a);
		}
		r = archive_read_free(a);
		result = (count > 0);
	}
	
	if (result) {
		matrices->matrices = realloc(matrices->matrices, sizeof(NamedMatrix) * count);
		result = (matrices->matrices != NULL);
		if (result) {
			memset(matrices->matrices, 0, sizeof(NamedMatrix) * count);
		}
	}

	if (result) {
		a = archive_read_new();
		archive_read_support_filter_all(a);
		archive_read_support_format_all(a);
		r = archive_read_open_filename(a, filename, 10240);
		result = (r == ARCHIVE_OK);
	}
	
	if (result) {
		uint32_t index = 0;
		while ((archive_read_next_header(a, &entry) == ARCHIVE_OK) && (index < count)) {
			matrices->matrices[index].matrix = matrix_npz_load_entry(a);
			matrices->matrices[index].name = strdup(archive_entry_pathname(entry));
			archive_read_data_skip(a);
			index += 1;
		}
		matrices->count = index;
		r = archive_read_free(a);
	}
}


Matrices *new_matrices(uint32_t count) {
	Matrices *matrices = calloc(sizeof(Matrices), 1);
	matrices->count = count;
	if (count > 0) {
		matrices->matrices = calloc(sizeof(NamedMatrix), count);
	}
	else {
		matrices->matrices = NULL;
	}
	return matrices;
}

Matrices *delete_matrices(Matrices *matrices) {
	if (matrices) {
		if (matrices->matrices) {
			for (uint32_t index = 0; index < matrices->count; ++index) {
				if (matrices->matrices[index].matrix) {
					matrices->matrices[index].matrix = delete_matrix(matrices->matrices[index].matrix);
				}
				if (matrices->matrices[index].name) {
					free(matrices->matrices[index].name);
				}
			}
			free(matrices->matrices);
		}
		free(matrices);
	}
	return NULL;
}


