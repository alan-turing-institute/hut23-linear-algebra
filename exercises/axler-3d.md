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
in the range of $T$ (it takes $T(\vec{v})$ to $`S(\vec{v})`$) so we need
to ensure (a) the this action is linear and (b) that it does something
sensible on other vectors to make it invertible. Our usual approach to
saying what we mean by “other vectors” is to choose a basis for $W$
that contains a basis for $\text{range }T$.

That is: (1) choose a basis for the range of $T$, say $\vec{e}_1,
\dots, \vec{e}_m$, and then (2) extend to a basis for $W$, say
$`\vec{e}_1, \dots, \vec{e}_m, \vec{e}_{m+1}, \dots, \vec{e}_n`$. With
this basis, every element of $W$, say $\vec{w}$, can be written as
$`\vec{w} = \sum_i w_i \vec{e}_i`$, which is

```math
\vec{w} = \sum_i w_i \vec{e}_i = \sum_{i=1}^{m} w_i \vec{e}_i +
\sum_{j=m+1}^n w_j \vec{e}_j
```

That is, every vector in $W$ can be written as the sum of an element
of $\text{range }T$ plus a vector not in the range of $T$.

So now, for $\vec{w}\in W$, define $E$ in the following way. Write
$\vec{w} = \vec{u}+\vec{u}'$, where $\vec{u}\in\text{range }T$. Since
$\vec{u}\in\text{range }T$, there must be some place in $V$ from which
this came: there must be some $\vec{v}\in V$ (not necessarily unique)
such that $\vec{u} = T(\vec{v})$. We'd like to set $E(\vec{u}) =
S(\vec{v})$, but we have the problem that the $v$ is not necessarily
unique. Fortunately, the only ways that there can be multiple
$`\vec{v}`$s with $\vec{u}=T(\vec{v})$ is if they differ by elements
of the null space.

That is, suppose $\vec{v}'$ is also such that $T(\vec{v}') =
\vec{u}$. Then $T(\vec{v}'-\vec{v}$) = \mathbf{0}$; in other words,
$\vec{v}'-\vec{v}$ is in the null space of $T$. Therefore, by
supposition, $\vec{v}'-\vec{v}$ is in the null space of $S$. Therefore
$S(\vec{v}') = S(\vec{v})$ and so there is no ambiguity in setting
$E(\vec{u}) = S(\vec{v})$.

We are nearly done with the definition of $E$. We want to define
$E(\vec{w})$ for some arbitrary $\vec{w}$, where however we have
written $\vec{w} = \vec{u]+\vec{u}'$, with $\vec{u}\in\text{range
T}$. We know what we want from $E(\vec{u})$ (it's wherever $S$ takes
the vector that $T$ sent to $\vec{u}$) but what about $E(\vec{u}')$? 
