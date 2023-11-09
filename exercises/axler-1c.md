# Exercises from Axler 1.C

## Question 1

For each of the following subsets of $\mathbf{F}^3$, determine whether
it is a subspace of $\mathbf{F}^3$.

### Answer

For each given subset, $V$, we must check that, for all
$\alpha\in\mathbf{F}$, and $v,w\in V$:

1. $\mathbf{0}\in V$;
2. $\alpha v \in V$; and
3. $v+w \in V$.

#### (a) $`\{(x_1, x_2, x_3)\in \mathbf{F}^3 \mid x_1 +2 x_2 +3 x_3 =0\}`$

This set is a subspace.

1. $\mathbf{0}$ is in $V$ since $\mathbf{0}=(0,0,0)$ and $0+2\times
   0+3\times 0 =0$, as required;
2. $\alpha v$ is in $V$ since, for $v=(v_1, v_2, v_3)$, we have
   $\alpha v = (\alpha v_1, \alpha v_2, \alpha v_3)$ and $(\alpha
   v_1) + 2(\alpha v_3) + 3(\alpha v_3) = \alpha (v_1 + 2v_2 + 3v+3)$,
   which is zero by supposition.
3. $v+w$ is in $V$. Write $v = (v_1, v_2, v_3)$ and $w=(w_1, w_2,
   w_3)$ so that $v+w= (v_1+w_1, v_2+w_2, v_3+w_3)$. Thus $(v_1+w_1) +
   2(v_2+w_2) + 3(v_3+w_3) = (v_1+2v_2+3v_3)+(w_1+2w_2+3w_3) = 0$.

#### (b) $`\{(x_1, x_2, x_3)\in \mathbf{F}^3 \mid x_1 +2 x_2 +3 x_3 =4\}`$

This set is not a subspace.

In particular, the zero vector is not an element since $x_1+2x_2+3x_3
\neq 4$ when $(x_1, x_2, x_3) = (0,0,0)$

#### (c) $`\{(x_1, x_2, x_3)\in \mathbf{F}^3 \mid x_1 x_2 x_3 = 0\}`$

This set is not a subspace.

For example, both $(1,1,0)$ and $(1,0,1)$ are elements (since the
product of their components is zero) but their sum, $(2,1,1)$ is not
an element (since the product of its components is not zero).

#### (d) $`\{(x_1, x_2, x_3)\in \mathbf{F}^3 \mid x_1  = 5 x_3\}`$

This set is a subspace.

1. The zero vector is an element, since $0=5\times 0$.
2. Scalar multiples of elements are elements, since $x_1=5x_3$ implies
   that $(\alpha x_1) = 5 (\alpha x_3)$.
3. Sums of elements are elements, since $v_1=5v_3$ and $w_1=5w_3$
   implies that $(v_1+w_1) = 5(v_3+w_3)$.

## Question 2

Verify all assertions about subspaces in Example 1.35.

(e) The set of all sequences of complex numbers with limit 0 is a
subspace of $\mathbf{C}^\infty$.

### Answer

Let's do this problem for the reals first, then see whether the
corresponding claim for the complex numbers follows.

$\mathbf{R}^\infty$ is the space of all infinite sequences of complex
numbers. A general element of $\mathbf{R}^\infty$ is $(x_1, x_2, x_3,
\dots)$. Some of those sequences have a _limit_, and some of the
sequences have a limit that is 0. For example, the sequence $(1,
\frac{1}{2}, \frac{1}{3}, \frac{1}{4}, \dots)$ has a limit which is 0;
the sequence $(1,1,1,\dots)$ has a limit which is 1; and the sequence
$(1,2,3,\dots)$ does not have a limit.

In general, a sequence has a limit of 0 if "the sequence eventually
gets as close as you like to zero and stays there." More formally, the
sequence has a limit of 0 if, for any $\epsilon>0$, there is some $N$
such that $\lvert x_n \rvert < \epsilon$ for all $n>N$.

For example, this condition is true of the sequence $(1, \frac{1}{2},
\frac{1}{3}, \dots, \frac{1}{n}, \dots)$. Given any $\epsilon>0$,
chose some $N > 1/\epsilon$. Then for any $n>N$, we have $\frac{1}{n}
< \frac{1}{N} < \epsilon$.

If $(x_1, x_2, \dots)$ is sequence with limit 0, we write
$$\lim_{n\to\infty} x_n = 0.$$

Is the set of these sequences a vector subspace of
$\mathbf{R}^\infty$? We must check the same three conditions.

1. The zero vector is certainly in this set. The sequence
   $(0,0,0,\dotsc)$ has a limit of 0.
2. Scalar products are in the set. Suppose $$\lim_{n\to\infty} x_n =
   0.$$ It follows that $\lim_{n\to\infty} (\alpha x_n) = 0.$ Proof:
   Given $\epsilon>0$, choose $N$ such that $\lvert x_n \rvert <
   \epsilon/\lvert \alpha \rvert$ for all $n>N$. (Such an $N$ must
   exist since since the $x_n$ converge to zero, by assumption). Then
   $\lvert \alpha x_n \rvert = \lvert \alpha \rvert \lvert x_n\rvert <
   \epsilon$ for all $n>N$.
3. Sums are in the set. Suppose $$\lim_{n\to\infty} \lvert x_n \rvert
   = 0\quad\text{and}\quad \lim_{n\to\infty} \vert y_n \rvert =0,$$
   then it follows that $$\lim_{n\to\infty} (x_n+y_n) = 0.$$ Proof:
   for $\epsilon>0$ choose $n$ such that $\lvert x_n \rvert <
   \epsilon/2$ and $\lvert y_n \rvert < \epsilon/2$ for $n>N$. (Such
   an $N$ will exist for each sequence separately; choose the larger.)
   Then $$\lvert x_n + y_n \rvert \leq \lvert x_n \rvert + \lvert y_n
   \rvert \leq \epsilon/2 + \epsilon /2  = \epsilon$$. (You should
   convince yourself that $\lvert a + b\rvert \leq \lvert a\rvert +
   \lvert b\rvert$ for any $a,b\in\mathbf{R}$.

Thus the set of all real-valued sequences with limit zero is a
subspace of the space of all sequences.

To see that this is true of the complex numbers,  note that every
assertion remains true if the “absolute value,” $\lvert x \rvert$, is
replaced with the definition appropriate for complex numbers: $\lvert
z \rvert = \sqrt{(\Re z)^2 + (\Im z)^2}$.

## Question 7

Prove or give a counter-example: If $U$ is a non-empty subset of
$\mathbf{R}^2$ such that $U$ is closed under addition and taking
additive inverses, then $U$ is a subspace of $\mathbf{R}^2$.

### Answer

This statement is false. Consider the set $U$ consisting of all pairs
$(m,n)\in \mathbf{R}^2$ where both $m$ and $n$ are integers. Since the
integers are closed under addition and taking additive inverses, the
conditions are satisfied; but this is not a subspace since, for
example, multiplication by $0.5$ gives elements not in $U$.

## Question 8

Give an example of a non-empty subset $U\subset \mathbf{R}^2$ which is
closed under scalar multiplication but not a subspace of
$\mathbf{R}^2$.

### Answer

The set
$$'\{(x,0)\in\mathbf{R}^2\mid x\in\mathbf{R}\} \cup \{(0,x)\in\mathbf{R}^2\mid x\in\mathbf{R}\}'$$
is an example. (It is
“points lying on the axes, but not otherwise.”)

## Question 10

Suppose $V_1$ and $V_2$ are subspaces of $V$. Prove that $V_1\cap V_2$
is also a subspace.

## Answer

We must check the usual three conditions.

1. Zero is in both $V_1$ and $V_2$ so is certainly in their
   intersection.
2. For $\alpha\in\mathbf{R}$ (or $\mathbf{C}$) and $v\in V_1\cap V_2$
   note that $\alpha v\in V_1$ and $\alpha v\in V_2$ and so $\alpha v$
   is in their intersection.
3. For $u, v$ in both $V_1$ and $V_2$, note that $u+v$ is in both
   $V_1$ and $V_2$ (since they are both subspaces) and hence in their
   intersection.
