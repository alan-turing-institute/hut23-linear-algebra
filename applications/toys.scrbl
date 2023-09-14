#lang scribble/base
@(require scribble-math/dollar)
@(require plot/pict)
@(require "polynomial-example.rkt")

@(use-mathjax)

@title{Toy applications}
@section{Linear regression}

Here is a toy ``supervised learning'' problem. We are given ten
training examples, @${(x_1, y_1)}, ..., @${(x_{10}, y_{10})}. Our task
is to find a rule to predict @${y} from @${x}.

@(plot (points (map vector example-xs example-ys)
               #:x-min 0 #:x-max 1
               #:y-min 0 #:y-max 0.125
               #:color "red" #:size 6 #:line-width 1.6)
       #:x-label "x" #:y-label "y"
       #:height 200 #:width 300)

