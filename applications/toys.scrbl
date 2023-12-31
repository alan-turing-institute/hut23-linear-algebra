#lang scribble/base
@(require scribble-math/dollar)
@(require plot/pict)
@(require "polynomial-example.rkt")

@(use-mathjax)

@title{Toy applications}
@section{Linear regression}

Here is a ``supervised learning'' problem. We are given 20
training examples, @${(x_1, y_1)}, ..., @${(x_{20}, y_{20})}. 

@centered[
          (plot (points (map vector example-xs example-ys)
                        #:x-min 0 #:x-max 1
                        #:y-min 0 #:y-max 0.125
                        #:color "red" #:size 6 #:line-width 1.6)
                #:x-label "x" #:y-label "y"
		#:title (format "~a data points" (length example-xs))
                #:height 200 #:width 300)]

Our task is to find a rule to predict @${y} from @${x}. That is, we
seek a function, @${f(x)}, which approximates the training data in
that sense that the @${f(x_i)} are ``close to'' the @${y_i}.

As stated, the problem is way too easy! Here is a possible @${f(x)}:

@centered[
          (plot (lines (map vector example-xs example-ys)
                        #:x-min 0 #:x-max 1
                        #:y-min 0 #:y-max 0.125
                        #:color "blue"
                        #:marker (point-sym)
                        #:marker-color "Red" #:marker-alpha 0.5
			#:marker-size 6 #:marker-line-width 1.6)
                #:x-label "x" #:y-label "y"
		#:title "A best-fit line?"
                #:height 200 #:width 300)]

This @${f(x)} joins up all the points with straight lines and so
matches the training data exactly. In most cases that is not actually
what we want. We don't really believe that the ``true'' relationship
between @${x} and @${y} is given my the piecewise linear curve.  We
don't really believe that the ``true'' @${y_i} are exactly as given in
the training data: there is usually some noise or unexplained
variation that is unlikely to be the same next time we measure the
same point. What we really want is a ``smooth'' function which does
its best to go near the data without being unrealistic.

A popular approach is as follows. First, we choose a set of
@italic{candidate} functions. The candidate functions are functions
which are thought to be ``appropriate'' in whatever sense that means
for the particular problem at hand. Then we find the candidate
function which is ``closest'' to the data, in some sense of
``closest'' which we also have to define.

How might we choose the set of candidate functions? Well, we don't
like functions that ``wiggle too much''---those are the ones which can
fit any dataset and so are likely to over-fit. So one immediate idea
is to select functions which don't wiggle too much. ``Wiggling'' is
captured by the size of the higher-order derivatives of the
function. So we might choose functions for which all derivatives
higher than, say, the third are zero. That is, choose a set,
@${\mathcal{F}}, of functions where, for any @${f\in\mathcal{F}},

@$${
\frac{d^nf}{dx^n} = 0 \quad\text{for all $n\geq 4$}.
}

Here are some examples of functions from @${\mathcal{F}}$:

