# Exercises from Axler 1.A

## Q.1
### Question
Prove that $-(-v) = v$ for every $v\in V$.

### Solution

It’s worth stating what we are being asked to prove! “$-v$” denotes
“the additive inverse of $v$” (that's notation 1.27 in Axler). That
is, given some vector $v$, the vector $-v$ is that vector such that
$v + (-v) = \mathbf{0}$. (1.26 shows that there is only one such
vector.)

So $-(-v)$ means “the additive inverse of $-v$.” In other words,
$-(-v)$ is that vector which, when added to $-v$, gives
$\mathbf{0}$. The vector which gives $\mathbf{0}$ when added to $-v$
is clearly $v$, by the very definition of $-v$ above. And there is
only one additive inverse, so we have found it: $-(-v) = v$. 

## Q.2
### Question
Suppose $a \in \mathbf{F}$, $\mathbf{v} \in V$, and $a\mathbf{v} =
\mathbf{0}$. Prove that $a = 0$ or $\mathbf{v} = \mathbf{0}$.

(I'm writing vectors in bold just to distinguish them from numbers.)

### Solution

It’s true that $0v = \mathbf{0}$ for any $v$ (Axler 1.29). And it’s
true that $a\mathbf{0} = \mathbf{0}$ for any number $a$ (Axler
1.30). This question asks us to show that those are the _only_ ways in
which the product can be the zero vector: that you can never get a
zero vector by multiplying a non-zero number with a non-zero vector.

If $a=0$ then we're done. So suppose $a\neq 0$; we would like to show
$\mathbf{v}= \mathbf{0}$. How can we get to $\mathbf{v} = \mathbf{0}$
from $a\mathbf{v} = \mathbf{0}$? Well, if these were just numbers,
we’d “divide both sides by $a$.” Okay, let’s do that! Or rather, let’s
multiply both sides by $1/a$ (which exists, since $a\neq 0$)

$$\frac{1}{a} (a\mathbf{v}) = \frac{1}{a}\mathbf{0}.$$ 

The right-hand side is $\mathbf{0}$ (by Axler 1.30). The left hand
side clearly ought to be $\mathbf{v}$---and it is, because
$(1/a)(a\mathbf{v}) = (a/a)\mathbf{v}$ by distributivity.

So we have shown that if $a\neq 0$ then $\mathbf{v}=0$. 


## Q.3
### Question
Suppose $v, w \in V$. Explain why there exists a unique $x \in V$ such that
$v+3x＝w$.

### Solution

## Q.4
### Question
The empty set is not a vector space. The empty set fails to satisfy
only one of the requirements listed in Axler 1.19. Which one?

### Solution

## Q.5
### Question
Show that in the definition of a vector space (Axler 1.19), the
additive inverse condition can be replaced with the condition that 
```math
0v = \mathbf{0} \quad\text{for all $v \in V$}.
```

### Solution

## Q.6
### Question
Let $\infty$ and $-\infty$ denote two distinct objects, neither of which
is in $\mathbf{R}$. Define an addition and scalar multiplication on
$\mathbf{R} \cup \{\infty\} \cup \{-\infty\}$ as you could guess from the
notation. Specifically, the sum and product of two real numbers is as
usual, and for $t\in\mathbf{R}$ define 

$$t\infty = 
\begin{cases}
	-\infty & \text{if $t<0}, \\
	0       & \text{if $t=0$}, \\
	\infty  & \text{if $t>0$},
\end{cases}$$
and
$$t(-\infty) = 
\begin{cases}
	\infty  & \text{if $t<0}, \\
	0       & \text{if $t=0$}, \\
	0\infty & \text{if $t>0$},$$ 
	
along with $t+\infty = \infty+t = \infty$, $t+(-\infty) = (-\infty)+t = -\infty$,
$\infty+\infty=\infty$, $(-\infty)+(-\infty)=-\infty$, and $\infty+(-\infty)=0$.

Is $\mathbf{R}\cup\{\infty\}\cup\{-\infty\}$ a vector space over $\mathbf{R}$?

### Solution


