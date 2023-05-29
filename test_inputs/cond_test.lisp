;--Basic COND, check for short-ciruiting-------------------------------------------
(cond
    't 'hello
    't ()
)
;HELLO

;--No true conditions--------------------------------------------------------------
(cond
    () 'hello
    () 6
)
;() Return NIL when there are no true conditions

;--Many conditions------------------------------------------------------------------
(cond
    () 1
    () 2
    () 3
    (NIL? 6) 4
    () 5
    () 6
    () 7
    (EQ? 8 8) 8
)
;8

;---Nested conds-------------------------------------------------------------------
(cond
    't (cond
        (= 0 0) (cond
                    't '(1 2 3 4)
                )
        )
)
;( 1 2 3 4 )