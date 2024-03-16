#lang racket

(require "load.rkt")


;; ------------------------------------------------------------
;; Represent a matrix as a struct

(struct matrix (ncols vec) #:transparent)

(define (make-matrix nrows ncols [v 0])
  (matrix ncols (make-vector (* nrows ncols) v)))

(define (matrix-nrows m)
  (quotient (vector-length (matrix-vec m)) (matrix-ncols m)))

;; Return element in the ith row and jth column
;; Index from 0
(define (matrix-ref m i j)
  (vector-ref (matrix-vec m) (+ j (* i (matrix-ncols m)))))

(define (matrix-set! m i j v)
  (vector-set! (matrix-vec m) (+ j (* i (matrix-ncols m))) v))

(define (matrix-equal-within? delta m1 m2)
  (and
   (= (matrix-ncols m1) (matrix-ncols m2))
   (= (matrix-nrows m1) (matrix-nrows m2))
   (andmap
    (λ (v1 v2)
      (<= (abs (- v1 v2)) delta))
    (vector->list (matrix-vec m1))
    (vector->list (matrix-vec m2)))))

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

;; ------------------------------------------------------------
;; main


(display "Loading test data ")

(match-define (list as bs cs)
  (map
   (λ (x)
     (map
      (λ (m)
        (let ([ncols (car m)]
              [vs    (cdr m)])
          (matrix ncols vs)))
      x))
   (load-float64-arrays-from-dir "../testdata/matrices")))

(display "done \n")

(display "Checking test cases...")

(unless
    (andmap
     (λ (m1 m2) (matrix-equal-within? 0.01 m1 m2))
     cs (map matrix-mul as bs))
  (error "something went wrong!"))

(displayln " done.")

(define *repeats* 32768)

(printf "Trying ~a matrix multipications.\n" (* *repeats* (length as)))

(display
 (time
  (for ([i (in-range *repeats*)])
    (when (zero? (modulo i 1024))
      (display "."))
    (map matrix-mul as bs))))


