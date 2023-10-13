# Selected exercises from Axler 1.A

## Q.1
### Question

Suppose $a$ and $b$ are real numbers, not both 0. Find real numbers
$c$ and $d$ such that $1 / (a + b\mathrm{i}) = c + d\mathrm{i}$.

### Solution

A complex number consists of a “real part” and an “imaginary part.” The
condition says that $a + b\mathrm{i}$ is a complex number whose real
part is $a$ and whose imaginary part is $b$ (and that this number is not
zero).

What the question is really asking is,“how do you compute the
multiplicative inverse of a complex number?”

If we knew $c$ and $d$ we would know the complex number that is the
multiplicative inverse of $a + b\mathrm{i}$. It *looks* like we’ve got
two unknowns ($c$ and $d$) and only one equation. That’s not good! In
general, one needs two equations to find two unknowns: one equation is
under-determined.

But in fact, every equation involving complex numbers is really two
equations in disguise: One obtained by equating the real parts, and one
obtained by equating the imaginary parts. So the trick here is to get
this into a form where we can equate the real and imaginary parts of
both sides.

Multiplying both sides by $a + b\mathrm{i}$ gives:
$$1 = (a + b\mathrm{i}) (c + d\mathrm{i})$$

Expanding out the right hand side and collecting terms gives:
$$1 = (ac - bd) + (bc + ad) \mathrm{i}$$ (The minus sign is there
because $\mathrm{i}^2 = -1$.)

Now it’s in the right form: we can “read off” the real parts and the
imaginary parts of both sides of this equation. Since the real parts
have to be equal: $$1 = (ac - bd);$$ and since the imaginary parts have
to be equal: $$0 = (bc + ad).$$

That’s two equations and there are two unknowns ($c$ and $d$) so now
we’re in with a fighting chance. One way to proceed is to use the second
equation to get $d$ in terms of $c$: $$d = -bc / a.$$ Then substitute
for $d$ in the first equation leaving something that can be solved for
$c$.

The results are: $$c = \frac{a}{a^2 + b^2}
  \quad\text{and}\quad 
    d = \frac{-b}{a^2 + b^2}.$$

## Q.4

### Question
Show that $\alpha + \beta = \beta + \alpha$ for all
$\alpha, \beta \in \mathbold{C}$.

### Solution
The technical term for an operation where the order doesn’t matter is a
*commutative* operation.

One’s first thought on reading this question is likely to be something
like, “isn’t that just true?” However, the thing to note is that, since
$\alpha$ and $\beta$ are complex numbers, the $+$ operation is
“complex addition,” not ordinary addition of real numbers. It *is*
obvious that ordinary addition is commutative (or, at least, we all
believe that fact) whereas the claim that complex addition is
commutative is something that requires a demonstration.

The definition of addition of complex numbers is given on page 2 of
Axler; it is: “add together separately the real parts and the imaginary
parts.” Put like that, the result follows immediately: adding together
the real parts is commutative (because it is ordinary addition) and the
same is true of adding together the imaginary parts. And so the addition
of complex numbers does not depend on the order either.

#### A wrinkle

Well, perhaps the result follows immediately but it’s worth giving the
argument again in symbols because it is surprising how easy it is to
switch unknowingly from one meaning to another.

In fact, let’s put a dot over the $+$ to indicate that this is complex
addition (this notation is not standard!). What we’re being asked to
show is:
$$\alpha \dotplus \beta = \beta \dotplus \alpha.$$
*That* makes it look more like there’s a thing to show because there’s
this odd $\dotplus$ and it’s not obvious how $\dotplus$ behaves.

In Axler, there’s a formula that is supposed to define complex addition.
Axler says that the sum of the complex numbers $a+b\mathrm{i}$ and
$c+d\mathrm{i}$ is given by:
$$(a + b\mathrm{i}) + (c + d\mathrm{i}) = (a+c) + (b+d)\mathrm{i}\quad\text{(from Axler)}.$$
But wait! There are six plus signs in this equation! Which one is
supposed to be the complex addition being defined? Presumably, it’s the
middle one on the left, like this:
$$(a + b\mathrm{i}) \dotplus (c + d\mathrm{i}) := (a+c) + (b+d)\mathrm{i}.$$
(There’s a dot on the plus that this equation is supposed to define.)

What about the other plus signs? The ones in $a+c$ and $b+d$ on the
right are just ordinary addition because $a$, $b$, $c$, and $d$ are all
real numbers.

But what about the additions in $a+b\mathrm{i}$ and $c+d\mathrm{i}$ on
the left? What kind of additions are *they*? They can’t be ordinary
addition because, for example, $a$ is real but $b\mathrm{i}$ is
imaginary and ordinary addition is only defined for real numbers. On the
other hand, it would be very weird indeed if they were complex addition
because then the whole equation looks like it’s assuming the very thing
it’s supposed to be defining. What is going on?

What’s going on is an abuse of notation. What Axler says to begin with,
is that a complex number is a *pair* of real numbers, like this:
$(a, b)$. Then the actual definition of complex addition is this:
$$(a, b) \dotplus (c, d) := (a+c, b+d) \quad\text{(what Axler should have said)}.$$

The expression $a+b\mathrm{i}$ is a sort of notational convenience for
$(a,b)$. Once complex addition is defined, one can of course choose to
write $a\dotplus b\mathrm{i}$—or, indeed $a+b\mathrm{i}$, just using
$+$ for complex addition as well as ordinary addition.

## Q.7
### Question
Show that for every $\alpha\in \mathbf{C}$, there exists a unique
$\beta\in \mathbf{C}$ such that $\alpha+\beta = 0$.

### Answer
This question is asking us to show that “additive inverses exist and are
unique.” There are two parts: (1) showing they exist and (2) showing
they are unique.

The best way to show existence, if you can do it, is actually to
construct an example. Here, a complex number $\alpha$ is a pair of real
numbers, $(\alpha_r, \alpha_i)$ (that’s the real part and the imaginary
part). We need a complex number $\beta$, say $(\beta_r, \beta_i)$, such
that: $$(\alpha_r, \alpha_i) + (\beta_r, \beta_i) = (0, 0).$$ The
definition of complex addition (as we talked about above) is that
$(\alpha_r, \alpha_i) + (\beta_r, \beta_i) = (\alpha_r + \beta_r, \alpha_i + \beta_i)$.
So we’re looking for $\beta_r$ and $\beta_i$ such that
$$(\alpha_r + \beta_r, \alpha_i + \beta_i)= (0, 0).$$ from which it’s
clear that $(\beta_r, \beta_i) = (-\alpha_r, -\alpha_i)$ will satisfy
the requirements.

Could there be some *other* $\beta$? Consider the real part of the
above: $\alpha_r + \beta_r = 0$. Since additive inverses are unique in
the reals, there’s only one $\beta_r$ satisfying this expression; and
likewise for the $\beta_i$. So there is in fact only one
$(\beta_i, \beta_r)$ with this property.

Why are additive inverses unique in the reals? Well, suppose there were
some *other* $\beta'_r$ which also had the property,
$\alpha_r + \beta'_r =0$. Then: 
```math
\begin{align}
    \alpha_r + \beta_r &= 0 \\
    \alpha_r + \beta_r + \beta'_r &= \beta'_r &&\text{(adding $\beta'_r$ to both sides)} \\
    \alpha_r + \beta'_r + \beta_r &= \beta'_r &&\text{(because addition is commutative)} \\
      0 + \beta_r &= \beta'_r &&\text{(by assumption of $\beta'_r$)} \\
      \beta_r &= \beta'_r &&\text{(by definition of 0)}. \\
  \end{align}
```
So, if there were a $\beta'_r$ that is an additive
inverse of $\alpha_r$ it would be the same as $\beta_r$.


## Q.8
### Question
Show that for every $\alpha\in \mathbf{C}$ with $\alpha \neq 0$,
there exists a unique $\beta\in \mathbf{C}$ such that
$\alpha\beta = 1$.

### Answer
In question 1 we actually constructed the multiplicative inverse of
$\alpha$ explicitly, so we have already shown existence of $\beta$.

To show uniqueness we can use the same trick as in question 7, replacing
addition with multiplication. We do need to assume that complex
multiplcation is associative (which is shown in question 6) and
commutative (which is apparent from the definition of complex
multiplication). Assume, then, that there is some $\beta'$ such that
$\alpha\beta'=1$. Then, 
```math
\begin{align}
    \alpha \beta &= 1 \\
    (\alpha \beta) \beta' &= \beta' &&\text{(multiplying by $\beta'$ on the right)} \\
    \alpha (\beta \beta') &= \beta' &&\text{(by associativity)} \\
    \alpha (\beta' \beta) &= \beta' &&\text{(by commutativity)} \\
    (\alpha \beta') \beta &= \beta' &&\text{(associativity again)} \\
    1 \beta &= \beta' &&\text{(by assumption that $\alpha\beta'=1$)} \\
    \beta &= \beta' &&\text{(multiplication by 1)}. 
  \end{align}
```
Thus, if there is some inverse of $\alpha$ it is the
same as $\beta$.


## Q.10

### Question

Find $x \in \mathbf{R}^4$ such that $$(4, -3, 1, 7) + 2x = (5, 9, -6, 8).$$

### Solution

Write $x = (x_1, x_2, x_3, x_4)$. Finding $x$ means finding $x_1,
\dotsc, x_4$.

From the definition of addition in $\mathbf{R}^n$, $$(4, -3, 1, 7) + 2x = 
(4+2x_1, -3+2x_2, 1+2x_3, 7+2x_4).$$ 
Therefore,
$$(4+2x_1, -3+2x_2, 1+2x_3, 7+2x_4) = (5, 9, -6, 8).$$

Equating the first component of the tuples gives $4+2x_1 = 5$, and
therefore $x_1 = 1/2$. Similarly, the second, third, and fourth
components give $x_2 = 6$, $x_3 = -7/2$, and $x_4=1/2$ respectively.

#### Alternative approach

There is another way to approach this problem, one which is perhaps
more “natural” for “things that live in $\mathbf{R}^4$”:

Start with $$(4, -3, 1, 7) + 2x = (5, 9, -6, 8).$$ 
Now subtract $(4, -3, 1, 7)$ from both sides. (The meaning of “subtract
$X$” is “add $-X$.”). Thus: 
$$2x = (1, 12, -7, 1).$$ 
Finally, divide both sides by 2. (The maning of “divide by $\lambda$”
is “multiply by $1/\lambda$”). Thus:
$$x = (1/2, 6, -7/2, 1/2).$$ 


## Q.11

### Question

Explain why there does not exist a $\lambda \in \mathbf{C}$ such
that $$\lambda (2 - 3i, 5 + 4i, -6 + 7i) = (12 - 5i, 7 + 22i, -32 - 9i).$$

### Solution

For this equation to be true, each component on the right must be the
same multiple, $\lambda$, of the corresponding component on the
left. (This follows from the definition of scalar multiplication in
$\mathbf{R}^3$.) In general this will not be true. 

Equating the first components gives $\lambda (2 - 3i) = 12 -5i$
and therefore $\lambda = \frac{12-5i}{2-3i}$.

There's a standard trick to dividing one complex number by another
(which question 1 gets you to do explicitly). That is to multiply both
the numerator and denominator by a carefully chosen complex number so
that the result in the denominator is purely real. In this case:
$$\frac{12-5i}{2-3i} = \frac{12-5i}{2-3i}\times \frac{2+3i}{2+3i} =
\frac{(12-5i)(2+3i)}{(2-3i)(2+3i)} = \frac{39 + 26i}{13} = 3 + 2i.$$
(The number that you multiply top and bottom by is always the same as
the denominator but with the sign of the imaginary part reversed.)

The same calculation for all the components is:
$$\frac{12-5i}{2-3i} = 3 + 2i, \quad
\frac{7+22i}{5+4i} = 3 + 2i, \quad\text{and}\quad
\frac{-32-9i}{-6+7i} = (129 + 278i) / 85.$$

Since those are not all the same number, no single $\lambda$ works for
all components, and so the original equation cannot be satisfied.


## Q.14

### Question
Show that $1x = x$ for all $x\in \mathbf{F}^n$.

### Solution
$x$ is a tuple of numbers, $(x_1, x_2, \dotsc, x_n)$. From the definition
of scalar multiplication:
$$1 (x_1, x_2, \dotsc, x_n) = (1 x_1, 1 x_2, \dotsc, 1 x_n) = (x_1, x_2, \dotsc, x_n).$$


## Q.16

### Question
Show that $(a+b)x = ax + bx$ for all $a,b \in \mathbf{F}$ and all 
$x \in \mathbf{F}^n$.

### Solution
$x$ is a tuple of numbers, $(x_1, x_2, \dotsc, x_n)$. From the definition
of scalar multiplication:
```math
\begin{align}
(a+b) (x_1, x_2, \dotsc, x_n) 
&= ((a+b) x_1, (a+b) x_2, \dotsc, (a + b) x_n) \\
&= (a x_1 + b x_1, a x_2 + b x_2, \dotsc, a x_n + b x_n) \\
&= (a x_1, a x_2, \dotsc, a x_n) + (b x_1, b x_2, \dotsc, b x_n) \\
&= a (x_1, x_2, \dotsc, x_n) + b (x_1, x_2, \dotsc, x_n).
\end{align}
```
