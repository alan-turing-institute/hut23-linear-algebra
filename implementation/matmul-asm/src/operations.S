/* vim: noet:ts=2:sts=2:sw=2 */

/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 David Llewellyn-Jones */

/* 
 * ARMv8 A64 quick reference:
 * https://courses.cs.washington.edu/courses/cse469/18wi/Materials/arm64.pdf
 *
 * ARMv8 A64 ISA reference
 * https://developer.arm.com/documentation/ddi0602/2024-03/
 *
 * ARM64 calling convention
 * https://dede.dev/posts/ARM64-Calling-Convention-Cheat-Sheet/#function-return
 *
 * GNU assembler manual
 * https://sourceware.org/binutils/docs/as/
 *
 */
#if defined(__aarch64__) || defined(_M_ARM64)
	.arch armv8-a

	.text
	.global multiply
	.balign 4
/**
 * @brief Multiplies two matrices together
 *
 * @param result matrix to return the result in (should be pre-allocated)
 * @param A left-hand side of the matrix multiplication
 * @param B right-hand side of the matrix multiplication
 *
 * @return true if the matrices could be multiplied, false o/w
 *
 * bool multiply(Matrix *result, Matrix *A, Matrix *B)
 */
multiply:

	/* Registers inputs */
	#define result x0
	#define A x1
	#define B x2

	/* Registers outputs */
	#define return x0

	/* Registers 32-bit */
	#define awidth w3
	#define bwidth w4
	#define rwidth w5
	#define aheight w6
	#define bheight w7
	#define rheight w8

	#define astart w5
	#define bstart w6
	#define apos w7
	#define bpos w8
	#define cpos w9
	#define count w10

	/* Registers 64-bit */
	#define rdata x0
	#define adata x1
	#define bdata x2

	/* Registers double */
	#define element d0
	#define e0 d1
	#define e1 d2

	// Ensure the matrices exist
	// bool success = A && B && result;
	CMP result, #0x0
	CCMP A, #0x0, #0x4, NE
	CCMP B, #0x0, #0x4, NE
	BEQ failure

	// Load matrix dimensions from the data structures
	LDP aheight, awidth, [A, #0x0]
	LDP bheight, bwidth, [B, #0x0]
	LDP rheight, rwidth, [result, #0x0]
	// Load pointers to the matrix elements from the data structures
	LDR adata, [A, #0x8]
	LDR bdata, [B, #0x8]
	LDR rdata, [result, #0x8]

	// Ensure the data exist
	// bool success = A->data && B->data && result->data;
	CMP adata, #0x0
	CCMP bdata, #0x0, #0x4, NE
	CCMP rdata, #0x0, #0x4, NE
	BEQ failure

	// Ensure the matrices have suitable sizes
	// bool success = (A->width == B->height)
	//   && (result->width == B->width)
	//   && (result->height == A->height);
	CMP awidth, #0x0
	CCMP bwidth, #0x0, #0x4, NE
	CCMP aheight, #0x0, #0x4, NE
	BEQ failure
	CMP awidth, bheight
	CCMP rwidth, bwidth, #0x0, EQ
	CCMP rheight, aheight, #0x0, EQ
	BNE failure

	// Start outer loop
	// Step through all the entries in the result matrix
	// Start at the end and work back to avoid a CMP inside the loop
	// for (uint32_t cpos = B->width * A->height- 1; cpos >= 0; --cpos)
	// cpos = (result->height * result->width) - 1;
	MUL cpos, bwidth, aheight
	SUB cpos, cpos, #0x1
	// Calculate A and B start positions incrementally to avoid
	// the need for multiplication or division inside the loop
	MUL astart, awidth, aheight
	MOV bstart, bwidth

start_outer:

	// For A start at the beginning of the row
	// apos = (cpos / B->width) * A->width;
	SUB apos, astart, awidth
	// For B start at the top of a column
	// bpos = cpos % B->width;
	SUB bpos, bstart, #0x1
	// Accumulator for the products
	// double element = 0;
	MOVI v0.4h, #0x0
	// Start inner loop
	// Start at the end and work back to avoid a CMP inside the loop
	// For each entry in the result, sum the product of row/column pairs
	// for (uint32_t count = A->width; count > 0; --count)
	MOV count, awidth

start_inner:

	// Accumulate the products
	// element += A->elements[apos] * B->elements[bpos];
	LDR e0, [adata, apos, UXTW #0x3]
	LDR e1, [bdata, bpos, UXTW #0x3]
	FMADD element, e0, e1, element
	// Row stride of 1
	// apos += 1;
	ADD apos, apos, #0x1
	// Column stride of width of B
	// bpos += B->width;
	ADD bpos, bpos, bwidth

	// End inner loop
	// for (uint32_t pos = A->width; pos > 0; --pos)
	SUBS count, count, #0x1
	BGT start_inner
	// Write out the resulting element
	// result->elements[cpos] = element;
	STR element, [rdata, cpos, UXTW #0x3]

	// For B move one column to the left
	// bpos = bpos - 1
	SUBS bstart, bstart, #0x1
	// If we reached the start of the columns move back to the last column
	CSEL bstart, bwidth, bstart, LE

	// For A move to the next row up; count is available as a temporary register
	// astart = astart - awidth
	SUB count, astart, awidth
	// Only do this if we completed an entire row of columns
	CSEL astart, count, astart, LE

	// End outer loop
	// for (uint32_t cpos = B->width * A->height- 1; cpos >= 0; --cpos)
	SUBS cpos, cpos, #0x1
	BGE start_outer

	// Function completed with success
	MOV return, #0x1
	RET

failure:

	// Function completed with failure
	MOV return, #0x0
	RET

#else
	#error Only aarch64 asm supported
#endif

