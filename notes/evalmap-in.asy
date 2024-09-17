//unitsize(1cm);
defaultpen(fontsize(9pt));

path subspc = (0,-1){(1,2)}..(0,0)..{(1,2)}(0,1);

// Not what I wanted, but what I needed
path funcspc = (-1,1){up}..(0,1){right}..(1,1){down}..(1.1,0){down}..(1,-1){left}..(0,-1.1){left}..(-1,-1){up}..(-1.1,0){up}..cycle;

// The space of functions
// Thick version:
// draw(subspc, currentpen+linewidth(2pt));
draw(subspc);
label("$\mathcal{F}$", (0,1), 2*N);

// The vector space
draw(shift(2,0)*scale(0.8)*((-1,1)--(1,1)--(1,-1)--(-1,-1)--cycle));
label("$\bm{R}^d$", (2.8,0.8), 1.5*N);

// Axes
draw(shift(2,0)*((-1,0)--(1,0)), dashed+grey);
draw(shift(2,0)*((0,-1)--(0,1)), dashed+grey);

// Image of space of functions
draw(shift(1.6,0) * subspc);
label("$\mathcal{E}_{\bm{x}}[\mathcal{F}]$", (1.6,1), 2*N);

// The data
dot("$\bm{y}$", (2.4,.4), NE);

// The evaluation map
pair p = relpoint(subspc, 0.7);
path evalmap = p{(1,0.2)}..(shift(1.6,0) * p);

draw(evalmap, dotted, Arrow(size=4pt), margin = Margins);
label("$\mathcal{E}_{\bm{x}}$", midpoint(evalmap), N);

// Some function mapped inside R^d
// dot("$f$", p, W);
// dot("$\mathcal{E}_{\bm{x}}(f)$", shift(1.6,0) * p, S);




// draw(shift(2,0)*scale(0.8)*rn);


