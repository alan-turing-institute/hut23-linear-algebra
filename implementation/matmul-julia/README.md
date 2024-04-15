To install dependencies:
```
julia --project=. -E "using Pkg; Pkg.instantiate()"
```

To run the benchmark:
```
julia --project=. matmul.jl
```

See source code for details, including some benchmarks for StaticArrays that I've commented
out.
