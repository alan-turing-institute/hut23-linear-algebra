#lang racket/base

(provide example-poly
         example-xs
         example-ys)

;; Some example data

;; A third-order polynomial
(define (example-poly x)
  (+ (* 0.1 0.5 0.8)
     (* (- x 0.1) (- x 0.5) (- x 0.8))))

;; Some example data
(define example-xs
  (for/list ([i 10])
    (random)))

(define example-ys
  (map example-poly example-xs))



