# Questions from Axler 5a

3,8,13,35

## Question 3

Suppose $T \in \mathcal{L}(V)$. Prove that the intersection of every
collection of subspaces of $V$ invariant under $T$ is invariant
under $T$.

### Answer

First, what is a "collection of subspaces"? A collection of subspaces
is:
  1. A set, $\Lambda$, whose elements will be used to "index" the collection;
  2. For each $\lambda\in\Lambda$, a subspace $U_\lambda$.

We say that $U_\lambda$ (where $\lambda\in \Lambda$) is a "family of
subspaces indexed by $\Lambda$".

(You might think that we could have written $U_1$, $U_2$, ... and so
on, using the natural numbers to index the $`U`$s. But the question
said /every/ collection, and some collections have "more things in
them than there are natural numbers.")

So, let $U_\lambda$ (where $\lambda\in\Lambda$) be some family of
subspaces such that each $U_\lambda$ is invariant under $T$. What that
means is that, for any $\lambda$ and for any $w\in U_\lambda$, we have
$Tw\in U_\lambda$.

The intersection of all the $U_\lambda$ is
```math
\bigcap_{\lambda\in\Lambda} U_\lambda = \{ u \mid u\in\U_\lambda 
\text{ for every }\lambda\}.
```



