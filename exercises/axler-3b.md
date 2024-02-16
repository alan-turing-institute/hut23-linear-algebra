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

$(ST)^2$ means $(S\circ T)\circ (S\circ T)$, which is the same as
$S\circ T\circ S\circ T$, where the rightmost map acts first. If we write
the map $S$, say, acting on $V$ as $V\stackrel{S}{\to} V$, then you
can think of $STST$ as this sequence of maps:

```math
V \xrightarrow{T} V \xrightarrow{S} V \xrightarrow{T} V \xrightarrow{S} V. 
```

In the middle, there is an $S$ followed by a $T$. Everything in first
$V$ ends up in the range of $S$, after the $S$. But this set is in the
null space of $T$, so after the $T$, everything ends up as the zero
vector.

## Question 3

Suppose $v_1, \dotsc, v_m \in V$. Define $T$ by

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

The rough intuition here is as follows: For the $Tv_i$ to _not_ be linearly
independent, we would need to reduce the dimension of the space
spanned by the $v_i$ to the space spanned by the $Tv_i$. But reducing
the dimension means that we must “collapse some directions,” which
would necessarily mean that the map is many-to-one and not injective.

More formally, suppose some linear combination of the $Tv_i$ is
zero. That is, suppose there are $\alpha_i$ such that $\sum_i \alpha_i
T(v_i)=\mathbf{0}$. To show linear indepenence of the $Tv_i$ we must
show that all the $\alpha_i$ are necessarily zero.

By linearity of $T$, we must have $T(\sum_i \alpha_i
v_i)=\mathbf{0}$. Now, either the sum $\sum_i \alpha_i v_i$ is the
zero vector, or it is not. Suppose it is not. Then we would have
$T(v)=\mathbf{0}$ for some $v\neq \mathbf{0}$. But $T(\mathbf{0}) = 0$
(because $T$ is linear) which implies that $T$ is not injective
(because both $v$ and $\mathbf{0}$ map to zero). But $T$ is injective,
by supposition, and so in fact we must have $\sum_i \alpha_i v_i =
\mathbf{0}$. But now, since the $v_i$ are supposed to be linearly
independent the only $\alpha_i$ for which this is true are, as we
needed to show, $\alpha_i = 0$.

## Question 25

Suppose that $W$ is finite-dimensional and $S, T\in
\mathcal{L}(V,W)$. Prove that $\text{null }S \subseteq \text{null }T$
if and only if there exists $E\in\mathcal{L}(W)$ such that $T=E\circ S$.

### Answer

The intuition here is that $T$ has a larger null space than $S$ and so
in order to get the same effect as $T$ after applying $S$ we need to
“collapse some more directions with $E$. What is perhaps surprising is
that we are guaranteed the existence of an $E$ which “does the right
thing to all the vectors not in the null space.”

The easy direction of the “if and only if” is to show that if
$T=E\circ S$ (for some $E$) then $\text{null }S \subseteq \text{null
}T$. Indeed, let $v\in V$ be any vector in the null space of $S$, so
that $S(v)=\mathbf{0}$. Then we have $T(v) = E(S(v)) = E(\mathbf{0}) =
\mathbf{0}$, and so $v$ is necessarily in the null space of $T$.

For the other direction, suppose that for some $S, T$ we have
$\text{null }S \subseteq \text{null }T$. How can we construct the
required $E$? One way is to give its action on a list of basis vectors
(this is the “linear map lemma,” Axler 3.4). $E$ acts on $W$, so we
need a basis for $W$, and luckily $W$ is supposed to be
finite-dimensional.

So, let $(e_1, \dotsc, e_n)$ be a basis for $\text{range }S$, and
extend to a basis of $W$ by adding $(f_1, \dotsc, f_m)$. (An
extension always exists by Axler 2.32.)

We now want $E$ to “do the same thing as $T$ to elements of $V$, but
after they have been acted on by $S$.” That is, to define $E(w)$, we
find $v\in V$ such that $w=S(v)$ and set $E(w) = T(v)$.

So, for each $e_i$ choose some $u_i\in V$ such that $e_i = S(u_i)$. (There
must be one, since $e_i$ is in the range of $S$.) Now define $E$ as
follows. For any $w\in W$, write $w$ as

```math
w = \sum_i \beta_i e_i + \text{terms involving }f_i,
```

and set

```math
E(w) \equiv \sum_i \beta_i T(u_i).
```

(So $E$ “does the right thing on the range of $S$, and otherwise is
zero”.)

Claim: this defines the required $E$. Proof: it clearly does the right
things on any $u_i \in V$ (by construction!). So it does the right
thing on a linear combination of the $u_i$. What about vectors in $V$
that are not linear combinations of the $u_i$? It will turn out that
those can be written as a linear combination of the $u_i$ plus
something in the null space of S and, since that is a subset of the
null space of T, that part will go to zero. 

Indeed, let $v\in V$ be arbitrary and find (the unique) $\alpha_i$
such that $S(v) = \sum_i \alpha_i e_i$. Write $w = \sum_i \alpha_i
u_i$. Note that, by construction $E(S(w)) = T(w)$. 

Now note that $v - w$ is in the null space of $S$. (To see this, note
that $S(v-w) = \mathbf{0}$ by construction.) Set $n = v-w$ so that (1)
$v = w + n$; (2) $w\in\text{span }(u_1, \dotsc, u_m)$; (3)
$n\in\text{null }S$. These three conditions are true of any $v$. And
since $\text{null }S\subset \text{null }T$, we have $T(n) =
\mathbf{0}$ and so $T(v) = T(w)$. Thus $E(S(v)) = E(S(w) = T(w) =
T(v)$.






## Question 27

Suppose $P\in \mathcal{L}(V)$ and $P^2 = P$. Prove that $V =
\text{null }P \oplus \text{range }P$.

### Answer

The main challenge here is that the question doesn't specify that $V$
is finite-dimensional so we can't use the “choose a basis” trick. (As
a matter of fact, it is true that every vector space has a basis but
Axler hasn't shown that.)

We need to show two things: first that the sum of $\text{null }P$ and
$\text{range }P$ is a _direct_sum; and second, that this sum spans all
of $V$.

Recall that a sum is a direct sum if and only if the two summands have
only the zero vector in common. (This is result 1.46 in Axler.)
Suppose $v$ is some vector in both $\text{null }P$ and $\text{range
}P$. What can we say about it?

Since $v\in\text{null }P$, we have 

```math
P(v) = \mathbf{0}.
```

Now, if $v\in\text{range }P$ there must be some $w\in V$ such that
$P(w) = v$ (that's what being in the range means). Thus

```math
\begin{align}
P(P(w)) &= P(v) \\
        &= \mathbf{0}.
\end{align}
```

All of this is true for any $P$. But this $P$ has the special property
that $P(P(w)) = P(w)$, so the last result tells us that $P(w) =
\mathbf{0}$. But $P(w)=v$! So we have shown that $v=\mathbf{0}$. In
other words, if $v$ is in both $\text{null }P$ and $\text{range }P$,
then $v$ is the zero vector, which implies that the sum is a direct
sum.

Could there be a vector that is not the sum of a vector in $\text{null
}P$ and one in $\text{range }P$? Let $v$ be any vector. We shall show
that $v$ can be writen as the sum of a vector in the null space and a
vector in the range by explicitly constructin the two parts.

Write $u=P(v)$ (so that in particular, $u\in\text{range }P$. Now
consider the vector $v-u$. We claim that this vector is in the null
space of $P$, from which the result will follow.

Indeed 
```math
\begin{align}
P(v-u) &= P(v)-P(u) \\
       &= P(v)-P(P(v)) \;\text{by definition of }u \\
	   &= P(v)-P(v)    \;\text{by property of }P \\
	   &= \mathbf{0}.
\end{align}
```

Thus $v-u$ is in the null space of $P$, and since $v = u + (v-u)$, we
have written $v$ as the sum of a vector in $\text{null }P$ and a
vector in $\text{range }P$.


## Question 29

Suppose $p\in \mathcal{P}(\mathbf{R})$. Prove that there exists a
polynomial $q\in \mathcal{P}(\mathbf{R})$ such that $5q'' + 3q' = p$.

### Answer

Worth noting that we're being asked to prove the existence of a
solution to a differential equation ... which is reasonably cool!

The derivative of a polynomial is another polynomial; and in fact the
following map

```math
\begin{gather}
\Delta \colon \mathcal{P}(\mathbf{R}) \to \mathcal{P}(\mathbf{R}) \\
q \mapsto 5q'' + 3q',
\end{gather}
```

is a linear map. To prove existence we need to show that this map is
surjective. 

In fact, we can say something more about this map. Any particular
polynomial is an element of $\mathcal{P}_n(\mathbf{R})$ (a
finite-dimensional space!) for some $n$. On that space, the map can be
written,

```math
\begin{gather}
\Delta \colon \mathcal{P}_n(\mathbf{R}) \to \mathcal{P}_{n-1}(\mathbf{R}) \\
q \mapsto 5q'' + 3q',
\end{gather}
```

(The term in $q''$ “goes down two degrees” and the term in $q'$ “goes
down one degree.) 

So by the fundamental theorem of linear maps (3.21) we have $\text{dim
}\mathcal{P}_n(\mathbf{R}) = \text{dim null }\Delta + \text{dum range
}\Delta$. 

We know $\text{dim }\mathcal{P}_n(\mathbf{R})$: it is $n+1$. What
about $\text{dim null }\Delta$? 

The solutions to $\Delta f = 0$ must be of the form $f(x) = A$, where
$A$ is a constant. There can't be a term $x$, $x^2$ or higher. If
the highest-order term were $x^n$, say, for $n>1$, then there would be
a term in $x^{n-1}$ is $\Delta f$, which means that the result could
not be zero. 

The dimension of this space is 1. So we have $\text{dim range }\Delta
= (n+1) - 1 = n$.

But that is the dimension of the codomain of $\Delta$! So the range of
$\Delta$ must in fact span the codomain. Hence, $\Delta$ is
surjective. 





