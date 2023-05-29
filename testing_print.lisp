(SET A 6)
A
(+ 6 4)
(define ascending? (lis) (cond
    (nil? lis) 't
    (nil? (cdr lis)) 't
    (> (car lis) (car (cdr lis))) ()
    't (ascending? (cdr lis))
))

(ascending? '(1 2 3))