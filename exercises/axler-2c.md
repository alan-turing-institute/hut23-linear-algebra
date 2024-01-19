# Exercises from Axler 2.C

## Question 1

Show that the subspaces of $\mathbb{R}^2$ are precisely $\{0\}$, all
lines in $\mathbb{R}^2$ containing the origin, and $\mathbb{R}^2$.

## Answer

First, note that the subspaces given _are_ subspaces. (A line through
the origin is the set of all multiples of some fixed vector.) Could
there be any nore?

Since $\mathbb{R}^2$ is two-dimensional, any subspace must have
dimension 0, 1, 2. The 0-dimensional subspace is precisely $\{0\}$
(see definition 2.4). The 2-dimensional subspace is precisely
$\mathbb{R}^2$ by the result in box 2.39. So we are left with the
1-dimensional subspaces.

Suppose $U$ is a 1-dimensional subspace. It has a basis consisting of
a single vector, say $\mathbf{e}$. For any $\alpha\in\mathbb{R}$, it
is true that $\alpha\mathbf{e}\in U$ (because a basis is a spanning
set). So $U$ contains a line through the origin. On the other hand,
there are no other vectors in $U$ (because, if there were,
$\{\mathbf{e}\}$ would not be a basis). So $U$ is precisely a line
through the origin.

## Question 5

### (a)

Let $U=\{p\in\mathcal{P}_4(\mathbb{F}) \mid p(2) = p(5)\}. Find a
basis of $U$.

### Answer

Reminder: $\mathcal{P}_4(\mathbb{F})$ is the space of all polynomials
of degree no more than 4 where the underlying space of numbers is
either $\mathbb{R}$ or $\mathbb{C}$. For example, $x + x^2$.

One way to proceed is to try to write down elements $p(x)$ of
$\mathcal{P}_4(\mathbb{F})$ such that $p(2)=p(5)$. If we can find
enough of these that are linearly independent, we'll have a basis for
$U$. The constant function, $p(x)=1$, has the required property.

To find the others, note that it suffices to find polynomials such
that $p(2) = p(5) = 0$ (because any other can be obained by adding the
constant function).

Here are three others: $(x-2)(x-5)$, $x(x-2)(x-5)$, and
$x^2(x-2)(x-5)$. Note that the four of these are linearly independent
(because they are of different degree). Their span has
dimension 4. There cannot be any more linearly independent polynomials
having the required property because if there were they would span a
subspace of dimension 5 and would therefore be the whole space. So we
have found enough.

### (b)

Extend the basis in (a) to a basis of $\mathcal{P}_4(\mathbb{F})$.

### Answer

We only have to add another, linearly independent, polynomial. $p(x)=x$
will do.

### (c) 

Find a subspace $W$ of $\mathcal{P}_4\mathbb{F}$ such that
$\mathcal{P}_4\mathbb{F} = U\oplus W$.

### Answer

For $W$ we may simply choose the supspace spanned by the vector we
added in (b): that is, the subspace spanned by $\{x\}$. 


## Question 18

