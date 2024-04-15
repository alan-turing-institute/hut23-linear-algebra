#lang racket/base

(provide
 matrix
 make-matrix
 matrix-nrows
 matrix-ncols
 matrix-ref
 matrix-set!
 matrix-equal-within?
 matrix-mul
 matrix-of-vector
 )

;; ------------------------------------------------------------
;; 

;; A matrix is a pair, (ncols vec)

(define (matrix ncols vec)
  (cons ncols vec))

(define (make-matrix nrows ncols [v 0])
  (matrix ncols (make-vector (* nrows ncols) v)))

(define (matrix-of-vector ncols vs)
  (matrix ncols vs))

(define (matrix-nrows m)
  (quotient (vector-length (cdr m)) (car m)))

(define (matrix-ncols m)
  (car m))

;; Return element in the ith row and jth column
;; Index from 0
(define (matrix-ref m i j)
  (vector-ref (cdr m) (+ j (* i (car m)))))

(define (matrix-set! m i j v)
  (vector-set! (cdr m) (+ j (* i (car m))) v))

(define (matrix-equal-within? delta m1 m2)
  (and
   (= (matrix-ncols m1) (matrix-ncols m2))
   (= (matrix-nrows m1) (matrix-nrows m2))
   (andmap
    (λ (v1 v2)
      (<= (abs (- v1 v2)) delta))
    (vector->list (cdr m1))
    (vector->list (cdr m2)))))

;; ------------------------------------------------------------
;; Mathematics

(define (matrix-mul m1 m2)
  (let ([I (matrix-nrows m1)]
        [J (matrix-ncols m2)]
        [K (matrix-ncols m1)])
    (unless (= K (matrix-nrows m2))
      (error "Matrices not compatible"))
    (define vec
      (for*/vector #:length (* I J)
                   ([i (in-range I)]
                    [j (in-range J)])
        (for/sum ([k (in-range K)])
          (* (matrix-ref m1 i k)
             (matrix-ref m2 k j)))))
      
    (matrix J vec))
  )
