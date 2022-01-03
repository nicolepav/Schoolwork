% Pavlovich, Nicole
% UCD ECS140A Project 4 Prof Jiang 
% Fall 2021

% Define a predicate queens(N, Q) where 
    % N is the size of the chessboard, and Q is a list N numbers such that 
    % the ith number represents the position of the queen in column i. 
% Given a 4×4board, there are two ways to place the 4queens: [2,4,1,3] and [3,1,4,2].

% https://www.swi-prolog.org/pldoc/man?predicate=length/2
% https://gist.github.com/noiano/924ea01419a2dd03e0ba
% https://github.com/Anniepoo/prolog-examples/blob/master/nqueens.pl
% https://www.swi-prolog.org/pldoc/man?predicate=findall/3
% https://www.swi-prolog.org/pldoc/man?predicate=maplist/2
% https://www.youtube.com/watch?v=Ph95IHmRp5M&t=237s
% https://www.metalevel.at/queens/
% https://www.swi-prolog.org/pldoc/man?section=clpfd-n-queens

% ----------------------------------------------------

is_safe( _ ,[], _ ).    % base: anything checked against the empty list is the end of the checker
is_safe( Q, [NextQ|Qtail ], X) :-
    Y is abs(NextQ-Q),              % Y distance between sequential queens
    Y \== X,                        % if Y = X, then queen is on the diagonal, failure (see N Queens video)     
    Q \== NextQ,                    % queens are in diff rows (cols dif by definition)         
    X1 is X + 1,                    % Update X position for next queen  
    is_safe(Q, Qtail, X1).          % check against rest of queens

queens(N, Q) :- 
    length(Q, N),
    doqueens(Q, N).                 % establish Q as length N list of trash, check queen

doqueens([], _).              % base case: all queens are safe 
doqueens( [Q | Qtail], N) :-
    doqueens(Qtail, N),             % recursion, solve from last queen upwards
    numlist(1, N, List),            % make a list from 1 to N https://www.swi-prolog.org/pldoc/man?predicate=numlist/3
    member(Q, List),                % check if queen Q is a member of the generated list
    is_safe(Q, Qtail, 1).           % check queen safety








