# Exercises from Axler 1.C

## Q.1
### Question
For each of the following subsets of $\mathbf{F}^3$, determine whether
it is a subspace of $\mathbf{F}^3$.  

#### a.

$$\{(𝑥_1, 𝑥_2, 𝑥_3)\in $\mathbf{F}^3 \mid 𝑥_1 +2 𝑥_2 +3 𝑥_3 =0\}$$ 



#### b.

{(𝑥1,𝑥2,𝑥3)∈𝐅3 ∶𝑥1 +2𝑥2 +3𝑥3 =4} 

#### c.

{(𝑥1,𝑥2,𝑥3)∈𝐅3 ∶𝑥1𝑥2𝑥3 =0} 

#### d. 

{(𝑥1,𝑥2,𝑥3) ∈ 𝐅3 ∶ 𝑥1 = 5𝑥3}

* Temp

For each given subset, $V$, we must check that, for all
$\alpha\in\mathbf{F}$, and $v,w\in V$:
1. $\mathbf{0}\in V$;
2. $\alpha v \in V$; and
3. $v+w \in V$.

(a) This set is a subspace.

1. $\mathbf{0}$ is in $V$ since $\mathbf{0}=(0,0,0)$ and $0+2\times
   0+3\times =0$, as required;
2. $\alpha v$ is in $V$ since for $v=(v_1, v_2, v_3)$, we have $\alpha
   v = (\alpha v_1, \alpha v_2, \alpha v_3)$ and so $(\alpha v_1) +
   2(\alpha v_3) + 3(\alpha v_3) = \alpha (v_1 + 2v_2 + 3v+3)$. The
   second term is zero by supposition.
3. $v+w$ is in $v$. Write $v = (v_1, v_2, v_3)$ and $w=(w_1, w_2,
   w_3)$ so that $v+w= (v_1+w_1, v_2+w_2, v_3+w_3)$. Thus $(v_1+w_1) +
   2(v_2+w_2) + 3(v_3+w_3) = (v_1+2v_2+3v_3)+(w_1+2w_2+3w_3) = 0$.

(b) This set is not a subspace. In particular, the zero vector is not
an element since $x_1+2x_2+3x_3 \neq 4$ when $(x_1, x_2, x_3) =
(0,0,0)$

(c) This set is not a subspace. For example, both $(1,1,0)$ and
$(1,0,1)$ are elements (since the product of their components is zero)
but their sum, $(2,1,1)$ is not an element (since the product of its
components is not zero).

(d) This set is a subspace.

1. The zero vector is an element, since $0=5\times 0$.
2. Scalar multiples of elements are elements, since $x_1=5x_3$ implies
   that $(\alpha x_1) = 5 (\alpha x_3)$.
3. Sums of elements are elements, since $v_1=5v_3$ and $w_1=5w_3$
   implies that $(v_1+w_1) = 5(v_3+w_3)$.
   
2. (e)

Let's do this problem for the reals first, then see whether the
corresponding claim for the complex numbers follows.

$\mathbf{R}^\infty$ is the space of all infinite sequences of complex
numbers. For example, $(x_1, x_2, x_3, \dots)$. Some of those
sequences have a _limit_, and that limit is 0. For example, the
sequence $(1, \frac{1}{2}, \frac{1}{3}, \frac{1}{4}, \dots)$ has a limit
which is 0; the sequence $(1,1,1,\dots)$ has a limit which is 1; and
the sequence $(1,2,3,\dots)$ does not have a limit.

In general, a sequence has a limit of 0 if "the sequence eventually
gets as close as you like to zero and stays there." More formally, the
sequence has a limit of 0 if, for any $\epsilon>0$, there is some $N$
such that $\lvert x_n \rvert < \epsilon$ for all $n>N$.

For example, this condition is true of the sequence $(1, \frac{1}{2},
\frac{1}{3}, \dots, \frac{1}{n}, \dots)$. Given any $\epsilon>0$,
chose some $N > 1/\epsilon$. Then for any $n>N$, we have $\frac{1}{n}
< \frac{1}{N} < 1/\epsilon$.

If $x_1, x_2, \dots$ is sequence with limit 0, we write
$$\lim_{n\to\infty} x_n = 0.$$

Are the set of these sequences a vector subspace of
$\mathbf{R}^\infty$?

1. The zero vector is! The sequence $(0,0,0,\dotsc)$ has a limit of 0.
2. Suppose
