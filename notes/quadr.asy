import graph;
size(6cm, 4cm, keepAspect = false);
defaultpen(fontsize(9pt));

real f(real x) { return 2.0*x*x - 8.0*x + 9.0; }

draw(graph(f,0,4.0), black+1.2);

// scale(false);

// xlimits(0, 4);
// ylimits(0, 10);

// crop();

xaxis("$x$", xmin = 0, xmax = 4, RightTicks(DefaultFormat, new real[] {0,2}));
yaxis("$y$", ymin = 0, ymax = 10, LeftTicks(DefaultFormat, new real[] {0, 1}));

dot((2, 1));

// label("$\Gamma(x)$",(1,2),red);
