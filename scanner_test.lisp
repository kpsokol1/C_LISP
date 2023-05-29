(define ascending? (lis) (cond
    (nil? lis) 't
    (nil? (cdr lis)) 't
    (gt? (car lis) (car (cdr lis))) ()
    't (ascending? (cdr lis))
))
