#lang scribble/base
@(require scribble-math/dollar)
@(require plot/pict)
@(require "polynomial-example.rkt")

@(use-mathjax)

@title{Toy applications}
@section{Linear regression}

Here is a ``supervised learning'' problem. We are given ten
training examples, @${(x_1, y_1)}, ..., @${(x_{10}, y_{10})}. 

@centered[
          (plot (points (map vector example-xs example-ys)
                        #:x-min 0 #:x-max 1
                        #:y-min 0 #:y-max 0.125
                        #:color "red" #:size 6 #:line-width 1.6)
                #:x-label "x" #:y-label "y"
                #:height 200 #:width 300)]

Our task is to find a rule to predict @${y} from @${x}. That is, we
seek a function, @${f(x)}, which approximates the training data in
that sense that the @${f(x_i)} are ``close to'' the @${y_i}.

As stated, the problem is too easy! Here is a possible @${f(x)}:

@centered[
          (plot (lines (map vector example-xs example-ys)
                        #:x-min 0 #:x-max 1
                        #:y-min 0 #:y-max 0.125
                        #:color "blue"
                        #:marker (point-sym)
                        #:marker-color "Pink" #:marker-size 6 #:marker-line-width 1.6)
                #:x-label "x" #:y-label "y"
                #:height 200 #:width 300)]

This @${f(x)} joins up all the points with straight lines and so matches
the training data exactly. In most cases that is not actually what we
want. The problem is that we typically don't really believe that the
@${y_i} are exactly as given in the training data; there is usually
some noise. So we don't want the approximating functions to 



