; Pavlovich, Nicole
; ECS 140A Fall 2021 Prof Jiang // Project 3


; Write a function called nth-fib that given a number n, returns the nth number in the Fibonacci sequence.
; fib base cases: F(0) = 0, F(1) = F(2) = 1, fib formula F(n) = F(n-1) + F(n-2)
(defun nth-fib (n)
	(cond ((<= n 1) n)
		  ((>= n 2) (+ (nth-fib (- n 1)) (nth-fib (- n 2))))
	)
)

; Write a function called fib that given a number n, returns the frist n numbers in the Fibonacci sequence.
; Example: (fib 9) should return the list (0 1 1 2 3 5 8 13 21).
(defun fib (n)
	(cond
		((= n 0)	'(0))
		((= n 1)	'(0 1))
		((> n 1)	( fibhelper n ))
	)
)

(defun fibhelper (n &optional (x 0) (y 1))
  	(if (= n 0)
		NIL
		(cons x (fibhelper (- n 1) y (+ x y)))
		;cons 0 (fib 		n-1 	1 	1+1) and so on since this will recurse
	)
)


; Write a function called fib-lt that given a number n, returns all the numbers in the Fibonacci sequence that are less than n.
; Example: (fib-lt 100) should return the list (0 1 1 2 3 5 8 13 21 34 55 89).
(defun fib-lt (n &optional (x '(0 1)) (a 0) (b 1))
	(cond	((= n 0) 						NIL)
			((= n 1)						'(0))
			((<= n (+ a b))					x)
			((fib-lt n (append x (cons (+ a b) '())) b (+ a b)))
	)	
)
