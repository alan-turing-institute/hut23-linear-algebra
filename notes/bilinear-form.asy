//unitsize(1cm);
defaultpen(fontsize(9pt));

transform vt = yscale(sqrt(2)) * shift(-0.5, -0.5);
transform xt = shift(2, 0);

path vecspace1 = vt * unitsquare;
path vecspace2 = xt * vecspace1;

filldraw(vecspace1, lightgray);
filldraw(vecspace2, lightgray);

path lineofcentres = (0,0)--xt*(0,0);
path curveofcentres = (0,0)..shift(0, 0.5)*midpoint(lineofcentres)..xt*(0,0);

// draw(upcurve, blue);

real[] c1s = intersect(curveofcentres, vecspace1);
real[] c2s = intersect(curveofcentres, vecspace2); 

path mapcurve = subpath(curveofcentres, c1s[0], c2s[0]);

draw(mapcurve, margin = DotMargins, Arrow(size=4pt));
// draw(reflect((0,0),E) * mapcurve, margin = DotMargins, BeginArrow(size = 4pt));

label("$V$", vt * (0.5, 1), 2 * N);
label("$V^*$", xt * vt * (0.5, 1), 2 * N); 

label("$\bm{C}$", midpoint(mapcurve), N);
// label("$C^{-1}$", reflect((0,0),E) * midpoint(mapcurve), S);

dot("$v$", vt * (0.7, 0.7), W);
dot("$\bm{C}(v)$", xt * vt * (0.3, 0.7), E);

// dot("$\tilde{b}$", xt * vt * (0.3, 0.2), E);
// dot("$C^{-1}(\tilde{b})$", vt * (0.7, 0.2), W);
