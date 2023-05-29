(SET A (CONS 0 (CONS 'a ())))

;(define ascending? (lis) (cond
;    (nil? lis) 't
;    (nil? (cdr lis)) 't
;    (> (car lis) (car (cdr lis))) ()
;    't (ascending? (cdr lis))
;))

;(PRINT (ascending? '(1 3 2)))
;(PRINT (ascending? A))
;(PRINT (car (cdr A)))

;(define function2 ()
;    (PRINT (+ 6 (car A)))
;)

;(function2)

(print (EQ? (car (cdr A)) 'a))
(PRINT (EQ? () ()))
(PRINT (SYMBOL? (car (cdr A))))
(PRINT (LIST? (CDR A)))

;fixme make error if trying to print full list