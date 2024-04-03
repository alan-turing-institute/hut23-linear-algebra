# I use the `reticulate` package to interface with Python/Numpy and load the
# test data. See
# https://rstudio.github.io/reticulate/articles/python_packages.html for more
# details on how to get that running I use the `bench` package to actually run
# benchmarking, rather than manually running and timing loops etc.

# Uncomment the following line to install the packages, but you will then also want
# to set up `reticulate` as per the instructions linked above.
# install.packages(c("reticulate", "bench"))

library(reticulate)
use_miniconda("r-reticulate")
np <- import("numpy")
all_mats <- np$load("matrices.npz")

a_matrices <- lapply(
  paste0(grep("a_",
              all_mats$files,
              value = TRUE),
         ".npy"),
  function(x) all_mats$f[[x]])

b_matrices <- lapply(
  paste0(grep("b_",
              all_mats$files,
              value = TRUE),
         ".npy"),
  function(x) all_mats$f[[x]])

c_matrices <- lapply(
  paste0(grep("c_",
              all_mats$files,
              value = TRUE),
         ".npy"),
  function(x) all_mats$f[[x]])

multiply_matrices <- function(a_mats, b_mats) {
  lapply(
    seq_along(a_mats),
    function(x) a_mats[[x]] %*% b_mats[[x]]
  )
}

bench_results <- bench::mark(
  multiply_matrices(a_matrices,
                    b_matrices),
  iterations = 32768
)

paste("Total time elapsed:", bench_results$total_time)
paste("Operations per sec:", round(bench_results$`itr/sec` * 512, 2))
