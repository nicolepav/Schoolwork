; Pavlovich, Nicole
; ECS 140A Fall 2021 Prof Jiang // Project 3

; An assertion is a list of strings, a pattern is a list of atoms that may contain ! or *
; ! means matching zero or more atoms.
; * means matching zero or more characters inside an atom.

; Write a function called match in the match.lisp file that given a pattern and assertion, determines if they match


; Main match function
(defun match (pattern assertion)
	(cond
		( ( atom pattern) 			(eq pattern assertion)) 			; if pattern single atom, return equality check
		( ( position #\* (symbol-name (first pattern))	)				; if atom contains or is *
			( if (eq assertion '())										; make sure that there is something from assertion to match it with
				NIL
				(if (atommatch (first pattern) (first assertion))		; attempt to match pattern with first atom in assertion
					(match (rest pattern) (rest assertion))				; if success, continue matching rest of pattern & assertion
					NIL													; else match failed, terminate
				)
			)
		)
		( ( eq (first pattern)	'!)										; if ! encountered					
			(cond 														; attempt to match rest of pattern to assertion
				( (match (rest pattern) assertion) )	
				( assertion 	(match pattern (rest assertion)))	
			)
		)
		; if no !, attempt match first, if succeeds attempt match rest
		( (match (first pattern)(first assertion))	(match (rest pattern)(rest assertion)) )			
	)
)

; Helper function for matching within an atom before continuing with the entire assertion
(defun atommatch (subpattern subassertion)
	(cond 
		( (= (length (string subpattern)) '1)							; if pattern only length 1, check for * or compare if not *
			(if (eq subpattern '*)
				t														; account for subassertion being NIL when pattern is longer
				(eq subpattern subassertion)
			)
		)
		; if * encountered
		( ( eq (read-from-string (subseq (string subpattern) 0 1) NIL)	'*)	
			(cond
				( (atommatch (read-from-string (subseq (string subpattern) 1) NIL) subassertion ) ) 
				( subassertion ( atommatch subpattern (read-from-string (subseq (string subassertion) 1) NIL) ) )	
			) 
		)
		; if no *, attemot atommatch char, if succeeds atommatch rest
		( (atommatch (read-from-string (subseq (string subpattern) 0 1) NIL )(read-from-string (subseq (string subassertion) 0 1) NIL))	
			(atommatch (read-from-string (subseq (string subpattern) 1) NIL )(read-from-string (subseq (string subassertion) 1) NIL)) 
		)	
	)	
)
