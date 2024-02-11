# Exercises from Axler 3.B

1, 2, 3, 9; 25, 27, 29.


## Question 1

Give an example of a linear map with $\text{dim null }T = 3$ and
$\text{dim range }T = 2$.

### Answer

The dimension of the domain must be 5. So let
$M:\mathbf{R}^5\to\mathbf{R}^5$ be given by:

```math
M \colon (x_1, x_2, x_3, x_4, x_5) \mapsto (0, 0, 0, x_4, x_5).
```

## Question 2

Suppose $S, T\in\mathcal{L}(v)$ are such that $\text{range }S\subseteq \text{null
}T$. Prove that $(ST)^2 = 0$.

### Answer

$(ST)^2$ means $STST$, where the rightmost map acts first. If we write
the map $S$, say, acting on $V$ as $V\stackrel{S}{\to} V$, then $STST$
can be written:

```math
V \xrightarrow{T} V \xrightarrow{S} V \xrightarrow{T} V \xrightarrow{S} V. 
```
