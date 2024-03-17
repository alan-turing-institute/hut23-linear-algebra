#lang racket/base

(require racket/flonum)

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

(define (matrix-vec m)
  (cdr m))

(define (matrix-nrows m)
  (quotient (flvector-length (cdr m)) (car m)))

(define (matrix-ncols m)
  (car m))

(define (make-matrix nrows ncols [v 0.0])
  (matrix ncols (make-flvector (* nrows ncols) v)))

(define (matrix-of-vector ncols vs)
  (matrix ncols (apply flvector (vector->list vs))))


;; Return element in the ith row and jth column
;; Index from 0
(define (matrix-ref m i j)
  (flvector-ref (cdr m) (+ j (* i (car m)))))

(define (matrix-set! m i j v)
  (flvector-set! (cdr m) (+ j (* i (car m))) v))

(define (flvector->list flv)
  (for/list ([v (in-flvector flv)])
    v))

(define (matrix-equal-within? delta m1 m2)
  (and
   (= (matrix-ncols m1) (matrix-ncols m2))
   (= (matrix-nrows m1) (matrix-nrows m2))
   (andmap
    (λ (v1 v2)
      (<= (abs (- v1 v2)) delta))
    (flvector->list (cdr m1))
    (flvector->list (cdr m2)))))

;; ------------------------------------------------------------
;; Mathematics

(define (matrix-mul m1 m2)
  (let ([I (matrix-nrows m1)]
        [J (matrix-ncols m2)]
        [K (matrix-ncols m1)])
    (unless (= K (matrix-nrows m2))
      (error "Matrices not compatible"))
    (let ([v1 (matrix-vec m1)]
          [v2 (matrix-vec m2)])
      (define vec
        (for*/flvector #:length (* I J)
                       ([i (in-range I)]
                        [j (in-range J)])
          (let dotprod ([k1 K]
                        [acc 0.0])
            (if (zero? k1)
                (fl+ acc) ;; This halves the time over simply returing acc!
                (let ([k (- k1 1)])
                  (dotprod k
                           (fl+ acc
                                (fl* (flvector-ref v1 (+ k (* i K)))
                                     (flvector-ref v2 (+ j (* k J)))))))))))
      
      (matrix J vec))))
