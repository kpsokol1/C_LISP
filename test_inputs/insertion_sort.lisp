(define insert(x lis) (cond;
	(nil? lis) (cons x ())
	(or? (< x (car lis)) (= x (car lis)))
	(cons x lis)
	't (cons (car lis) (insert x (cdr lis)))
))

(define IShelper(sorted unsorted) (cond
	(nil? unsorted) sorted
	't (IShelper (insert (car unsorted) sorted) (cdr unsorted))
))

(define insertionSort(lis)
	(IShelper () lis)
)

(insertionSort '(2 1 0))                                        ;(0 1 2)
(insertionSort '(2 1 0 100 3 4 65  4 2 1 5 45 3 2))            ;( 0 1 1 2 2 2 3 3 4 4 5 45 65 100 )

;(insertionSort '())
;(IShelper () ())

(insert 7 '(4 5 6))                                             ;( 4 5 6 7 )
;(insert 7 '(4 5 6))                                            ;( 4 5 6 7 )