#!/bin/python3
# vim: noet:ts=2:sts=2:sw=2

# SPDX-License-Identifier: MIT
# Copyright © 2024 David Llewellyn-Jones

import numpy as np
import random
import time

BENCHMARK_REPEAT = 32768

def rand_matrix(height, width):
	data = []
	for row in range(height):
		row_data = []
		for col in range(width):
			value = random.randrange(99) / 10
			row_data.append(value)
		data.append(row_data)
	return np.matrix(data)

print(f'Generating test data...')
a_matrices = []
b_matrices = []
c_matrices = []
random.seed(56)
count = 0
kwargs = {}
for height in range(2, 10):
	for width in range(2, 10):
		for edge in range(2, 10):
			a = rand_matrix(height, edge)
			b = rand_matrix(edge, width)
			c = a * b
			kwargs['a_' + str(count)] = a
			kwargs['b_' + str(count)] = b
			kwargs['c_' + str(count)] = c
			count += 1
			a_matrices.append(a)
			b_matrices.append(b)
			c_matrices.append(c)

print(f'Exporting test data...')
np.savez('../testdata/matrices.npz', **kwargs)
total = count

a = rand_matrix(4, 3)
b = rand_matrix(3, 4)
c = a * b
np.save('../testdata/matrix-a.npy', a)
np.save('../testdata/matrix-b.npy', b)
np.save('../testdata/matrix-c.npy', c)

print("Benchmarking...")
start_time = time.process_time()
for count in range(BENCHMARK_REPEAT):
	for index in range(total):
		a = a_matrices[index]
		b = b_matrices[index]
		c = a * b
end_time = time.process_time()
elapsed = end_time - start_time
operations = total * BENCHMARK_REPEAT
print(f'Time taken to perform {operations} multiply operations: {elapsed:0.2f} seconds')
ops_per_sec = operations / elapsed
print(f'Equivalent to {ops_per_sec:0.2f} operations per second')

