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
functions.  More generally, for any $x\ in [0,1]$, the map $E_x\colon
f \mapsto f(x)$ is a linear functional.

There are other linear functionals if we modify the space
slightly. Instead of considering all functions, we might choose the
space of all differentiable functions. Then the map which, given a
function, returns the value of the derivative of the function
evaluated at $x = 0.5$ (say) is also a linear functional. Or, we might
choose the space of all integrable functions. Then the map $f
\mapsto\int_0^1 f(x)\,dx$ is also a linear functional.

### Question 9


### Answer

First note that $\phi_k$ is a linear map. Next, consider
$\frac{d^k}{dx^k} (x^n)\mid_0$. If $n< k$ then the $`k`$th derivative of $x^n$ is
identically zero. On the other hand, if $n > k$ then the $`k`$th
derivative of $x^n$ is $n (n-1)(n-2)\dots(n-k+1)x^{n-k}$, which is
zero when evaluated at $x=0$. Finally, when $n=k$, the $`k`$th
derivative of $x^n$ is the constant $n (n-1)(n-2)\dots 1=n!=k!$. In
summary
\begin{equation}
\phi_k(x^n) = 
\begin{cases}
k! & \text{when } n = k \\
0  & \text{otherwise},
\end{cases}
\end{equation}
from which the duality follows.
