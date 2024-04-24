# Exercises from Axler 3.E

3, 8, 13.

## Question 3

Suppose $V_1, \dots, V_m$ are vector spaces. Prove that
$\mathcal{L}(V_1\times\dotsb\times V_m, W)$ and $\mathcal{L}(V_1, W)
\times\dotsb\times \mathcal{L}(V_m, W)$ are isomorphic vector spaces.

### Answer

If all the vector spaces were finite-dimensional, we could show that
the dimension of each side matched and be done. Like this:

```math
\begin{aligned}
\text{dim }\mathcal{L}(V_1\times\dotsb\times V_m, W) 
  &= \text{dim }(V_1\times\dotsb\times V_m)\times\text{dim }W \\
  &= \left(\sum_{i=1}^m \text{dim }V_i\right)\times\text{dim }W \\
  &= \sum_{i=1}^m (\text{dim }V_i\times\text{dim }W), 
\end{aligned}
```

whereas

```math
\begin{aligned}
\text{dim } \mathcal{L}(V_1, W)\times\dotsb\times \mathcal{L}(V_m, W)
  &= \sum_{i=1}^m (\text{dim }V_i\times\text{dim W}).
  \end{aligned}
```

However, it is not stated that they are finite-dimensional. So let us
try to exhibit an isomorphism.

An element of $\mathcal{L}(V_1\times\dotsb\times V_m, W)$, say $\rho$,
is a map from tuples $(v_1, \dotsc, v_m)$ (where $v_i\in V_i$) to
$W$. For each $i$, define $\rho_i\in \mathcal{L}(V_i, W)$ by
$\rho_i(v_i) = \rho((0,\dotsc,0,v_i,0,\dotsc,0))$ for any $v_i\in
V_i$. The tuple $(\rho_1,\dotsc,\rho_m)$ is an element of
$\mathcal{L}(V_1, W) \times\dotsb\times \mathcal{L}(V_m, W)$. Thus we
have a map,

```math
\begin{aligned}
M\colon \mathcal{L}(V_1\times\dotsb\times V_m, W) &\to \mathcal{L}(V_1, W)
\times\dotsb\times \mathcal{L}(V_m, W) \\
\rho &\mapsto (\rho_1, \dotsc, \rho_m).
\end{aligned}
```

This map is injective since two different $\rho$'s must differ on some
$V_i$.

Conversely, let $(\rho_1,\dotsc,\rho_m)$ is some element of
$\mathcal{L}(V_1, W) \times\dotsb\times \mathcal{L}(V_m, W)$. For any
$(v_1,\dotsc,\v_m)\in V_1\times\dotsb\times V_m$, we obtain an element of $W$ by
$\sum_i \rho_i(v_i)$. 
