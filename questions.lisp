(define a ())
(define b ()
    (+ 6 0)
)
;---NUMBER?-----------------
'NUMBER_TESTS
(NUMBER? 3) ;T
(NUMBER? (- (+ 6 4)(- 6 4))) ;T
(NUMBER? ())  ;()
(NUMBER? '(1 2 3)) ;()
(NUMBER? '(NUMBER? 1)); ()
(NUMBER? 't); ()
(NUMBER? (a)); ()
;(NUMBER? (b); ;T

;----SYMBOL?------------------
'SYMBOL_TESTS

(SYMBOL? 6) ;()
(SYMBOL? 'hello) ;T
(SYMBOL? '(1 2 3)); ()

(SET list (CONS 1 (CONS 2 (CONS 'a ()))))
(SYMBOL? list); ()
(SYMBOL? (CAR (CDR (CDR list)))); T
(SYMBOL? 'list); T

;----LIST?------------------
'LIST_TESTS

(SET list1 (CONS 1 (CONS 2 (CONS 'a ()))))
(SET list2 '(((1) (2)) (3)))
(Set list3 '((1) (2) (3)))
(SET list4 '(1 2 3 4 5 6))
(SET list5 '((1 2 3) (2)))
(SET list6 '(1 () 3))

(LIST? list1)   ;T
(LIST? (CAR list1)) ;()
(LIST? (CAR (CDR (CDR list1)))) ;()
(LIST? list2)   ;T
(LIST? (CAR list2)) ;T
(LIST? list3)   ;T
(LIST? list4)   ;T
(LIST? list5)   ;T
(LIST? list6)   ;T
(LIST? (CAR (CDR list6))) ;()

;----NIL?------------------
'NIL_TESTS
(NIL? ())                                   ;T
(NIL? 't)                                   ;()
(NIL? (CAR (CDR list6)))                    ;T

;---EQUALS------------------(NOTE EQ? and = are the same operation)
'EQUAL_TESTS
(= 3 3)                                     ;T
(= 2 3)                                     ;()
(EQ? 3 3)                                   ;T

(SET A (CONS 0 (CONS 'a ())))
(SET variable1 (-0 0))
(SET variable2 0)

(EQ? (car (cdr A)) 'a)                       ;T
(EQ? () ())                                  ;T
(EQ? 'a 'a)                                  ;T
(EQ? 'a 'b)                                  ;()
(EQ? 6 4)                                    ;()
(EQ? (b) (b))                                ;T
(EQ? variable1 variable1)                    ;T
(EQ? variable1 variable2)                    ;T

