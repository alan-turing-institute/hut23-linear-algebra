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

Well, if $w\in U_\lambda$ for some $\lambda$, then $Tw\in U_\lambda$
for the same $\lambda$. And so if $w$ is in every $U_\lambda$ then
$Tw$ is also in every $U_\lambda$, and hence in all the $U_\lambda$;
and hence in their intersection. In other words, $w\in
\bigcup_{\lambda\in\Lambda} U_\lambda$ implies $Tw\in
\bigcup_{\lambda\in\Lambda} U_\lambda$, and thus
$\bigcup_{\lambda\in\Lambda} U_\lambda$ is invariant under $T$.


## Question 8

Suppose $P\in\mathcal{L}(V)$ is such that $P^2=P$. Prove that if
$\lambda$ is an eigenvalue of $P$, then $\lambda = 0$ or $\lambda =
1$.

### Answer

If $\lambda$ is an eigenvalue of $P$, then that means that there is
some $v$ such that $Pv=\lambda v$. Now, in general, $P^2(v) =
P(P(v))= P(\lambda v) = \lambda P(v) = \lambda^2 v$, so that
$\lambda^2$ is an eigenvalue of $P^2$ with the same eigenvector. 

But the question says $P^2 = P$. So, for the common eigenvector $v$,
$\lambda^2 v = \lambda v$. Thus either $v=0$ (which isn't allowed for
an eigenvector) or $\lambda^2=\lambda$. And the only solutions of that
are $\lambda=0$ or $\lambda=1$. 


## Question 13

Suppose $T\in \mathcal{L}(V)$. Suppose $S\in\mathcal{V}$ is invertible.

### (a) 

Prove that $T$ and $S^{-1}TS$ have the same eigenvalues.

#### Answer

Suppose that $\lambda$ is an eigenvalue of $T$. That means that
$(T-\lambda I)v=0$ for some $v\neq 0$. Now consider applying
$S^{-1}(T-\lambda I)S$ to the vector $S^{-1}v$ (noting that $S$ is
invertible). We have
```math
\bigl(S^{-1}(T-\lambda I) \bigr) S^{-1}(v) = S^{-1}(T-\lambda I) v = 0.
```
On the other hand, we also have 
```math
\bigl(S^{-1}(T-\lambda I) \bigr) S^{-1}(v) = (S^{-1}TS-\lambda I) (S^{-1}v),
```
where, on the the right hand side, we have used $S^{-1}IS = I$. 

Thus $(S^{-1}TS-\lambda I) (S^{-1}v) = 0$ and so $\lambda$ is also an
eigenvalue of $S^{-1}TS$.


### (b)

What is the relationship between the eigenvectors of $T$ and the
eigenvectors of $S^{-1}TS$?

#### Answer

From the above, we have that, if $v$ is an eigenvector of $T$, then
$S^{-1}v$ is an eigenvector of $S^{-1}TS$. 


## Question 35

Suppose that $\lambda_1, \dotsc, \lambda_n$ is a list of distinct real
numbers. Prove that the list $e^{\lambda_1 x}, \dotsc, e^{\lambda_n
x}$ is linearly independent in the vector space of real-valued
functions on $\mathbf{R}$. 

Hint: Let $V=\text{span}(e^{\lambda_1 x}, \dotsc, e^{\lambda_n x})$,
and define an operator $D\in\mathcal{L}(V)$ by $Df=f'$. Find
eigenvalues and eigenvectors of $D$. 

### Answer

Let's follow the hint. Note that $D e^{\lambda_i x} = \lambda_i
e^{\lambda_i x}$. Thus, $\lambda_i$ is an eigenvalue of $D$ on the
space $V$. But the $\lambda_i$ are distinct. So there are at least $n$
distinct eigenvalues. So the dimension of $V$ is at least $n$. But the
dimension of $V$ is at most $n$ by construction. Thus $\text{dim
}V=n$. Since the $e^{\lambda_i x}$ span $V$, and there are $n$ of
them, they must be linearly independent. 

