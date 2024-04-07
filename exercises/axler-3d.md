# Exercises from Axler 3.C

1, 2, 6, 9, 18, 21

## Question 1

Suppose $T\in\mathcal{L}(V, w)$ is invertible. Show that $T^{-1}$ is
invertible and $(T^{-1})^{-1} = T$.

### Answer

When asked to show that something has a certain property, it's often
best to go back to the definition of that property. A linear map
$R:V\to W$ is invertible (this is definition 3.59) if there exists an
$S:W\to V$ such that $RS$ is the identity on $W$ and $SR$ is the
identity on $V$.

So, in order to show that some linear map (say $T^{-1}$) is
invertible, we must exhibit another linear map with the required
properties.

The obvious candidate for an inverse of $T^{-1}$ is $T$. Let's check
whether it is. We need to check that $T^{-1}T$ is the identity on $V$
and that $TT^{-1}$ is the identity on $W$. And indeed they are --
because _those_ conditions are precisely the meaning of $T^{-1}$
(which we are assured exists by the question).

## Question 2

Suppose $T\in \mathcal{L}(U, V)$ and $S\in \mathcal{L}(V, W)$ are both
invertible. Prove that $ST$ is invertible and that $(ST)^{-1} =
T^{-1}S^{-1}$.

### Answer

To prove that something is invertible we must exhibit its
inverse. Fortunately, the question has told us what the inverse is, so
what we need to do is check that it does in fact satisfy the
conditions for being an inverse.

That is, we need to show: (1) that $\bigl(ST\bigr) \bigl(
T^{-1}S^{-1}\bigr)$ is the identity on $W$; and (2) that $\bigl(
T^{-1}S^{-1}\bigr) \bigl(ST\bigr)$ is the identity on $U$.

To show (1), note that composition of linear maps is associative --
that is, it doesn't matter where we put the parentheses. Thus, roughly
speaking, we can “cancel the inner $`T`$s” and then, having got rid of
those, “cancel the outer $`S`$s.”

More carefully, $\bigl(ST\bigr) \bigl( T^{-1}S^{-1}\bigr) = S(T
T^{-1})S^{-1}$ because composition is associative. And that is
$S\mathbf{1}_V S^{-1}$, which is $SS^{-1}$ which is
$\mathbf{1}_W$. The same argument works for (2).

## Question 6

Suppose that $W$ is finite-dimensional and $S, T\in\mathcal{L}(V,
W)$. Prove that $\text{null } S = \text{null } T$ if and only if there
exists an invertible $E\in\mathcal{L}(W)$ such that $S=ET$.

```mermaid
stateDiagram-v2
  direction LR
  state "V" as s1 
  state "W" as s2
  s1 --> s2 : S 
  s1 --> s2 : T
  s2 --> s2 : E
```

### Answer

The “if” direction is the most straighforward. First, if such an $E$
exists, then $\text{null }S \subset \text{null }T$. (To see this,
suppose $v\in\text{null }T$; that is, $T(v)=\mathbf{0}$. Since $S(v) =
E(T(v))$ we have $S(v)=\mathbf{0}$ and hence $v\in\text{null S}$.) Now
run the argument again, using $E^{-1}$ and conclude that $\text{null
}T\subset\text{null }S$. Putting those together implies $\text{null
}S=\text{null }T$.

The other direction is not so easy!

What is this question saying? It is sort of saying two things. The
first is something like, “if the null spaces of $S$ and $T$ are equal,
then their ranges are isomorphic.” That's kind of interesting, because
the null spaces live in the domain of $S$ and $T$, whereas the ranges
live in the codomain.

The second thing the question is saying is, “the ismorphism between
the ranges of $S$ and $T$ can be extended to an isomporphism on the
whole of $W$.” That is, “the bit of $W$ that isn't the range of $S$ is
also isomorphic to the bit of $W$ that isn't the range of $T$.” This
part is less interesting because it's nothing to do with maps like $S$
and $T$ (at least, I don't think so).

So, let's try to show that the range of $T$ is isomporphic to the
range of $S$. That is, we will show

```math
\text{null }S = \text{null }T \implies \text{range }S \cong
\text{range }T.
```

To do so, we will construct a linear map, $\tilde{E}\colon \text{range
}T\to\text{range }S$, that is both injective and surjective (and thus
invertible).





Suppose $\text{null } S = \text{null } T$. We'll try to construct the
required $E$. (That will show the “only if” part.)

```mermaid
stateDiagram-v2
  direction LR
  state "W" as s1 
  state "W" as s2
  V --> s1 : S 
  V --> s2 : T
  s2 --> s1 : E
```

What _is_ $E$? The diagram above isn't great but maybe gives some
idea. Starting from $V$, one can get to $W$ by using either $S$ or
$T$. (Note that the diagram “duplicates” $W$ -- that is, $W$ appears
twice.) The two maps $T$ and $S$ might give different answers: $E$ is
the map which “makes them the same.” $E$ takes the element of $W$ you
got by following $T$ and transforms it to the element of $W$ you got
by following $S$.

Roughly speaking, the $E$ that we are looking for is “$`E=S\circ
T^{-1}`$”. That is, given some element of $W$, we “take it back to $V$
with $T^{-1}$ and then forwards again to $W$ using $S$.” Well, anyway,
that's the intuition -- but there are several questions to resolve.

First, $T^{-1}$ might not exist if $T$ isn't surjective. We can't “go
back to $V$” from elements not in the range of $T$ because there's
nowhere for them to have come from. We will need to fix that by making
up somewhere for them to go when acted on by $E$.

Second, $T^{-1}$ might not exist if $T$ isn't injective. That is,
it might be that there are _many_ elements of $V$ which are mapped by
$T$ to the same element of $W$. Then there is a choice of “where to go
back to.” Fortunately, it will turn out that this choice will not
matter.

So let's start with what we can do. First of all, since we know what
to do with vectors in the range of $T$, let's start by separating that
out. Since $\text{range }T$ is a subspace of $W$, it is possible to
write $W$ as a direct sum $W = (\text{range }T)\oplus Z$ where $Z$ is
some other subspace of $W$. (This is Axler 2.33.) What this means is
that there's a way to write any vector in $W$ uniquely as the sum of a
vector in $\text{range }T$ and a vector in some other subspace $Z$
which has no overlap with $\text{range }T$ (except the zero
vector). (The choice of $Z$ itself is not unique but we don't care
about that.)

To define $E$ we need to say what it does to any element $w\in
W$. First, using the decomposition $W = \text{range }T\oplus Z$, write
that element as $w=u+z$ where $u\in\text{range }T$ and $z\in Z$. To
define the action of $E$ on $w$, we may separately define the action
of $E$ on $u$ and on $z$.

Start with $u$. Since $u\in \text{range }T$, there must be some
$v\in V$ such that $T(v) = u$. Set

```math
E(u) = S(v).
```

We must be careful! There might be _another_ $v'\in V$ such that $T(v')
= u$. The rule above makes sense only if $S(v) = S(v')$ for any such
$v'$. Fortunately, that is true. Indeed, if $T(v')=T(v)$ then
$T(v'-v)=0$; in other words, $v'-v$ is in the null space of $T$. But
by supposition this is the null space of $S$. So $S(v'-v)=0$ and
therefore $S(v)=S(v')$.

What about $z$? We will set

```math
E(z) = 
```
. 





we know what $E$ has to do on vectors in the range of $T$ (it takes
$T(\vec{v})$ to $`S(\vec{v})`$) so we need to ensure (a) the this
action is linear and (b) that it does something sensible on other
vectors to make it invertible. Our usual approach to saying what we
mean by “other vectors” is to choose a basis for $W$ that contains a
basis for $\text{range }T$.

That is: (1) choose a basis for the range of $T$, say $\vec{e}_1,
\dots, \vec{e}_m$, and then (2) extend to a basis for $W$, say
$`\vec{e}_1, \dots, \vec{e}_m, \vec{e}_{m+1}, \dots, \vec{e}_n`$. With
this basis, every element of $W$, say $\vec{w}$, can be written as
$`\vec{w} = \sum_i w_i \vec{e}_i`$, which is

```math
\vec{w} = \sum_i w_i \vec{e}_i = \sum_{i=1}^{m} w_i \vec{e}_i +
\sum_{j=m+1}^n w_j \vec{e}_j
```

That is, every vector in $W$ can be written as the sum of an element
of $\text{range }T$ plus a vector not in the range of $T$.

So now, for $\vec{w}\in W$, define $E$ in the following way. Write
$\vec{w} = \vec{u}+\vec{u}'$, where $\vec{u}\in\text{range }T$. Since
$\vec{u}\in\text{range }T$, there must be some place in $V$ from which
this came: there must be some $\vec{v}\in V$ (not necessarily unique)
such that $\vec{u} = T(\vec{v})$. We'd like to set $E(\vec{u}) =
S(\vec{v})$, but we have the problem that the $v$ is not necessarily
unique. Fortunately, the only ways that there can be multiple
$`\vec{v}`$s with $\vec{u}=T(\vec{v})$ is if they differ by elements
of the null space.

That is, suppose $\vec{v}'$ is also such that $T(\vec{v}') =
\vec{u}$. Then $T(\vec{v}'-\vec{v}) = \mathbf{0}$; in other words,
$\vec{v}'-\vec{v}$ is in the null space of $T$. Therefore, by
supposition, $\vec{v}'-\vec{v}$ is in the null space of $S$. Therefore
$S(\vec{v}') = S(\vec{v})$ and so there is no ambiguity in setting
$E(\vec{u}) = S(\vec{v})$.

We are nearly done with the definition of $E$. We want to define
$E(\vec{w})$ for some arbitrary $\vec{w}$, where however we have
written $\vec{w} = \vec{u}+\vec{u}'$, with $\vec{u}\in\text{range
T}$. We know what we want from $E(\vec{u})$ (it's wherever $S$ takes
the vector that $T$ sent to $\vec{u}$) but what about $E(\vec{u}')$?
We could just send that to zero but that would make $E$
non-invertible. So instead let's leave it alone. In other words, $E$
is defined by

```math
E(\vec{w}) = S(\vec{v}) + \vec{u}',
```

where $\vec{w} = \vec{u}+\vec{u}'$ and $T(\vec{v}) = \vec{u}$.

We _still_ have to show that $E$ is a linear map and invertible. To
show that it is linear is an annoying process of following through the
definition above for some $\alpha \vec{w}_1 + \beta \vec{w}_2$ (though
really it can't but be linear given that everything we have done is
linear). Why is it invertible?

$E$ is invertible if it is injective and surjective. It can't be
non-injective on the bit of $W$ that is not the range of $T$, because
we've defined it to be the identity there. Suppose there were distinct
$\vec{u}, \vec{u}'$, both in the range of $T$ such that
$E(\vec{u})=E(\vec{u}')$. That would mean that there must be
$\vec{v},\vec{v}'\in V$, with $\vec{u}=T(\vec{v})$ and
$\vec{u}'=T(vec{v}')$, such that $S(\vec{v}) = S(\vec{v}')$. But that
means that $\vec{v}'-\vec{v}\in\text{null }S$, and hence
$\vec{v}'-\vec{v}\in\text{null }T$ and hence in fact
$T(\vec{v})=T(\vec{v}')$ or $\vec{u}=\vec{u}'$, in contradiction to
the supposition. So $E$ is injective.

Is $E$ surjective? In other words, does every $\vec{w}\in\text{range
}S$ come from some $E(\vec{u})$? Yes: roughly, to find $\vec{u}$, go
back to $V$ (using $S$) and then forward to $W$ (using $T$): existence
and the required properties of $\vec{u}$ follow by running the same
argument above with $T$ and $S$ switched.

Well, that's the "only if" direction. The "if" direction is
easy. Suppose $\vec{v}\in\text{null T}$, say. Then $S(\vec{v}) =
E(T(\vec{v})) = \mathbf{0}$, so $\vec{v}$ is in the null space of
$S$. The argument can be reversed, noting that $E$ is invertible.

## Question 9

Suppose $V$ is finite-dimensional and $T\colon V\to W$ is a surjective
linear map of $V$ onto $W$. Prove that there is a subspace $U$ of $V$
such that $T\rvert_U$ is an isomorphism of $U$ onto $W$.

### Answer

Question 6 was about splitting up $W$ into “the range of $T$ plus
another bit.” This question is sort of the complement: we're splitting
$V$ into “the null space of $T$ plus another bit.”

So, let $(\vec{e}_1, \dots, \vec{e}_m, \vec{f}_1, \dots, \vec{f}_n)$ be
a basis of $V$ such that $(\vec{e}_1, \dots, \vec{e}_m)$ is a basis for
$\text{null }T$ and the $`\vec{f}`$s extend that to a basis of the
full space.

I claim that a subspace satisfying the conditions of the question is
$U = \text{span }(\vec{f}_1, \dots, \vec{f}_n)$. First of all, it _is_
a subspace (since it’s the span of some vectors). The map $T|_U$ is
also surjective. For, given some $\vec{w}\in W$, then, since the
original $T$ was surjective, there must be $\vec{v}\in V$ with
$T(\vec{v}) = \vec{w}$. Now write $\vec{v}=\vec{u}+\vec{\nu}$ where
the $\vec{u}$ is a combination of the $`\vec{f}`$s and the $\vec{\nu}$
is a combination of the $`\vec{e}`$s (ie, in the null space). Since
$T(\vec{\nu})=\mathbf{0}$ we must have $\vec{w} = T(\vec{v}) =
T(\vec{u}) = T|_U(\vec{u}$. And since $\vec{u}\in U$, we have shown
that $T|_U$ is surjective.

Then, suppose $\vec{v}_1,\vec{v}_2\in U$ are distinct; it follows that
$T|_U(\vec{v}_1) \neq T|_U(\vec{v}_2)$, otherwise their difference
would be in $\text{null }T$, and hence that $T|_U$ is injective.

Finally, since $T|_U$ is surjective and injective, it is an
isomorphism.

## Question 18

Show that $V$ and $\mathcal{L}(\mathbf{F}, V)$ are isomorphic vector
spaces.

### Answer

We must exhibit an invertible linear map between $V$ and
$\mathcal{L}(\mathbf{F}, V)$. 

What is $\mathcal{L}(\mathbf{F}, V)$? It is the space of linear maps
from $\mathbf{F}$ to $V$. That is, an element of
$\mathcal{L}(\mathbf{F}, V)$ is a rule which, given a number in
$\mathbf{F}$, produces a vector in $V$. Suppose
$\tilde{w}\in\mathcal{L}(\mathbf{F}, V)$ is one such rule. Then, for
any $\alpha\in\mathbf{F}$, $`\tilde{w}(\alpha) =
\tilde{w}(\alpha\times 1) = \alpha\tilde{w}(1)`$. In other words, any
$\tilde{w}\in\mathcal{L}(\mathbf{F}, V)$ is defined entirely by its
action on $1$. Indeed, $\tilde{w}(1)$ is an element of $V$, so we can
say that any element of $\mathcal{L}(\mathbf{F}, V)$ is defined by a
specific vector in $V$. That's the informal story.

More carefully, consider the map, $\Omega\colon
V\to\mathcal{L}(\mathbf{F}, V)$ which acts in the following way: for
any $\vec{v}\in V$, set $\Omega(\vec{v})$ to be the map

```math
\begin{aligned}
\Omega(\vec{v}) : \mathbf{F} &\to  V \\
\alpha &\mapsto \alpha \vec{v}.
\end{aligned}
```

That is to say, $\Omega(\vec{v})$ is an element of
$\mathcal{L}(\mathbf{F}, V)$, hence a map; specifically the map which
takes any $\alpha\in\mathbf{F}$ to the vector $\alpha\vec{v}$.

I claim the map $\Omega$ is both injective and surjective. Suppose
$\vec{v}, \vec{v}'\in V$ are distinct. Then clearly
$\Omega(\vec{v}) \neq \Omega(\vec{v}')$, since they take $1$ to
different vectors. That shows injectivity of $\Omega$.

Suppose $\tilde{w}\in \mathcal{L}(\mathbf{F}, V)$ is some map. Then
$\tilde{w}(1)$ is some element of $V$, and indeed $\Omega(\tilde{w}(1)) =
\tilde{w}$. That shows surjectivity of $\Omega$.

## Question 21

Suppose $n$ is a positive integer and $A_{jk}\in\mathbf{F}$ for
$j,k\in\{1,\dots,n\}$. Prove that the following are equivalent:

(a) The only solution to the homogeneous system of equations

```math
\sum_k A_{ik} x_k = 0 \quad (i\in\{1,\dots, n\})
```

is the trivial solution $x_1 = \dotsb = x_n = 0$.

(b) For every $c_1,\dots,c_n\in\mathbf{F}$, there exists a solution to
the system of equations

```math
\sum_k A_{ik} x_k = c_i \quad (i\in\{1,\dots, n\}).
```

### Answer

Consider the vector space $\mathbf{F}^n$ and let $A$ be the linear map
in $\mathcal{L}(\mathbf{F}^n, \mathbf{F}^n)$ whose matrix
representation in the canonical basis of $\mathbf{F}^n$ is
$A_{jk}$.

Then (a) is equivalent to the statement that $A$ is injective; and $b$
is equvalent to the statement that $A$ is surjective. But we know
(Axler 3.65) that, for linear maps between finite-dimensional vector
spaces of the same dimension, each of these properties implies the
other.
