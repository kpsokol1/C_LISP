;(PRINT (+ 6 4))     ;10
;(PRINT (- 6 4))     ;2
;(PRINT (- (+ 6 4)(- 6 4)))  ;8
;(PRINT (- 0 4)) ;-4 negative number
;(PRINT (* 6 4)) ;24
;(PRINT (/ 6 4)) ;1
;(PRINT (< 3 4)) ; T
;(PRINT (AND? 3 ()))
;(PRINT (NUMBER? 3)) ;T
;(PRINT (NUMBER? (- (+ 6 4)(- 6 4)))) ;T
;(PRINT (NUMBER? ()))  ;()
;(PRINT (= 3 3)); T
;(PRINT (AND? 6 4)); T
;(PRINT (AND? 6 ())); ()
;(PRINT (AND? (= 3 3) (OR? (= 3 3) (= 4 3)))); T
;(PRINT (OR? (= 3 3) (= 4 3))); T
;(PRINT ((+ 6 4)))     ;10
;(SYMBOL? a) ;T
;(SET a '(NUMBER? (- (+ 6 4)(- 6 4))))
;(SET a ''6)
;(PRINT a) ;6
;(PRINT (+ a 4))
;(PRINT(NUMBER? a)) ;T


;'(1)
;'(1 2 3)
;'( (1 2 3) (2 3 4))
;(SET a ''6)
;(PRINT (NUMBER? a))
;(SET a ''6)
;(PRINT (a)) ;error
;(PRINT a) ;6
;(PRINT (NUMBER? a))

;(PRINT (LIST? '(((1 2) 3) (1 2 3))))
;(PRINT (LIST? '10))
;(PRINT (NUMBER? '10))

;(DEFINE function2 (a)
;    (PRINT a)
;)
;(DEFINE function (a b c)
;    (PRINT a)
;    (PRINT b)
;    (PRINT c)
;    (function 1 2 3)
;    ;(PRINT d)
;)

;(function (+ 6 4) 11 12)

;(SET a (CONS 1 (CONS 2 ())))
;(PRINT (LIST? a))
;(PRINT (LIST? 1))
;(PRINT (LIST? '(((1 2) 3) (1 2 3))))
;(PRINT (NIL? ()))
;(PRINT (NIL? '(((1 2) 3) (1 2 3))))
;(PRINT (NUMBER? '(((1 2) 3) (1 2 3))))  ;try out with function later
;(PRINT (CAR (CDR a)))
;(SET b (CDR a))
;(PRINT (CAR b))

(DEFINE function (a)
    (+ 6 4)
    ;(COND
    ;   (SYMBOL? a) (COND 't 6)
    ;   't (+ 6 4)
    ;)
)
(PRINT (function 'x))          ;6


