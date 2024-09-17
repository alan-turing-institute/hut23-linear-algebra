//unitsize(1cm);
defaultpen(fontsize(9pt));

path subspc = (0.2,-1)--(-0.2,1);

draw(subspc);
label("$U$", (-0.2,1), 2*N);

// The vector space
draw(shift(2,0)*scale(0.8)*((-1,1)--(1,1)--(1,-1)--(-1,-1)--cycle));
label("$V$", (2.8,0.8), 1.5*N);

// Axes
draw(shift(2,0)*((-1,0)--(1,0)), dashed+grey);
draw(shift(2,0)*((0,-1)--(0,1)), dashed+grey);

// Image of space of functions
draw(shift(2,0) * subspc);
label("$\phi[U]$", (1.8,1), 2*N);

// The data
// dot("$\bm{y}$", (2.4,.4), NE);

// The evaluation map
pair p = relpoint(subspc, 0.7);
// path evalmap = p{(1,0.2)}..(shift(1.6,0) * p);
path evalmap = p--(shift(2,0) * p);

draw(evalmap, dotted, Arrow(size=4pt), margin = Margins);
label("$\phi$", midpoint(evalmap), N);

