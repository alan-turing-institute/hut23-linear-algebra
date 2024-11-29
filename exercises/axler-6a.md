# Questions from Axler 6a

1,3,13

## Question 1

Prove or give a counterexample: If $v_1, \dotsc, v_m \in V$, then
```math
\sum_{j=1}^m \sum_{k=1}^m \langle v_j, v_k \rangle \geq 0.
```

### Answer

How might we show that something to do with inner products is
non-negative? One thing we know (because of the definition of the
inner product) is that $\langle v,v\rangle \geq 0$ for any $v\in V$.

Write $v = v_1+\dotsb + v_m$. Then note that
```math
\lange v,v\rangle = \langle\sum_{j=1} v_j, \sum_{k=1}^m v_k\rangle
= \sum_{j=1}^m \sum_{k=1}^m \langle v_j, v_k \rangle.
```
The first term on the right is the definition of $v$, the second term
follows by additivity of the inner product. But the left-hand side is
non-negative, and therefore so too is the right.

## Question 3

(a) Show that the function taking an ordered pair $((x_1, x_2), (y_1,
y_2))$ of elements of $\mathbf{R}^2$ to $|x_1y_1| + |x_2|y_2$ is not an inner
product on $\mathbf{R}^2$.

(b) Show that the function taking an ordered pair $((x_1, x_2, x_3),
(y_1, y_2, y_3))$ of elements of $\mathbf{R}^3$ to $x_1y_1+x_3y_3$ is not an
inner product on $\mathbf{R}^3$.



## Question 13

Show that the square of an average is less than or equal to the
average of the squares. More precisely, show that if $a_1, \dotsc,
a_n\in\mathbf{R}$, then the square of the average of $a_1, \dotsc,
a_n$ is less than or equal to the average of $a_1^2, \dotsc, a_n^2$.
