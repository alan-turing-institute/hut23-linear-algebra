# Questions from Axler 5a

3,8,13,35

## Question 3

Suppose $T \in \mathcal{L}(V)$. Prove that the intersection of every
collection of subspaces of $V$ invariant under $T$ is invariant
under $T$.

### Answer

First, what is a "collection of subspaces"? A collection of subspaces
is:
  1. A set, $\Lambda$, whose elements will be used to “index” the collection;
  2. For each $\lambda\in\Lambda$, a subspace $U_\lambda$.

We say that $U_\lambda$ (where $\lambda\in \Lambda$) is a “family of
subspaces indexed by $\Lambda$”.

(You might think that we could have written $U_1$, $U_2$, ... and so
on, using the natural numbers to index the $`U`$s. But the question
said _every_ collection, and some collections have “more things in
them than there are natural numbers.”)

So, let $U_\lambda$ (where $\lambda\in\Lambda$) be some family of
subspaces such that each $U_\lambda$ is invariant under $T$. What that
means is that, for any $\lambda$ and for any $w\in U_\lambda$, we have
$Tw\in U_\lambda$.

The intersection of all the $U_\lambda$ is
```math
\bigcap_{\lambda\in\Lambda} U_\lambda \equiv \{ u \mid u\in U_\lambda 
\text{ for every }\lambda\}.
```

That is, for a vector $w$ to be in _all_ the subspaces means that it
is in _every_ subspace. 

Well, if $w\in U_\lambda$, then $Tw\in U_\lambda$. And so $Tw$ is also
in in every subspace, and hence in all the subspaces, and hence in
their intersection. In other words, $\bigcup_{\lambda\in\Lambda}
U_\lambda$ is invariant under $T$.


## Question 8

Suppose $P\in\mathcal{L}(V)$ is such that $P^2=P$. Prove that if
$\lambda$ is an eigenvalue of $P$, then $\lambda = 0$ or $\lambda =
1$.

### Answer

If $\lambda$ is an eigenvalue of $P$, then that means that there is
some $v$ such that $Pv=\lambda v$. Now, in general, $P^2(v)$ =
P(P(v))= P(\lambda v) = \lambda P(v) = \lambda^2 v$, so that
$\lambda^2$ is an eigenvalue of $P^2$ with the same eigenvector. 

But the question says $P^2 = P$. So, for the common eigenvector $v$,
$\lambda^2 v = \lambda v$. Thus either $v=0$ (which isn't allowed for
an eigenvector) or $\lambda^2=\lambda$. And the only solutions of that
are $\lambda=0$ or $\lambda=1$. 







