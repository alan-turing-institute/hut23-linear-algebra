A::UInt32 = 16807
C::UInt32 = 0
M::Float64 = 2147483647

mutable struct Rand
    state::UInt32
end

# Seed the random number generator
function rand_init(seed)
    return Rand(convert(UInt32, seed))
end

# A decimal between 0.0 and 1.0
# See https://www.math.arizona.edu/~tgk/mc/book_chap3.pdf
function rand_next(rand)
	rand.state = ((A * rand.state) + C) % M
	return convert(Float64, rand.state) / M
end

# A value between 0.0 and 100.0
function rand_value(rand)
	result = rand_next(rand)
	result = trunc(Int32, (result * 1000.0)) / 10.0
	return result
end

# A dim2 × dim1 matrix filled with random values
# Note the dimensions are reversed to match rand()
function rand_matrix(rand, dim1, dim2)
    return reduce(vcat, transpose.([[rand_value(rand) for _ in 1:dim1] for _ in 1:dim2]))
end


