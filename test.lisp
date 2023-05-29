(define ascending? (lis) (cond
    (nil? lis) 't
    (nil? (cdr lis)) 't
    (gt? (car lis) (cadr lis)) ()
    't (ascending? (cdr lis))
))
