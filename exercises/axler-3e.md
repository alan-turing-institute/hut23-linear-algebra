# Exercises from Axler 3.E

3, 8, 13.

## Question 3

Suppose $V_1, \dots, V_m$ are vector spaces. Prove that
$\mathcal{L}(V_1\times\dotsb\times V_m, W)$ and $\mathcal{L}(V_1, W)
\times\dotsb\times \mathcal{L}(V_m, W)$ are isomorphic vector spaces.

### Answer

If all the vector spaces were finite-dimensional, we could show that
the dimension of each side matched and be done. However, it is not
stated that they are. So let us try to exhibit an isomorphism.

An element of the left hand side, say $\rho$, is a map from tuples
$(v_1, \dotsc, v_m)$ (where $v_i\in V_i$) to $W$. For each $i$, define
$\rho_i\in \mathcal{L}(V_i, W)$ by $\rho_i(v_i) =
\rho((0,\dotsc,0,v_i,0,\dotsc,0))$ for any $v_i\in V_i$. The tuple
$(\rho_1,\dotsc,\rho_m)$ is an element of $\mathcal{L}(V_1, W)
\times\dotsb\times \mathcal{L}(V_m, W)$,
