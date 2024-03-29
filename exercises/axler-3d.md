# Exercises from Axler 3.C

1, 2, 6, 9, 18, 21

## Question 1

Suppose $T\in\mathcal{L}(V, w)$ is invertible. Show that $T^{-1}$ is
invertible and $(T^{-1})^{-1} = T$.

### Answer

When asked to show that something has a certain property, it's often
best to go back to the definition of that property. A linear map
$R:V\to W$ is invertible (this is definition 3.59) if there exists an
$S:W\to V$ such that $RS$ is the identity on $W$ and $SR$ is the
identity on $V$.

So, in order to show that some linear map (say $T^{-1}$) is
invertible, we must exhibit another linear map with the required
properties.

The obvious candidate for an inverse of $T^{-1}$ is $T$. Let's check
whether it is. We need to check that $T^{-1}T$ is the identity on $V$
and that $TT^{-1}$ is the identity on $W$. And indeed they are --
because _those_ conditions are precisely the meaning of $T^{-1}$
(which we are assured exists by the question).

## Question 2

Suppose $T\in \mathcal{L}(U, V)$ and $S\in \mathcal{L}(V, W)$ are both
invertible. Prove that $ST$ is invertible and that $(ST)^{-1} =
T^{-1}S^{-1}$.

### Answer

To prove that something is invertible we must exhibit its
inverse. Fortunately, the question has told us what the inverse is, so
what we need to do is check that it does in fact satisfy the
conditions for being an inverse.

That is, we need to show: (1) that $\bigl(ST\bigr) \bigl(
T^{-1}S^{-1}\bigr)$ is the identity on $W$; and (2) that $\bigl(
T^{-1}S^{-1}\bigr) \bigl(ST\bigr)$ is the identity on $U$.

To show (1), note that composition of linear maps is associative --
that is, it doesn't matter where we put the parentheses. Thus, roughly
speaking, we can “cancel the inner $`T`$s” and then, having got rid of
those, “cancel the outer $`S`$s.”

More carefully, $\bigl(ST\bigr) \bigl( T^{-1}S^{-1}\bigr) = S(T
T^{-1})S^{-1}$ because composition is associative. And that is
$S\mathbf{1}_V S^{-1}$, which is $SS^{-1}$ which is
$\mathbf{1}_W$. The same argument works for (2).

## Question 6

Suppose that $W$ is finite-dimensional and $S, T\in\mathcal{L}(V,
W)$. Prove that $\text{null } S = \text{null } T$ if and only if there
exists an invertible $E\in\mathcal{L}(W)$ such that $S=ET$.

### Answer

Suppose $\text{null } S = \text{null } T$. We'll try to construct the
required $E$. Roughly speaking, we know what $E$ has to do on vectors
in the range of $T$ (it takes $T(\vec{v})$ to $S(\vec{v})$) so we need
to ensure (a) the this action is linear and (b) that it does something
sensible on other vectors to make it invertible.

Our usual construction is: (1) choose a basis for $\text{range } T$,
say $\vec{e}_1, \dots, \vec{e}_m$ and then (2) extend to a basis for
$W$, say $\vec{e}_1,\dots,\vec{e}_m, \vec{e}_{m+1},\dots
\vec{e}_{n}$. With this basis, every element of $W$, say $\vec{w}$,
can be written as $\sum_i w_i \vec{e}_i$, which is $\sum_{i=1}^{m} w_i
\vec{e}_i + \sum_{j=m+1}^n w_j \vec{e}_j$ -- that is, the sum of an
element of $\text{range }T$ plus a vector not in the range of $T$.


