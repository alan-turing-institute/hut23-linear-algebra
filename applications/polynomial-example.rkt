#lang racket/base
(require math/distributions
         racket/flonum)

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
  (sort
   (for/list ([_ 20])
     (random))
   <))

(define (norm-sample s)
  (flvector-ref (flnormal-sample 0.0 s 1) 0))

(define example-ys
  (map (λ (x) (+ (example-poly x)
                 (norm-sample 0.01)))
       example-xs))



