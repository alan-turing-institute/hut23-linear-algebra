/* vim: noet:ts=2:sts=2:sw=2 */ 

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "parse_header.h"

#define STRING_BLOCK (8)

typedef enum _HEADER_STATE {
	HEADER_STATE_INVALID = -1,
	
	HEADER_STATE_INIT,
	HEADER_STATE_PRE_KEY,
	HEADER_STATE_KEY,
	HEADER_STATE_POST_KEY,
	HEADER_STATE_PRE_VALUE,
	HEADER_STATE_VALUE_TEXT,
	HEADER_STATE_VALUE_BOOL,
	HEADER_STATE_VALUE_LIST_PRE_INT,
	HEADER_STATE_VALUE_LIST_INT,
	HEADER_STATE_POST_VALUE,
	HEADER_STATE_DONE,
	
	HEADER_STATE_NUM
} HEADER_STATE;

void string_reset(char **string, size_t *length, size_t *buffer) {
	if (*buffer != STRING_BLOCK) {
		*buffer = STRING_BLOCK;
		*string = realloc(*string, STRING_BLOCK);
	}
	*length = 0;
	memset(*string, 0, STRING_BLOCK);
}

void string_append(char **string, size_t *length, size_t *buffer, char character) {
	if (*length >= ((*buffer) - 1)) {
		*string = realloc(*string, *buffer + STRING_BLOCK);
		memset((*string) + (*buffer), 0, STRING_BLOCK);
		*buffer += STRING_BLOCK;
	}
	(*string)[*length] = character;
	*length += 1;		
}

typedef struct _HeaderContext {
	HEADER_STATE state;
	char *key;
	size_t key_length;
	size_t key_buffer;
	char *value;
	size_t value_length;
	size_t value_buffer;
	uint32_t value_integer;
	uint32_t list_index;
	Header *result;
} HeaderContext;

void read_head_list_integer(HeaderContext *context) {
	if (strcmp(context->key, "shape") == 0) {
		switch (context->list_index) {
		case 0:
			context->result->height = context->value_integer;
			break;
		case 1:
			context->result->width = context->value_integer;
			break;
		default:
			printf("Unsupported matrix shape\n");
			break;
		}
	}
}

bool read_header_char(HeaderContext *context, char next) {
	bool success = true;

	//printf("Read before state: %d; char %c\n", context->state, next);
	switch (context->state) {
	case HEADER_STATE_INIT:
		if (next == '{') {
			context->state = HEADER_STATE_PRE_KEY;
		}
		else if (!isspace(next)) {
			success = false;
		}
		break;
	case HEADER_STATE_PRE_KEY:
		if (next == '\'') {
			context->state = HEADER_STATE_KEY;
			string_reset(&context->key, &context->key_length, &context->key_buffer);
		}
		else if (next == '}') {
			context->state = HEADER_STATE_DONE;
		}
		else if (!isspace(next)) {
			success = false;
		}
		break;
	case HEADER_STATE_KEY:
		if (next == '\'') {
			//printf("Key: %s\n", context->key);
			context->state = HEADER_STATE_POST_KEY;
		}
		else {
			string_append(&context->key, &context->key_length, &context->key_buffer, next);
		}
		break;
	case HEADER_STATE_POST_KEY:
		if (next == ':') {
			context->state = HEADER_STATE_PRE_VALUE;
		}
		else if (!isspace(next)) {
			success = false;
		}
		break;
	case HEADER_STATE_PRE_VALUE:
		if (next == '\'') {
			context->state = HEADER_STATE_VALUE_TEXT;
			string_reset(&context->value, &context->value_length, &context->value_buffer);
		}
		else if ((next == 'T') || (next == 'F')) {
			string_reset(&context->value, &context->value_length, &context->value_buffer);
			string_append(&context->value, &context->value_length, &context->value_buffer, next);
			context->state = HEADER_STATE_VALUE_BOOL;
		}
		else if (next == '(') {
			context->state = HEADER_STATE_VALUE_LIST_PRE_INT;
			context->value_integer = 0;
			context->list_index = 0;
		}
		else if (!isspace(next)) {
			success = false;
		}
		break;
	case HEADER_STATE_VALUE_TEXT:
		if (next == '\'') {
			//printf("Value: %s\n", context->value);
			context->state = HEADER_STATE_POST_VALUE;
		}
		else {
			string_append(&context->value, &context->value_length, &context->value_buffer, next);
		}
		break;
	case HEADER_STATE_VALUE_BOOL:
		if (isspace(next)) {
			context->state = HEADER_STATE_POST_VALUE;
			//printf("Bool: %s\n", context->value);
		}
		else if (next == ',') {
			context->state = HEADER_STATE_PRE_KEY;
			//printf("Bool: %s\n", context->value);
		}
		else {
			string_append(&context->value, &context->value_length, &context->value_buffer, next);
		}
		break;
	case HEADER_STATE_VALUE_LIST_PRE_INT:
		if ((next >= '0') && (next <= '9')) {
			context->value_integer = (next - '0');
			context->state = HEADER_STATE_VALUE_LIST_INT;
		}
		else if (next == ')') {
			context->state = HEADER_STATE_POST_VALUE;
		}
		else if (!isspace(next)) {
			success = false;
		}
		break;
	case HEADER_STATE_VALUE_LIST_INT:
		if ((next >= '0') && (next <= '9')) {
			context->value_integer = (10 * context->value_integer) + (next - '0');
		}
		else if (next == ',') {
			//printf("List value: %u\n", context->value_integer);
			read_head_list_integer(context);
			context->list_index += 1;
			context->state = HEADER_STATE_VALUE_LIST_PRE_INT;
		}
		else if (next == ')') {
			//printf("List value: %u\n", context->value_integer);
			read_head_list_integer(context);
			context->list_index += 1;
			context->state = HEADER_STATE_POST_VALUE;
		}
		else {
			success = false;
		}
		break;
	case HEADER_STATE_POST_VALUE:
		if (next == ',') {
			context->state = HEADER_STATE_PRE_KEY;
		}
		else if (!isspace(next)) {
			success = false;
		}
		break;
	default:
		break;
	}

	//printf("Read after state: %d; success %d\n", context->state, success);
	
	return success;
}

bool read_header(Header *result, char *header, size_t length) {
	HeaderContext context;
	bool success = true;
	size_t index = 0;

	memset(&context, 0, sizeof(HeaderContext));
	context.state = HEADER_STATE_INIT;
	context.result = result;
	string_reset(&context.key, &context.key_length, &context.key_buffer);
	string_reset(&context.value, &context.value_length, &context.value_buffer);

	while ((index < length) && success) {
		success = read_header_char(&context, header[index]);
		++index;
	}
	
	free(context.key);
	free(context.value);

	return success;
}

