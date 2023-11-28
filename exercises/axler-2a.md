# Exercises from Axler 2.A

## Question 5

Find a number $t$ such that $`\{(3,1,4), (2,−3,5), (5,9,t)\}`$
is not linearly independent in $\mathbb{R}^3$.

### Answer

If the set is to be not linearly independent, then one of the elements
must be expressible as a linear combination of the others. That is,
there are numbers $\alpha$ and $\beta$ such that

```math
\alpha(3,1,4) + \beta(2,-3,5) = (5, 9, t).
```

The plan is to find $\alpha$ and $\beta$ that make this equation true
and then compute $t$. There are really three equations, one for each
of the components:

```math
\begin{align}
3\alpha + 2\beta &= 5 \\
1\alpha+(-3)\beta &= 9 \\
4\alpha+5\beta &= t.
\end[align}
```

The first two are two equations in two unknowns. The solution is
$\alpha = 3$ and $\beta = -2$. (I rearranged the second to get
$\alpha$ in terms of $\beta$ and then substituted this into the
first.)

Finally, from the third equation, now we know $\alpha$ and $\beta$, $t
= 2$.

Just to summarise what we have shown, it is that $(5, 9, t)$ can be
written as a linear combination of $(3,1,4)$ and $(2,-3,5)$ when
$t=2$.

## Question 9

Prove or give a counterexample: If $v_1$, $v_2$, ..., $v_m$ is a
linearly independent list of vectors in $V$, then

```math
5v_1 − 4v_2, v_2, v_3, \dotsc , v_m
```

is linearly independent.

### Answer



## Question 12

Suppose $v_1$, ..., $v_m$ is linearly independent in $V$ and $w
\subset V$. Prove that if $v_1 + w$, ..., $v_m + w$ is linearly
dependent, then $w \not\in \text{span}(v_1, \dotsc, v_m)$.

## Question 17

Prove that $V$ is infinite-dimensional if and only if there is a
sequence $v_1$, $v_2$, ... of vectors in $V$ such that $v_1$, $v_2$,
..., $v_m$ is linearly independent for every positive integer $m$.

### Answer

Let's start with the "if" direction. We are given a sequence of
vectors $v_1$, $v_2$, ... such that every initial subsequence, $v_1$,
..., $v_m$ is linearly independent, and we're to show that the vector
space must be infinite dimensional.

To prove something, it is necessary to know what that thing is. So we
should look back in Axler to see what "infinite dimensional"
_means_. Axler says, "A vector space is called _infinite-dimensional_
if it is not finite dimensional" (this is 2.13 in the fourth
edition). Which means we need to know what "finite dimensional
means". Axler says, "A vector space is called _finite-dimensional_ if
some list of vectors in it spans the space" (this is 2.9).

Remember that to Axler, "list" means "finite list".

So to show that our vector space is infinite dimensional, we must show
that there is _no_ list of vectors which spans the space.

Suppose, for contradiction, that there were such a list, say $e_1$,
$e_2$, ..., $e_N$. We don't know what $N$ is, but there must be an $N$
by supposition. The intuition here is that if that list really did
span the space, then the list $v_1$, $v_2$, ..., $v_{N+1}$ would be
linearly _dependent_



