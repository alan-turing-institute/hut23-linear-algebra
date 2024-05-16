using Plots
using CSV
using DataFrames
using Plots.PlotMeasures

df = CSV.read("../results.csv", DataFrame)
count = size(df, 2) - 1

dims = Dict()
times = Dict()

dims_array = [2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192, 256, 384, 512, 768, 1024]

for row in eachrow(df)
    dims[row[:method]] = dims_array
    times[row[:method]] = [row[i] for i in 2:count + 1]
end

p = plot()
for key in keys(times)
    plot!(p, dims[key], times[key], label=key, lw=2, marker=:cross, ms=5, alpha=0.7)
end

# Add the theoretical scaling slope
fastest_largest = minimum([times[key][end] for key in keys(times)])
max_dim = minimum([dims[key][end] for key in keys(dims)])
min_dim = 10
plot!(p, [min_dim, max_dim], [fastest_largest * min_dim^3 / max_dim^3, fastest_largest], label="O(n^3)", lw=2, color=:grey, alpha=0.5, dpi=360, thickness_scaling=0.5, margin=64px)

plot!(p, xscale=:log10, yscale=:log10, xlabel="Matrix dimension", ylabel="Time (s)", legend=:bottomright, title="\nTime to multiply two square matrices as a function of matrix size")

savefig(p, "../results.svg")
savefig(p, "../results.png")
