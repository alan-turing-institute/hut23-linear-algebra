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
basis $1, x, \dots, x_m$ of $\mathcal{𝒫}_m(\mathbf{R})) is $\phi_0,
\phi_1, \dots, \phi_m$, where $\phi_k(p) = 𝑝^{(𝑘)}(0)/k!$. 

Here $𝑝^{(𝑘)}$ denotes the $k$th derivative of $p$, with the
understanding that the 0th derivative of $p$ is $p$.

### Answer

