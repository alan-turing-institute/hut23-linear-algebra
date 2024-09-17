# Exercises from Axler 3.F

2, 9, 32

## Question 2

Give three distinct examples of linear functionals on $\mathbf{R}^{[0,
1]}$.

### Answer

One example of a linear functional on $\mathbf{R}^{[0, 1]}$ is the map
that assigns, to each $f \in \mathbf{R}^{[0, 1]}$, the number
$f(0)$. That is, it evaluates $f$ at zero. This map is linear since
$(f + g)(0) = f(0) + g(0)$, by the definition of addition of
functions.  More generally, for any $x\in [0,1]$, the map $E_x\colon
f \mapsto f(x)$ is a linear functional.

There are other linear functionals if we modify the space
slightly. Instead of considering all functions, we might choose the
space of all differentiable functions. Then the map which, given a
function, returns the value of the derivative of the function
evaluated at $x = 0.5$ (say) is also a linear functional. Or, we might
choose the space of all integrable functions. Then the map $f
\mapsto\int_0^1 f(x) dx$ is also a linear functional.

## Question 9

Suppose $m$ is a positive integer. Show that the dual basis of the
basis $1, x, \dots, x^m$ of $\mathcal{𝒫}_m(\mathbf{R})) is $\phi_0,
\phi_1, \dots, \phi_m$, where $\phi_k(p) = 𝑝^{(𝑘)}(0)/k!$.

Here $𝑝^{(𝑘)}$ denotes the $k$th derivative of $p$, with the
understanding that the 0th derivative of $p$ is $p$.

### Answer

(What are the $\phi_k(p)$? They are the coefficiencts of the Taylor
series expansion of $p$.)

First note that $\phi_k$ is a linear map. We must show that
$\phi_k(x^m) =\delta_{km}$.

Consider $\frac{d^k}{dx^k} (x^n)\mid_0$. If $n< k$ then the $`k`$th
derivative of $x^n$ is identically zero. On the other hand, if $n > k$
then the $`k`$th derivative of $x^n$ is $n
(n-1)(n-2)\dots(n-k+1)x^{n-k}$, which is zero when evaluated at
$x=0$. Finally, when $n=k$, the $`k`$th derivative of $x^n$ is the
constant $n (n-1)(n-2)\dots 1=n!=k!$. In summary

$$
\left.\frac{d^k}{dx^k}\right|_{x=0} x^n =
\begin{cases}
k! & \text{when } n = k \\
0  & \text{otherwise},
\end{cases}
$$

from which the duality follows.

## Question 32

The _double dual space_ of $V$, denoted by $V''$, is defined to be the
dual space of $V'$. In other words, $V''=(V')'$. Define $\Lambda\colon
V\to V''$ by $(\Lambda v)(\phi) =\phi(v)$ for each $v\in V$ and each
$\phi\in V'$.

### (a)

Show that $\Lambda$ is a linear map from $V$ to $V''$.

### Answer

We must show that $\Lambda (u+\alpha v) = \Lambda u +\alpha\Lambda
v$. The action of $\Lambda (u+\alpha v)$ on an arbitrary $\phi$ is

$$
(\Lambda (u+\alpha v))(\phi) = \phi(u+\alpha v) = \phi(u)+\alpha\phi(v),
$$

by linearity of $\phi$. But this is precisely $(\Lambda u)(\phi) +
\alpha(\Lambda v)(\phi)$.

### (b)

Show that if $T\in\mathcal{L}(V)$, then $T''\circ \Lambda =
\Lambda\circ T$, where $T''=(T')'$.

### Answer

For any $v\in V$, $(T''\circ\Lambda)(v)$ is an element of $V''$.  For
any $\phi\in V'$, we have

$$
\begin{aligned}
\bigl((T''\circ\Lambda)(v)\bigr)(\phi)
&= \bigl(T''(\Lambda(v))\bigr(\phi) & \\
&= \Lambda(v)(T'(\phi))  & \text{by definition of }T' \\
&= (T'(\phi))(v)         & \text{by definition of }\Lambda \\
&= \phi(T(v))            & \text{by definition of }T' \\
&= (\Lambda(T(v)))(\phi) & \text{by definition of }\Lambda.
\end{aligned}
$$

Thus $\bigl(T''(\Lambda(v))\bigr(\phi) = (\Lambda(T(v)))(\phi)$ for
all $\phi$; hence $T''(\Lambda(v)) = (\Lambda(T(v)))$.

### (c)

Show that if $V$ is finite-dimensional, then $\Lambda$ is an
isomorphism from $V$ onto $V''$.

### Answer

Since $V$ is finite-dimensional, $\text{dim }V'' = \text{dim }V' =
\text{dim V}$. So it suffices to show that $\Lambda$ is injective.

Let $v\in V$ be such that $\Lambda(v)=0$. Then, for all $\phi\in V'$,
we have $(\Lambda(v))(\phi) = 0 = \phi(v)$. But the annihilator of
$V'$ (in $V$) is just $0\in V$, so we have $v = 0$. Thus, $\Lambda$ is
injective, hence an isomorphism.
