# Meetup 13 October 2023

## Recap

Definition 1.10 of $\mathbf{R}^n$ (or $\mathbf{C}^n$): An element of
$\mathbf{R}^n$ is a tuple of numbers, $(x_1, x_2, \dotsc, x_n)$. 

Definition 1.12 of addition in $\mathbf{R}^n$ (or
$\mathbf{C}^n$): “Add together corresponding components.”
$$(x_1, x_2, \dotsc, x_n) + (y_1, y_2, \dotsc, y_n) =
(x_1+y_1, x_2+y_2, \dotsc, x_n+y_n).$$

Definition 1.17 of scalar multiplication in $\mathbf{R}^n$ (or
$\mathbf{C}^n$). For $\lambda\in \mathbf{R}$ (or $\mathbf{C}$):
$$\lambda (x_1, x_2, \dotsc, x_n) = (\lambda x_1, \lambda x_2, \dotsc,
\lambda x_n).$$

## Questions from Axler 1.A

### Q.10. 

#### Question
Find $x \in \mathbf{R}^4$ such that $$(4, -3, 1, 7) + 2x = (5, 9, -6, 8).$$

#### Solution
Write $x = (x_1, x_2, x_3, x_4)$. Finding $x$ means finding $x_1,
\dotsc, x_4$.

From the definition of addition in $\mathbf{R}^n$, $(4, -3, 1, 7) + 2x = 
(4+2x_1, -3+2x_2, 1+2x_3, 7+2x_4)$. Therefore,
$$(4+2x_1, -3+2x_2, 1+2x_3, 7+2x_4) = (5, 9, -6, 8).$$

Equating the first component of the tuples gives $4+2x_1 = 5$, and
therefore $x_1 = 1/2$. Similarly, the second, third, and fourth
components give $x_2 = 6$, $x_3 = -7/2$, and $x_4=1/2$ respectively.

----

There is another way to approach this problem, one which is perhaps
more “natural” for “things that live in $\mathbf{R}^4$”:

Start with $$(4, -3, 1, 7) + 2x = (5, 9, -6, 8).$$ 
Now subtract $(4, -3, 1, 7)$ from both sides. (The meaning of “subtract
$X$” is “add $-X$.”). Thus: 
$$2x = (1, 12, -7, 1).$$ 
Finally, divide both sides by 2. (The maning of “divide by $\lambda$”
is “multiply by $1/\lambda$”). Thus:
$$x = (1/2, 6, -7/2, 1/2).$$ 


### Q.11

#### Question

Explain why there does not exist a $\lambda \in \mathbf{C}$ such
that $$\lambda (2 - 3i, 5 + 4i, -6 + 7i) = (12 - 5i, 7 + 22i, -32 - 9i).$$

#### Solution

For this equation to be true, each component on the right must be the
same multiple, $\lambda$, of the corresponding component on the
left. (This follows from the definition of scalar multiplication in
$\mathbf{R}^3$.) In general this will not be true. 

Equating the first components gives $\lambda (2 - 3i) = 12 -5i$
and therefore $\lambda = \frac{12-5i}{2-3i}$.

There's a standard trick to dividing one complex number by another
(which question 1 gets you to do explicitly). That is to multiply both
the numerator and denominator by a carefully chosen complex number so
that the result in the denominator is purely real. In this case:
$$\frac{12-5i}{2-3i} = \frac{12-5i}{2-3i}\times \frac{2+3i}{2+3i} =
\frac{(12-5i)(2+3i)}{(2-3i)(2+3i)} = \frac{39 + 26i}{13} = 3 + 2i.$$
(The number that you multiply top and bottom by is always the same as
the denominator but with the sign of the imaginary part reversed.)

The same calculation for all the components is:
$$\frac{12-5i}{2-3i} = 3 + 2i, \quad
\frac{7+22i}{5+4i} = 3 + 2i, \quad\text{and}\quad
\frac{-32-9i}{-6+7i} = (129 + 278i) / 85.$$

Since those are not all the same number, no single $\lambda$ works for
all components, and so the original equation cannot be satisfied.


### Q.14

#### Question
Show that $1x = x$ for all $x\in \mathbf{F}^n$.

#### Solution
$x$ is a tuple of numbers, $(x_1, x_2, \dotsc, x_n)$. From the definition
of scalar multiplication:
$$1 (x_1, x_2, \dotsc, x_n) = (1 x_1, 1 x_2, \dotsc, 1 x_n) = (x_1, x_2, \dotsc, x_n).$$


### Q.16

#### Question
Show that $(a+b)x = ax + bx$ for all $a,b \in \mathbf{F}$ and all 
$x \in \mathbf{F}^n$.

#### Solution
$x$ is a tuple of numbers, $(x_1, x_2, \dotsc, x_n)$. From the definition
of scalar multiplication:
```math
\begin{align}
(a+b) (x_1, x_2, \dotsc, x_n) 
&= ((a+b) x_1, (a+b) x_2, \dotsc, (a + b) x_n) \\
&= (a x_1 + b x_1, a x_2 + b x_2, \dotsc, a x_n + b x_n) \\
&= (a x_1, a x_2, \dotsc, a x_n) + (b x_1, b x_2, \dotsc, b x_n) \\
&= a (x_1, x_2, \dotsc, x_n) + b (x_1, x_2, \dotsc, x_n).
\end{align}
```