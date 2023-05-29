(PRINT (EQ? 6 5)) ;()
(PRINT (EQ? 6 6)) ;T
(PRINT (EQ? 'a 6)) ;()
(PRINT (EQ? 'a 'a)) ;T
(PRINT (EQ? 'a 'ab)) ;()

(SET A (CONS 0 (CONS 'a ())))

(print (EQ? (car (cdr A)) 'a)) ;T
(PRINT (EQ? () ())) ;()

;test =
(PRINT (= 6 5)) ;()
(PRINT (= 6 6)) ;T
(PRINT (= 'a 6)) ;()
(PRINT (= 'a 'a)) ;T
(PRINT (= 'a 'ab)) ;()

(SET A (CONS 0 (CONS 'a ())))

(print (= (car (cdr A)) 'a)) ;T
(PRINT (= () ())) ;()