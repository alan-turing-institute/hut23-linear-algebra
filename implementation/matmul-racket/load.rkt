#lang racket

(require binaryio)

;; Returns (as bs cs) where xs is a list of "arrays"
;; Each array is a pair (n . v), where v is a vector
;; and n the length of the rows.
(provide load-float64-arrays-from-dir)

(struct npy-header
  (magic-string
   major-version-number
   minor-version-number
   length
   format)
  #:transparent)

(define (load-float64-arrays-from-dir dir)
  (define filenames (directory-list dir))
  ;; each filename is X_999.npy, where X is a, b, or c and 999 is a number->string

  (define n-matrices
    (+ 1
       (apply max
              (map
               (λ (entry)
                 (string->number
                  (cadr (regexp-match #rx"[abc]_([0-9]+).npy" (path->string entry)))))
               filenames))))

  ;; returns (values as bs cs)
  (define-values (as bs cs)
    (for/lists (as bs cs)
               ([i (in-range n-matrices)])
      (when (zero? (modulo i (quotient n-matrices 8)))
        (display "."))
      (apply values
             (for/list ([x '("a" "b" "c")])
               (call-with-input-file
                 (build-path dir (string-append x "_" (number->string i) ".npy"))
                 load-float64-array-from-npy)))))

  (list as bs cs))


(define (load-float64-array-from-npy in)
  ;; Read header
  (define the-header 
    (let* ([mgc (read-bytes 6 in)]
           [maj (read-integer 1 #f in)]
           [min (read-integer 1 #f in)]
           [len (read-integer 2 #f in #f)]
           [fmt (bytes->string/latin-1 (read-bytes len in))])
      (npy-header mgc maj min len fmt)))
  
  ;; Parse shape from a Python dictionary (!)
  (define the-shape
    (let ([shape (regexp-match #rx"'shape': \\(([0-9]+), ([0-9]+)\\)"
                               (npy-header-format the-header))])
      (list (string->number (cadr shape)) 
            (string->number (caddr shape)))))

  ;; Read array and return it and the length of a row
  (cons (cadr the-shape)
        (for/vector ([_ (in-range (* (car the-shape) (cadr the-shape)))])
          (read-float 8 in #f))))



