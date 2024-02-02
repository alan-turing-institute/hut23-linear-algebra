# Exercises from Axler 3.A

**Note:** My answers are a bit terse this week!


## Question 1

For $b,c\in\mathbf{R}$ and $T:\mathbf{R}^3 \to \mathbf{R}^2$ given by
$$
T(x,y,z) = (2x-4y+3z+b, 6x + cxyz),
$$
show that $T$ is linear iff $b = c = 0$.

### Answer

Suppose $T$ is linear. Then $T((0,0,0))=(b, 0)$ must be the zero vector
in $\mathbf{R}^2$, so $b = 0$. Then $T((1,1,1))=(1, 6+c)$ but $2T((1,1,1))
= T((2,2,2))$ (by linearity) $(2, 12+8c)$ so we must have $c=0$.

Conversely, suppose $b = c = 0$. Then by inspection $2x-4y+3z$ and
$6x$ are linear terms so $T$ is linear.

## Question 3

Suppose $T\in\mathcal{L}(\mathbf{F}^n,\mathbf{F}^m)$. Show that there
exist scalars $A_{j,k}$ such that
$$
T(x_1, \dotsc, x_n) = (\sum_k A_{1, k} x_k, \dotsc, \sum_k A_{m, k} x_k).
$$

### Answer

Define $A_{j, 1}$ by
$$
(A_{1, 1}, A_{2, 1}, \dotsc, \A_{m, 1}) = T((1, 0,\dotsc,0))
$$
and in general define $A_{j, k}$ by
$$
(A_{1, k}, A_{2, k}, \dotsc, \A_{m, k}) = T((0,\dotsc, 0,1,0, \dotsc,
0))
$$
(with the single 1 in the $k$th position).

Now observe that any $(x_1, \dotsc, x_n)$ can be written as a linear
sum of the terms on the right, with the coefficients being precisely
the $x_i$. Writing the same linear sum on the left (using linearity of
$T$) produces the required form.


## Question 4

Suppose $T\in\mathcal{V, W}$ and $v_1, \dotsc, v_n\in V$ is such that
$Tv_1, \dotsc, Tv_n$ is linearly independent in $W$. Prove that $v_i$
are linearly independent in $V$.

### Answer

Suppose $\alpha_1 v_1 + \alpha_2 v_2 \dotsb + alpha_n v_n = 0$ for
some $\alpha_i$. Then by linearity of $T$,
$$
\alpha_1 Tv_1 +\dotsb + \alpha_n Tv_n = 0$
$$
But the $Tv_i$ are linearly independent, and so we must have
$\alpha_i=0$ for all $\alpha_i$. Hence the $v_i$ are linearly
independent.

## Question 8

Give an example of a function $\phi:\mathbf{R}^2\to \mathbf{R}$ which
satisfies the property of homogeneity but is not linear.

### Answer

$$
\phi((x,y)) = 
\begin{cases}
(x,y) & \text{if } \left| x\right| > \left|y\right| \\
0     & \text{otherwise}.
\end{cases}
$$
Note that multiplication by 2 preserves the truth of $|x|>|y|$. 


## Question 9

Give an example of a function $\phi:\mathbf{C}\to\mathbf{C}$ which
satisfies the additive property but is not linear.

Consider
$$
\newcommand{\ii}{\mathrm{i}}
\phi(a+\ii b) = a.
$$
Then $\phi((a+\ii b) + (c+\ii d)) = a+c = \phi(a+ib)+\phi(c+id)$ so $\phi$
is additive.

But $i\phi(a+ib) = ai \neq \phi(i(a+ib)) = -b$.


