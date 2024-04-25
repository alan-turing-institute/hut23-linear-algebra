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

Roughly, the story here is that the null space of $T$ — that is, the
set of $x$ for which $T(x)=0$ — is a subspace. It’s the subspace of
everything in $V$ that $T$ “projects down onto 0.” So one could
imagine that the set of “everything in $V$ that $T$ projects down onto
$c$“ is a very similar space, and that is what we are trying to show.

Either $c$ is in the range of $T$ or it isn't. If it is not, then
there is no $x\in V$ with $T(x)=c$ (by definition) and so $X$, the set
of all such $x$, is empty. So now suppose instead that $c$ is in the
range of $T$; that is, there is some (not necessarily unique) $t\in V$
with $T(t)=c$.

We will show that $X$ is $t+\text{null }T$ (the translate of
$\text{null }T$ by $t$). To show $X = t+\text{null }T$ we must show
$X\subset t+\text{null }T$ and $t+\text{null }T\subset X$.

For any $x\in t+\text{null }T$, we have $T(x) = T(t)$ (by
definition of the null) and hence $T(x) = c$, whence $x\in X$. Thus
$t+\text{null }T \subset X$.

Conversely, take $x\in X$ and consider $x-t$. We have
$T(x-t)=T(x)-T(t)=c-c=0$. Thus $x-t$ is in the null of $T$. So $x$
can be written as $x = t+(x-t)$, with $x-t\in\text{null }T$. Thus
$x\in t+\text{null T}$ and so $X\subset t+\text{null T}$.

### (b)

Explain why the set of solutions to a system of linear equations such
as 3.27 is either the empty set or is a translate of some subspace of
$\mathbf{F}^n$.

### Answer

A system of equations like 3.27 just is the matrix version of
$T(x)=c$. So either there are no solutions, or the solution set is a
translate of $\text{null }T$, meaning it is a translate of some
$\mathbf{F}^n$ (the one that is isomorphic to $\text{null }T$).

NB: A translate of $\text{null }T$ is some hyerplane; so now we know
how to write linear constraints.

## Question 13

Suppose $U$ is a subspace of $V$ such that $V/U$ is
finite-dimensional. Prove that $V$ is isomorphic to $U\times (V/U)$.

### Answer

Well $V/U$ might be finite-dimensional, but that doesn’t mean $U$ or
$V$ are, so once again we’ll need to find an actual isomorphism. That
is, we need an invertible map $U\times (V/U)\leftrightarrow V$.

$V/U$ is the vector space of translates of $U$ in $V$. So an element
of $U\times (V/U)$ is a pair $(u, \rho)$ with $u\in U$ and $\rho$ a
translate of $U$.

A translate of $U$, like $\rho$, is a subset of $V$ of the form $r+U$
for some $r$. We'd like to identify $(u, \rho)$ with the vector
$u+r\in V$: that would provide a map from $U\times (V/U)$ to $V$. But
the problem is that this $r$ is not unique. Adding any element of $U$
to $r$ produces the very same translate $\rho$.

However, $V/U$ is finite-dimensional, so has a basis $(\sigma_1,
\dotsc, \sigma_n)$ for some $n$. Each of the $\sigma_i$ is a translate
of $U$ in $V$; that is, it is a subset of the form $e_i + U$ for some
$e_i$. Fix these $e_i$. (That is, for each $i$, choose _some_ $e_i$ so
that $\sigma_i$ is the translate $e_i+U$.) 

Another way to say this is that the $e_i$ are chosen such that
$\pi(e_i) = \sigma_i$ where $\pi$ is the quotient map $\pi:V\to V/U$.

We will use these basis elements, and the specific choice of $e_i$, to
choose, consistently, a particular $r\in V$ which generates the
subspace $\rho$, in the following way. For any $\rho$, write $\rho =
\sum_i\alpha_i\sigma_i$ (that is, the $\alpha_i$ are the components of
$\rho$ in the basis $\sigma_i$). Now set $r=\sum_i\alpha_i e_i$, the
same linear combination but back in $V$. Now we can identify
$(u,\rho)\in U\times(V/U)$ with $u+r\in V$.

That is one direction of the map. (Again, you do have to convince
yourself that this is a _linear_ map, but since every operation we use
is linear, that is reasonably straightforward to do.)

For the other direction, first note that the $e_i$ (in $V$) are
linearly independent. For, supposing $\sum_i\alpha_i e_i=0$ for some
$\alpha_i$, it follows that $\sum_i\alpha_i \pi(e_i) = \sum_i\alpha_i
\sigma_i =0$, and therefore, since the $\sigma_i$ are linearly
independent, that all the $\alpha_i$ are necessarily zero.

Now, for any $v\in V$, compute $\pi(v)$ (an element of $V/U$) and
write it in terms of the $\sigma$s, say
$\pi(v)=\sum_i\beta_i\sigma_i$. Set $r= \sum_i\beta_i e_i$ and observe
that $(v - r)$ is an element of $U$. Define a map $V\to U\times
(V/U)$ by $v\mapsto (v - r, \pi(v))$.

To tie everything up, we need to show that these two maps are inverses
of each other.

