To install dependencies:
```
julia --project=. -E "using Pkg; Pkg.instantiate()"
```

To run the benchmarks single-threaded:
```
julia --project=. --threads=1 matmul.jl
```

To run the benchmarks multi-threaded:
```
julia --project=. --threads=10 matmul.jl
```

Results will be saved out to the `results.csv` file.
Only result rows using the same method will be overwritten.

To render the graph for all results in the `results.csv` file run:
```
julia --project=. plots.jl
```

This will render the graph to two files: `results.png` and `results.svg`.

See source code for details, including some benchmarks for StaticArrays that I've commented out.
