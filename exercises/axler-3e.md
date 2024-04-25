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

Conversely, let $(\rho_1,\dotsc,\rho_m)$ be some element of
$\mathcal{L}(V_1, W) \times\dotsb\times \mathcal{L}(V_m, W)$. For any
$(v_1,\dotsc,v_m)\in V_1\times\dotsb\times V_m$, we obtain an element
of $W$ by $\sum_i \rho_i(v_i)$. It is not hard to see that this is the
inverse of $M$. (It is not hard, but it is annoying, to check
linearity of all the maps, which I have not done here.)

## Question 8

### (a)

Suppose $T\in \mathcal{L}(V,W)$ and $c\in W$. Prove that $`\{x\in V\mid
T(x) = c\}`$ is either the empty set or is a translate of $\text{null }T$.

### Answer

Write $`X = \{x\in V\mid T(x) = c\}`$.

Either $c$ is in the range of $T$ or it isn't. If it is not, then
there is no $x\in V$ with $T(x)=c$ (by definition) and so $X$, the set
of all such $x$, is empty. So now suppose instead that $c$ is in the
range of $T$; that is, there is some (not necessarily unique) $t\in V$
with $T(t)=c$.

Consider $t+\text{null }T$ (the translate of $\text{null }T$ by
$t$). To show $X\subset t+\text{null }T = t+\text{null }T\subset X$ we
must show $X\subset t+\text{null }T$ and $t+\text{null }T\subset X$.

For any $x\in t+\text{null }T$, we have $T(x) = T(t)$ (by
definition of the null) and hence $T(x) = c$, whence $x\in X$. Thus
t+\text{null }T \subset X$.

Conversely, take $x\in X$ and consider $x-t$. We have
$T(x-t)=T(x)-T(t)=c-c=0$. Thus $x-t$ is in the null of $T$. So $x$
can be written as $x = t+(x-t)$, with $x-t\in\text{null }T$. Thus
$x\in t+\text{null T}$ and so $X\subset t+\text{null T}$.

### (b)

Explain why the set of solutions to a system of linear equations such
as 3.27 is either the empty set or is a translate of some subspace of $\mathbf{F}^n$.
