# Exercises from Axler 3.B

1, 2, 3, 9; 25, 27, 29.


## Question 1

Give an example of a linear map with $\text{dim null }T = 3$ and
$\text{dim range }T = 2$.

### Answer

The dimension of the domain must be 5. So let
$M:\mathbf{R}^5\to\mathbf{R}^5$ be given by:

```math
M \colon (x_1, x_2, x_3, x_4, x_5) \mapsto (0, 0, 0, x_4, x_5).
```

## Question 2

Suppose $S, T\in\mathcal{L}(v)$ are such that $\text{range }S\subseteq \text{null
}T$. Prove that $(ST)^2 = 0$.

### Answer

$(ST)^2$ means $STST$, where the rightmost map acts first. If we write
the map $S$, say, acting on $V$ as $V\stackrel{S}{\to} V$, then $STST$
can be written:

```math
V \xrightarrow{T} V \xrightarrow{S} V \xrightarrow{T} V \xrightarrow{S} V. 
```

In the middle, there is an $S$ followed by a $T$. Everything in first
$V$ ends up in the range of $S$, after the $S$. But this set is in the
null space of $T$, so after the $T$, everything ends up as the zero
vector.

## Question 3

Suppose $v_1, \dotsc, v_m \in V$. define $T$ by

```math
T \colon \mathbf{F}^m \to V
```

```math
T \colon (z_1, \dotsc, z_m) \mapsto \sum_i z_i v_i.
```

### (a) 

What property of $T$ corresponds to $v_1,\dotsc, v_m$ spanning $V$?

The span of a list of vectors is the set of all linear combinations of
those vectors (Axler, definition 2.4). The right-hand side of the
definition of $T$ is a particular linear combination of the $`v`$’s, and
the range of $T$ is _all_ linear combinations of the $`v`$’s. So the
$`v`$’s span $V$ if the range of $T$ is precisely $V$.


### (b) 

What property of $T$ corresponds to the list $v_1, \dotsc, v_m$ being
linearly independent?

A list of vectors is linearly independent if the only linear
combination of them that is the zero vector is the one in which all
coefficients are zero. (Axler, definition 2.15). The null space of $T$
is the set of $`z`$’s that map under $T$ to the zero vector. So the
condition of linear independence is that the null space of $T$ is just
$(0, 0,\dotsc, 0)\in \mathbf{F}^m$.

## Question 9

Suppose $T\in \mathcal{L}(V, W)$ is injective and $v_1, \dotsc, v_n$
is linearly independent in $V$. Prove that $Tv_1, \dotsc, Tv_n$ is
linearly independent in $W$.

### Answer

The rough intuition here is as follows: For $Tv_i$ to be not linearly
independent, we would need to reduce the dimension of the space
spanned by the $v_i$ to the space spanned by the $Tv_i$. But reducing
the dimension means that we must “collapse some directions,” which
would necessarily mean that the map is many-to-one and not injective.

More formally, suppose some linear combination of the $Tv_i$ is
zero. That is, there are $\alpha_i$ such that $\sum_i \alpha_i
T(v_i)=\mathbf{0}$. To show linear indepenence of the $Tv_i$ we must
show that all the $\alpha_i$ are necessarily zero.

By linearity of $T$, we must have $T(\sum_i \alpha_i
v_i)=\mathbf{0}$. Either the sum $\sum_i \alpha_i v_i$ is zero, or it
is not. Suppose it is not. Then we would have $T(v)=\mathbf{0}$ for
some $v\neq 0$. But $T(\mathbf{0}) = 0$ (because $T$ is linear) and so
$T$ is not injective (because both $v$ and $\mathbf{0}$ map to
zero). But $T$ is injective, by supposition, and so we must have
$\sum_i \alpha_i v_i = 0$. But now, since the $v_i$ are supposed to be
linearly independent, and so the only $\alpha_i$ for which this is
true are $\alpha_i = 0$.

## Question 25

Suppose that $W$ is finite-dimensional and $S, T\in
\mathcal{L}(V,W)$. Prove that $\text{null }S \subseteq \text{null }T$
if and only if there exists $E\in\mathcal{L}(W)$ such that $T=ES$.

### Answer

The intuition here is that $T$ has a larger null space than $S$ and so
after applying $S$ we need to “collapse some more directions with $E$
in order to get to the effect of $T$”. What is perhaps surprising is
that we are guaranteed such an $E$ exists.

The easy direction of the “if and only if” is to show that if $T=ES$
(for some $E$) then $\text{null }S \subseteq \text{null }T$. Indeed,
let $v\in\mathcal{V}$ be any vector in the null space of $S$, so that
$S(v)=0$. Then for any $E$, we have $T(v) = E(S(v)) = E(\mathbf{0}) =
\mathbf{0}$, and so $v$ is necessarily in the null space of $T$. Thus
$v\in\text{null }S \implies v\in\text{null }T$.

For the other direction, suppose that for some $S, T$ we have
$\text{null }S \subseteq \text{null }T$. How can we construct the
required $E$? One way is to give its action on a list of basis vectors
(this is the “linear map lemma,” Axler 3.4). A particular choice of
basis springs to mind: Let $u_1, \dotsc, u_m$ be a basis for the null
space of $S$ (noting that the null space is a vector space) and let
$u_1, \dotsc, u_m, e_1, \dotsc, e_n$ be an extension to a basis of
$\mathcal{V}$. (Such an extension exists by Axler 2.32.)

We now want $E$ to “do the same thing as $T$ to elements of $\mathcal{V}$, but
after they have been acted on by $S$.” That is, to define $E(w)$ we
find $v\in\mathcal{V}$ such that $w=S(v)$ and set $E(w) = T(v)$.

Consider the set of vectors $S(e_i)$. This is a linearly independent
set. (If it were not, there would be some $\alpha_i$ not all zero such
that $\sum_i \alpha_i S(e_i) = \mathbf{0}$, and therefore that
$S(\sum_i\alpha_i e_i) = \mathbf{0}$; in other words that $\sum_i
\alpha_i e_i$ is in the null space of $S$. But the null space of $S$
is spanned by the $u_i$, by construction, so can't include some of the
$e_i$.)

Extend this set to basis for $\mathcal{W}$, say $S(e_1), \dotsc,
S(e_n), f_1, \dotsc, f_o$.  Now define $E$ as follows. For any
$w\in\mathcal{W}$, write $w$ as

```math
w = \sum_i \beta_i S(e_i) + \text{terms involving }f_i,
```

and set

```math
E(w) \equiv \sum_i \beta_i T(e_i).
```

(So $E$ “does the right thing on the range of $S$, and otherwise is
zero”.)

Claim: this defines the required $E$. Proof: Suppose
$v\in\mathcal{V}$. Write $v=\sum_i \alpha_i u_i + \sum_j \beta_j
e_j$. Noting that $T(u_i) = 0) (since the null space of $T$ is at
least the null space of $S$) we have $T(v) = \sum_j \beta_j T(e_j)$
and, by construction $E(S(v)) = \sum_j \beta_j E(S(e_j)) = E(\sum_j
\beta_j S(e_j)) = \sum_j \beta_j T(e_j)$.

It's worthwhile noting that if the null space of $T$ were _smaller_
than the null space of $E$, we would have $T(u_k) \neq \mathbf{0}$ for
some $k$ and so we would have “had to make $E$ do something with
$S(u_k)$,” but there is nothing $E$ could have done except return
$\mathbf{0}$.
