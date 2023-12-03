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
\begin{gathered}
3\alpha + 2\beta = 5 \\
1\alpha+(-3)\beta = 9 \\
4\alpha+5\beta = t.
\end{gathered}
```

The first two are two equations in two unknowns. The solution is
$\alpha = 3$ and $\beta = -2$. (I rearranged the second to get
$\alpha$ in terms of $\beta$ and then substituted this into the
first.)

Finally, from the third equation (now we know $\alpha$ and $\beta$) it
follows that $t = 2$.

Just to summarise what we have shown: $(5, 9, t)$ can be written as a
linear combination of $(3,1,4)$ and $(2,-3,5)$ when $t=2$.

## Question 8

Suppose $v_1$, $v_2$, $v_3$, $v_4$ is linearly independent in
$V$. Prove that the list 

```math
v_1 - v_2, v_2 - v_3, v_3 - v_4, v_4
```

is also linearly independent.

### Answer

What would it mean for the list to be linearly independent? It would
mean that, if there were $\alpha_i$ satisfying

```math
\alpha_1(v_1 - v_2) + \alpha_2(v_2 - v_3) + \alpha_3(v_3 - v_4) +
\alpha_4 v_4 = 0,
```

then necessarily those $\alpha_i$ would all be zero. 

Can we show that they are zero? Some rearranging of the term on the left
gives:

```math
\alpha_1 v_1 +(-\alpha_1 + \alpha_2)v_2 +(-\alpha_2 + \alpha_3) v_3 +
(- \alpha_3 + \alpha_4) v_4.
```



## Question 9

Prove or give a counterexample: If $v_1$, $v_2$, ..., $v_m$ is a
linearly independent list of vectors in $V$, then

```math
5v_1 − 4v_2, v_2, v_3, \dotsc , v_m
```

is linearly independent.

### Answer

The list would not be linearly independent only if there exist
$\alpha_i$ not all zero such that

```math
\alpha_1 (5v_1 - 4v_2) + \alpha_2 v_2 + \dotsb + \alpha_n v_n = 0.
```

However, the sum above is equivalent to:

```math
(5\alpha_1) v_1 + (- 4\alpha_1 + \alpha_2) v_2 + \dotsb + \alpha_n v_n = 0.
```

Since the $v_i$ are linearly independent by supposition, the only way
_that_ can be true is if all the coefficients are 0. That is:
$5\alpha_1 = 0$, $-4\alpha_1+\alpha_2 = 0$, $\alpha_3 = 0$, ...,
$\alpha_n = 0$. Thus in fact, $\alpha_i = 0$ for all $i$. In other
words, the original list is linearly independent.

## Question 12

Suppose $v_1$, ..., $v_m$ is linearly independent in $V$ and $w
\in V$. Prove that if $v_1 + w$, ..., $v_m + w$ is linearly
dependent, then $w \in \text{span}(v_1, \dotsc, v_m)$.

### Answer

For $v_1 + w$, ..., $v_m + w$ to be linearly dependent means that
there exist $\alpha_1$, ..., $\alpha_m$, not all zero, such that

```math
\alpha_1 (v_1 + w) + \dotsb + \alpha_m(v_m + w) = 0.
```

Some rearranging gives:

```math
\alpha_1 v_1 + \dotsb + \alpha_m v_m + (\alpha_1 + \dotsb + \alpha_m)
w = 0.
```

(We've pulled out the terms in $w$.) 

We'd like to rearrange this into an expression for $w$, but that will
involving dividing by $\alpha=\sum_i\alpha_i$. If that expression were
zero, we'd have a problem. But if the sum of the $\alpha_i$ were zero,
then the sum on the left, $\sum_i \alpha_i z_i$ would also be zero,
and that would mean that the $v_i$ are not linearly independent. So we
conclude that $\alpha$ is zero, and hence:

```math
w = -\frac{\alpha_1}{\alpha} v_1 - \dotsb - \frac{\alpha_m}{\alpha}
v_m = 0.
```

That is, we have written $w$ as a linear combination of the $v_i$,
which is precisely what it means for $w$ to be in the span of the
$v_i$.

## Question 17

Prove that $V$ is infinite-dimensional if and only if there is a
sequence $v_1$, $v_2$, ... of vectors in $V$ such that $v_1$, $v_2$,
..., $v_m$ is linearly independent for every positive integer $m$.

### Answer

Let's start with the "reverse" direction. We are given a sequence of
vectors $v_1, v_2, \dotsc, \in V$ such that every initial subsequence,
$v_1$, ..., $v_m$ is linearly independent; we're to show that the
vector space $V$ must be infinite dimensional.

To prove something, it is necessary to know what that thing is. So we
should look back in Axler to see what "infinite dimensional"
_means_. Axler says, "A vector space is called _infinite-dimensional_
if it is not finite dimensional" (this is 2.13 in the fourth
edition). Which means we need to know what "finite dimensional
means". Axler says, "A vector space is called _finite-dimensional_ if
some list of vectors in it spans the space" (this is 2.9).

Remember that to Axler, "list" means "finite list".

So to show that our vector space is infinite dimensional, we must show
that there is _no_ finite list of vectors which spans the space.

Suppose, for contradiction, that there were such a list, say $e_1$,
$e_2$, ..., $e_N$. We don't know what $N$ is, but there must be an $N$
by supposition that the list is finite. We're going to argue that that
if that list really did span the space, then, since $N+1$ $v$'s
($v_1$, $v_2$, ..., $v_{N+1}$) can be constructed from only $N$ $e$'s;
surely one of the $v$s would be a combination of the others. In fact,
Axler's theorem 2.22 says precisely this: the length of any linearly
independent list in $V$ must be no greater than the length of a list
that spans $V$. And so there must be no more linearly independent
$v$'s than $e$'s. But we can choose the list of $v$'s to be as long as
we like (by the antecedent of the claim) and so the only conclusion is
that there can't be any such list of $e$'s. In other words, there is
no finite list of vectors which spans $V$.

It is left to show the "forward" part. That is, we must show that if
$V$ is infinite dimensional, there exists an infinite set $v_1$,
$v_2$, ... such that $`\{v_1, v_2, \dots, v_n\}`$ is linearly
independent for any $n$.

One way to prove that something exists is to construct it. The idea is
to start with some $v_1$, add a new $v_2$ so that $`\{v_1, v_2\}`$ is
linearly independent, then add a $v_3$ such that $`\{v_1, v_2, v_3\}`$
is linearly independent, and so on; noting that we never get stuck.

We need to start by finding a $v_1$. Pick any vector that is not the
zero vector. (There must be one, otherwise $V$ would be finite
dimensional.) Now we need to find $v_2$. Choose any vector that is not
a multiple of $v_1$. There must be one for, if not, $v_1$ would span
$V$ all by itself and thus would be a list of vectors which spanned
$V$, and so $V$ would not be infinite dimensional.

In general, if we have found $v_1$, $v_2$, ..., $v_{n-1}$, and these
are linearly independent, then we choose $v_n$ to be a vector that is
not a linear combination of the first $n-1$ $v$'s. There must be one,
else $v_1$, ..., $v_{n-1}$ would span $V$ and $V$ would therefore not
be infinite-dimensional. Thus we can find a linearly independent list
of any length.
