# Questions from Axler 5d

2, 4, 14

## Question 2

Suppose $A$ and $B$ are upper-triangular matrices of the same size,
with $\alpha_1$, \dots, $\alpha_n$ on the diagonal of $A$ and
$\beta_1$, \dots, $\beta_n$ on the diagonal of $B$.

(a) Show that $A+B$ is an upper-triangular matrix with
$\alpha_1+\beta_1$, \dots, $\alpha_n+\beta_n$ on the diagonal.

(b) Show that $AB$ is an upper-triangular matrix with
$\alpha_1\beta_1$, \dots, $\alpha_n\beta_n$. 𝛼1𝛽$ on the diagonal.

### Answer

(a) We must show that the leading diagonal has the form given and also
that the entries below the leading diagonal are zero.

Write $C=A+B$. We must show (i) that $C_{ii}=A_{ii}+B_{ii}$
($i=1,\dotsc,n$); and (ii) that $C_{ij}=$ when $i>j$. Both follow
immediately from the definition of matrix addition (3.34 in Axler)
noting that $i>j$ implies that $A_{ij}=0$ and $B_{ij}=0$.

(b) This part is slightly trickier. Write $C = AB$, so that (from
Axler 3.41)

```math
C_{ij} = \sum_k A_{ik}B_{kj}.
```.

Start with $C_{ii}$. This term is $C_{ii}=\sum_k A_{ik}B_{ki}$. In the
sum on the right hand side, $k$ ranges over
$1$,\dots,$i-1$,$i$,$i+1$,\dots,$n$. But when $k<i$ the element
$A_{ik}$ is zero; and when $k>i$, the element $B_{ki}$ is zero
(because $A$ and $B$ are upper-triangular). So the only term which
contrinutes to $C_{ii}$ is $A_{ii}B_{ii}$, as required.

Likewise, suppose $i>j$ and consider $C_{ij}=\sum_k A_{ik}B_{kj}$. At
least one of the multiplicands is zero when $k<i$ or when $k>j$. So
the only terms which could be non zero are when $k$ is between $i$ and
$j$. But $i>j$, so there are no such terms. Thus the sum is zero.


## Question 4

Give an example of an operator whose matrix with respect to some basis
contains only 0’s on the diagonal, but the operator is invertible.

(Note that the matrix is not required to be im upper-triangular form,
only that the diagonal elements are zero.)

### Answer

