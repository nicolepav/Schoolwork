Pavlovich, Nicole
ECS 140A Fall 2021 Prof Jiang // Project 3


NOTES on fibonacci.lisp
- nth-fib is implemented as a basic recusion and is therefore not big O efficient. Anything larger than nth-fib(30) will probably never finish calculating
- since runtime was not specified in project guidelines, this should not impact performance unless test cases are large
- likewise for fib, also not implemented in runtime efficient manner

NOTES on match.lisp
- algorithm expects that multiple ! symbols in test cases are passed with spaces between them, i.e. `! ! table !` and not `!! table !`

Sources for fibonacci.lisp:
; https://riptutorial.com/common-lisp/example/11082/conditional-constructs
; http://www.lispworks.com/documentation/lw70/CLHS/Body/f_cons.htm
; https://www.tutorialspoint.com/lisp/lisp_optional_parameters.htm
; https://stackoverflow.com/questions/23065846/generating-fibonacci-series-in-lisp-using-recursion


Sources for match.lisp
; https://stackoverflow.com/questions/59845479/common-lisp-pattern-matching
; https://stackoverflow.com/questions/6144435/check-if-item-is-in-a-list-lisp
; https://stackoverflow.com/questions/52241906/check-if-character-is-in-string
; https://www.gnu.org/software/emacs/manual/html_node/eintr/Lisp-Atoms.html
; http://clhs.lisp.se/Body/f_symb_2.htm
; http://clhs.lisp.se/Body/f_rd_fro.htm
; https://stackoverflow.com/questions/11070985/how-do-i-convert-a-string-to-a-symbol-for-use-as-a-key-in-the-lisp-assoc-funct

