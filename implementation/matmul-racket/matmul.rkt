#lang racket

(require "load.rkt"
         "matrix-unsafe.rkt")

;; ------------------------------------------------------------
;; main


(display "Loading test data ")

(match-define (list as bs cs)
  (load-float64-arrays-from-dir "../testdata/matrices" matrix-of-vector))

(displayln " done.")

(display "Checking test cases...")

(unless
    (andmap
     (λ (m1 m2) (matrix-equal-within? 0.01 m1 m2))
     cs (map matrix-mul as bs))
  (error "something went wrong!"))

(displayln " done.")

(define *repeats* 32768)

(printf "Trying ~a matrix multiplications.\n" (* *repeats* (length as)))

(display
 (time
  (for ([_ (in-range *repeats*)])
    (map matrix-mul as bs))))


