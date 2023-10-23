# Exercises from Axler 1.A

## Q.1
### Question
Prove that $-(-v) = v$ for every $v\in V$.

### Solution

It’s worth stating what we are being asked to prove! $-v$ denotes
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
side clearly ought to be $\mathbf{v}$—and it is, because
$(1/a)(a\mathbf{v}) = (a/a)\mathbf{v} = 1\mathbf{v} = \mathbf{v}$.

So we have shown that if $a\neq 0$ then $\mathbf{v}=0$. 


## Q.3
### Question
Suppose $v, w \in V$. Explain why there exists a unique $x \in V$ such that
$v+3x＝w$.

### Solution

Suppose $\alpha$ is a non-zero number. I claim that the map $V\to V$
given by multiplication by $\alpha$, that is $v\mapsto \alpha v$, is a
bijection. Proof: It is surjective, since, for any $v'\in V$, the
vector $(1/\alpha)v'$ is mapped to $v'$. It is injective since, if
there were $v'$ with $\alpha v = \alpha v'$, we would have
$\alpha(v-v')=0$ (this requires some use of the properties of vectors,
together with 1.31), and thus, by Q.2, $v-v'=0$, hence $v=v'$.

Likewise, for $w\in V$ any vector, the map $V\to V$ given by addition
of $w$, that is $v\mapsto w+v$, is also a bijection. (Proof is
similar, noting that additive inverses exist and are unique.)

Thus the combination, “multiply by a number and add a vector“ is a
bijection. Thus, there _is_ an $x$ satisfying the given equation, and
it is unique. 

## Q.4
### Question
The empty set is not a vector space. The empty set fails to satisfy
only one of the requirements listed in Axler 1.19. Which one?

### Solution

The requirement that there exist an additive identity is not
satisifed. There are no elements at all; _a fortiori_ there is no
element $\mathbf{0}$ with the required properties.

## Q.5
### Question
Show that in the definition of a vector space (Axler 1.19), the
additive inverse condition can be replaced with the condition that 
```math
0v = \mathbf{0} \quad\text{for all $v \in V$}.
```

### Solution

That this follows from 1.19 is theorem 1.29. It remains to be shown
that, from the above condition, and all conditions in the definition
of a vector space _except_ that of the additive inverse, the existence
of additive inverses follows.

Indeed, for any $v\in V$, consider the expression $v + (-1)v$. 
```math
\begin{align}
v + (-1)v 
 &= 1v+(-1)v &&\text{(condition of “multiplicative  identity”)} \\ 
 &= (1-1)v &&\text{(by distributivity)} \\
 &= 0v \\
 &=0 &&\text{(by supposition)}.
\end{align}
```

Therefore, $(-1)v$ is an additive inverse of $v$. 

## Q.6
### Question
Let $\infty$ and $-\infty$ denote two distinct objects, neither of which
is in $\mathbf{R}$. Define an addition and scalar multiplication on
$`\mathbf{R} \cup \{\infty\} \cup \{-\infty\}`$ as you could guess from the
notation. Specifically, the sum and product of two real numbers is as
usual, and for $t\in\mathbf{R}$ define 
```math
t\infty = 
\begin{cases}
	-\infty & \text{if $t<0$}, \\
	0       & \text{if $t=0$}, \\
	\infty  & \text{if $t>0$},
\end{cases}
```

and
```math
t(-\infty) = 
\begin{cases}
	\infty  & \text{if $t<0$}, \\
	0       & \text{if $t=0$}, \\
	-\infty & \text{if $t>0$},
\end{cases}
```
along with $t+\infty = \infty+t = \infty$, $t+(-\infty) = (-\infty)+t = -\infty$,
$\infty+\infty=\infty$, $(-\infty)+(-\infty)=-\infty$, and $\infty+(-\infty)=0$.

Is $`\mathbf{R} \cup \{\infty\}\cup \{-\infty\}`$ a vector space over $\mathbf{R}$?

### Solution

Sometimes people don't like the fact that division is not defined
everywhere—you “can't divide by zero”—and try to fix the problem by
including infinity as a sort of number. This is one such attempt.

The usual place to look from problems is in terms that would normally
count as undefined: things like “infinity minus infinity.”

What, for example, would be the result of $\infty+\infty+(-\infty)$?
We might read this as $(\infty+\infty)+(-\infty) = \infty +(-\infty) =
0$. Or we might read it as $\infty+(\infty+(-\infty)) = \infty+0 =
\infty$. Addition in a vector space is supposed to be associative; but
in this space the operation of $+$ is not associative. So we do not
have a vector space.
