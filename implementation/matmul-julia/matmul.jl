using LinearAlgebra
using NPZ
using StaticArrays
using Octavian
using Plots
using CSV
using DataFrames

include("utils.jl")

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# The various matrix multiplication functions that we'll benchmark and compare

function matmul_blas(a, b)
    return a * b
end

function matmul_naive(a, b)
    dim1, dim2 = size(a)
    dim3 = size(b, 2)
    c = zeros(eltype(a), (dim1, dim3))
    for i in 1:dim1
        for j in 1:dim3
            for k in 1:dim2
                c[i, j]  += a[i, k] * b[k, j]
            end
        end
    end
    return c
end

function matmul_naive_transpose(a, b)
    dim1, dim2 = size(a)
    dim3 = size(b, 2)
    c = zeros(eltype(a), (dim1, dim3))
    a_transpose = zeros(eltype(a), size(a))
    LinearAlgebra.transpose!(a_transpose, a)
    for i in 1:dim1
        for j in 1:dim3
            for k in 1:dim2
                c[i, j]  += a_transpose[k, i] * b[k, j]
            end
        end
    end
    return c
end

function matmul_unsafe(a, b)
    # This is like matmul_naive, but with @fastmath and @inbounds, which turn off some
    # safety checks. I also allocate a temporary variable in which I accumulate each element
    # of the result before assigning it to the result matrix.
    @fastmath @inbounds begin
        dim1, dim2 = size(a)
        dim3 = size(b, 2)
        c = zeros(eltype(a), (dim1, dim3))
        for i in 1:dim1
            for j in 1:dim3
                c_el = zero(eltype(c))
                for k in 1:dim2
                    c_el += a[i, k] * b[k, j]
                end
                c[i, j] = c_el
            end
        end
        return c
    end
end

function matmul_unsafe_preallocate!(c, a, b)
    # Like matmul_unsafe, but with a preallocated result matrix that gets overwritten.
    @fastmath @inbounds begin
        dim1, dim2 = size(a)
        dim3 = size(b, 2)
        fill!(c, zero(eltype(c)))
        for i in 1:dim1
            for j in 1:dim3
                c_el = zero(eltype(c))
                for k in 1:dim2
                    c_el += a[i, k] * b[k, j]
                end
                c[i, j] = c_el
            end
        end
    end
end

function matmul_octavian(a, b)
    # Call the matmul function from Octavian.jl.
    return matmul(a, b)
end

function matmul_octavian_preallocate!(c, a, b)
    # Call the in-place matmul function from Octavian.jl that overwrites the result matrix.
    return matmul!(c, a, b)
end

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# Functions that loop over the matmul functions above.

function loop_matmul_blas(as, bs, num_repeats)
    num_pairs = length(as)
    for _ in 1:num_repeats
        for i in 1:num_pairs
            matmul_blas(as[i], bs[i])
        end
    end
end

function loop_matmul_naive(as, bs, num_repeats)
    num_pairs = length(as)
    for _ in 1:num_repeats
        for i in 1:num_pairs
            matmul_naive(as[i], bs[i])
        end
    end
end

function loop_matmul_naive_transpose(as, bs, num_repeats)
    num_pairs = length(as)
    for _ in 1:num_repeats
        for i in 1:num_pairs
            matmul_naive_transpose(as[i], bs[i])
        end
    end
end

function loop_matmul_unsafe(as, bs, num_repeats)
    num_pairs = length(as)
    for _ in 1:num_repeats
        for i in 1:num_pairs
            matmul_unsafe(as[i], bs[i])
        end
    end
end

function loop_matmul_unsafe_preallocate(as, bs, num_repeats)
    num_pairs = length(as)
    max_dim1 = maximum(size(a, 1) for a in as)
    max_dim2 = maximum(size(b, 2) for b in bs)
    c = zeros(Float64, (max_dim1, max_dim2))
    for _ in 1:num_repeats
        for i in 1:num_pairs
            matmul_unsafe_preallocate!(c, as[i], bs[i])
        end
    end
end

function loop_matmul_octavian(as, bs, num_repeats)
    num_pairs = length(as)
    for _ in 1:num_repeats
        for i in 1:num_pairs
            matmul_octavian(as[i], bs[i])
        end
    end
end

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# The main function that reads in the test matrices and runs the benchmarks.

function main_benchmark()
    BENCHMARK_REPEAT = 32768
    matrices = npzread("../testdata/matrices.npz")
    num_pairs = div(length(matrices), 3)
    # The dictionary uses Python's zero-based numbering.
    as = [matrices["a_$i"] for i in 0:num_pairs-1]
    bs = [matrices["b_$i"] for i in 0:num_pairs-1]
    cs = [matrices["c_$i"] for i in 0:num_pairs-1]

    # Pick one example set of a, b, and c that we use to check that each of the matmul
    # functions is working correctly.
    example_pick = 23
    a_example = as[example_pick]
    b_example = bs[example_pick]
    c_example = cs[example_pick]

    # The assert serves two purposes: It triggers compilation for the matmul function, which
    # we want to happen outside the timing block, and checks that we are getting the
    # right result.
    @assert c_example ≈ matmul_blas(a_example, b_example)
    println("Running matmul_blas")
    @time loop_matmul_blas(as, bs, BENCHMARK_REPEAT)

    @assert c_example ≈ matmul_naive(a_example, b_example)
    println("Running matmul_naive")
    @time loop_matmul_naive(as, bs, BENCHMARK_REPEAT)

    @assert c_example ≈ matmul_unsafe(a_example, b_example)
    println("Running matmul_unsafe")
    @time loop_matmul_unsafe(as, bs, BENCHMARK_REPEAT)

    c = zeros(eltype(c_example), size(c_example))
    matmul_unsafe_preallocate!(c, a_example, b_example)
    @assert c_example ≈ c
    println("Running matmul_unsafe_preallocate")
    @time loop_matmul_unsafe_preallocate(as, bs, BENCHMARK_REPEAT)

    @assert c_example ≈ matmul_octavian(a_example, b_example)
    println("Running matmul_octavian")
    @time loop_matmul_octavian(as, bs, BENCHMARK_REPEAT)
end

# main_benchmark()

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# Static array stuff
#
# Julia has a library called StaticArrays, which defines array types that have the size of
# the array in the type definition. This allows the compiler to know the size of the array
# at compile time. I wanted to try it out, but for that I needed to define a different set
# of test matrices that are all of the same size, hence the separate benchmarking function.
#
# Seems StaticArrays faster than BLAS for very small matrices. My own naive implementation
# is very slow, don't know why. Compilation times get very long for even moderate sized
# matrices.

function matmul_naive(a::SMatrix{N1, N2, T}, b::SMatrix{N2, N3, T}) where {N1, N2, N3, T}
    c = zeros(MMatrix{N1, N3, T})
    for i in 1:N1
        for j in 1:N3
            for k in 1:N2
                c[i, j] += a[i, k] * b[k, j]
            end
        end
    end
    return c
end

function static_benchmark()

    for dim in (2, 4, 8, 16, 32, 64)
        println("\nBenchmarking with matrices of dimension $dim")
        BENCHMARK_REPEAT = div(2^19, dim^2)
        dim1 = dim
        dim2 = dim
        dim3 = dim
        num_pairs = 512

        as = [rand(Float64, dim1, dim2) for _ in 1:num_pairs]
        bs = [rand(Float64, dim2, dim3) for _ in 1:num_pairs]
        cs = [a * b for (a, b) in zip(as, bs)]

        static_as = [SMatrix{dim1, dim2}(a) for a in as]
        static_bs = [SMatrix{dim2, dim3}(b) for b in bs]
        static_cs = [a * b for (a, b) in zip(static_as, static_bs)]

        example_pick = 23

        @assert cs[example_pick] ≈ matmul_blas(as[example_pick], bs[example_pick])
        println("Running matmul_blas (non-static)")
        @time loop_matmul_blas(as, bs, BENCHMARK_REPEAT)

        # This doesn't actually use BLAS, but rather the matmul implementatino in
        # StaticArrays.
        @assert static_cs[example_pick] ≈ matmul_blas(static_as[example_pick], static_bs[example_pick])
        println("Running matmul_blas (static)")
        @time loop_matmul_blas(static_as, static_bs, BENCHMARK_REPEAT)

        @assert static_cs[example_pick] ≈ matmul_naive(static_as[example_pick], static_bs[example_pick])
        println("Running matmul_v2 (static)")
        @time loop_matmul_naive(static_as, static_bs, BENCHMARK_REPEAT)
    end
end

# static_benchmark()

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Scaling benchmark

function scaling_benchmark(method)
    dims = [2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192, 256, 384, 512, 768, 1024]

    base_num_pairs = 2^32
    threads = Threads.nthreads()
    thread_string = threads > 1 ? "$(threads) threads" : "single-threaded"

    method_name = "none"
    times = Array{Float64}(undef, 0)

    rand = rand_init(42)

    for dim in dims
        println("\nBenchmarking scaling with matrices of dimension $dim")
        dim1 = dim
        dim2 = dim
        dim3 = dim
        num_pairs = div(base_num_pairs, dim^3)
        # Use fewer pairs for small matrices.
        if dim <= 2
            num_pairs = div(num_pairs, 16)
        elseif 2 < dim <= 4
            num_pairs = div(num_pairs, 8)
        elseif 4 < dim <= 8
            num_pairs = div(num_pairs, 4)
        end
        println("Using $num_pairs pairs of matrices")

        as = [rand_matrix(rand, dim1, dim2) for _ in 1:num_pairs]
        bs = [rand_matrix(rand, dim2, dim3) for _ in 1:num_pairs]

        if method == :octavian
            loop_matmul_octavian(as[1:1], bs[1:1], 1)
            timing_result = @elapsed loop_matmul_octavian(as, bs, 1)
            method_name = "octavian, $(thread_string)"
        elseif method == :naive
            loop_matmul_naive(as[1:1], bs[1:1], 1)
            timing_result = @elapsed loop_matmul_naive(as, bs, 1)
            method_name = "naive, $(thread_string)"
        elseif method == :naive_transpose
            loop_matmul_naive_transpose(as[1:1], bs[1:1], 1)
            timing_result = @elapsed loop_matmul_naive_transpose(as, bs, 1)
            method_name = "naive transpose, $(thread_string)"
        elseif method == :blas
            method_name = "blas, $(thread_string)"
            loop_matmul_blas(as[1:1], bs[1:1], 1)
            timing_result = @elapsed loop_matmul_blas(as, bs, 1)
        end
        per_matrix_time = timing_result / num_pairs
        println("Raw timing: $timing_result")
        println("Per matrix time: $(per_matrix_time)")
        times = vcat(times, per_matrix_time)
    end
    println("dims = $dims")
    println("times = $times")
    plot(dims, times, xscale=:log10, yscale=:log10, xlabel="Dimension", ylabel="Time (s)", legend=:topleft, lw=2, marker=:circle, ms=5)
    export_data("../results.csv", method_name, times)
end

function export_data(filename, name, data)
    if (isfile(filename))
        df = CSV.read(filename, DataFrame)
        df[!, :method] = convert.(String, df[!, :method])
    else
        df = DataFrame([Float32[] for i in 1:size(data, 1)], :auto)
        insertcols!(df, 1, :method => String[])
    end

    df = filter(row -> row.method != name, df)

    push!(df, vcat(name, data))
    println("Writing data to: $(filename)")
    CSV.write(filename, df)
end

function scaling_benchmarks()
    methods = [:octavian, :naive, :naive_transpose, :blas]
    for method in methods
        scaling_benchmark(method)
    end
end

# Run as follows for single-threaded tests
# julia --project=. --threads=1 matmul.jl

# Run as follows for multi-threaded tests
# julia --project=. --threads=10 matmul.jl

scaling_benchmarks()
