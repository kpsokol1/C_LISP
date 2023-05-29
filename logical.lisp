(PRINT (AND? 6 4)); T
(PRINT (AND? 6 ())); ()
(PRINT (AND? () ())); ()
(PRINT (OR? 6 ())); T
(PRINT (OR? () ())); ()
(PRINT (AND? (= 3 3) (OR? (= 3 3) (= 4 3)))); T
(PRINT (OR? (= 3 3) (= 4 3))); T