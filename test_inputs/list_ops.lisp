(define median (a b c)
	(cond
		(and? (< a b) (> b c)) c
		(and? (> a b) (< b c)) a
		't b
	)
)

(median 1 1 2)