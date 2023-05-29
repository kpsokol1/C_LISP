(define simple_function()
    (+ 6 4)
)

(define ascending? (lis) (cond
    (nil? lis) 't
    (nil? (cdr lis)) 't
    (> (car lis) (car (cdr lis))) ()
    't (ascending? (cdr lis))
))

(define ascendinglist? (lis) (cond
    (nil? lis) 't
    (ascending? (car lis)) ( ascendinglist? (cdr lis))
    't ()
))

(define contains? (x a) (cond
    (nil? a) ()
    (number? a) (eq? x a)
    (contains? x (car a)) 't
    (contains? x (cdr a)) 't
    't ()
))



(simple_function)                                                   ;10
(ascending? '(1 3 2))                                               ;()
(ascending? '(1 2 3))                                               ;T


(ascendinglist? '(( 1 2 3 ) ( 9 ) ( 4 5 )))                         ;T
(ascendinglist? '(( 1 2 3 ) ( 9 ) ( 5 4 )))                         ;()

(contains? 6 '(1 6))                                                ;T
(contains? 6 '(1 2 3))                                              ;()
(contains? 6 '((1 2) (3 (4 (5 6)))))                                ;T