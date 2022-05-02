% Pavlovich, Nicole
% UCD ECS140A Project 4 Prof Jiang 
% Fall 2021


% 1. my_concat(L1, L2, L): meaning the concatenation of two lists L1 and L2 is L.
%  https://www.swi-prolog.org/pldoc/doc/_SWI_/library/lists.pl?show=src#append/3

my_concat([], L, L).                                                            % base case, empty first list                                 
my_concat([ Head | Tail ], L, [ Head | Rest ]) :-  my_concat(Tail, L, Rest).    % recursion


% 2. element_at(X, N, L): meaning the element X is the Nth element in list L.
%  https://www.cs.bham.ac.uk/~pjh/modules/current/02630/lectures/lecture7/lecture7_slides.pdf
%  https://medium.com/@soniayap/prolog-find-nth-element-7589f81b89dd

element_at(H, 0, [H|_]).
element_at(X, K, [_|T]) :- 
    element_at(X, K1, T),
    K is K1 + 1.                % wanted to add cut but causes X, N, List where X isn't given to fail sometimes


% 3. my_reverse(L1, L2): meaning the reverse of list L1 is L2.
%  https://stackoverflow.com/questions/19471778/reversing-a-list-in-prolog
%  https://www.swi-prolog.org/pldoc/doc/_SWI_/library/lists.pl?show=src#reverse/2


my_reverse([], L2, L2, []).                         % helper base
my_reverse( [L | L1], Rightside, L2, [ _ | T]) :- 
    my_reverse(L1, [L | Rightside], L2, T).         % helper (my_reverse/4)
my_reverse( L1, L2 ) :- 
    my_reverse(L1, [], L2, L2).



% 4. my_flatten(L1, L2): Given a list L1, its flattened version is L2.
%  https://cs.union.edu/~striegnk/courses/esslli04prolog/practical.day3.php?s=practical.day3.node7
%  https://www.ic.unicamp.br/~meidanis/courses/mc336/problemas-prolog/

my_flatten( L ,[L]) :- 
    \+ is_list(L).                  % case item is a list
my_flatten([],[]).                  % base case, empty list is flat
my_flatten([LH |LT],L2) :- 
    my_flatten(LH, NewHead), 
    my_flatten(LT, NewTail), 
    append(NewHead,NewTail, L2).    % flatten head, flatten tail, append and check if they're the same as L2


% 5. compress(L1, L2): Given a list L1, L2 is its compressed version by eliminating the duplicates.
%  https://www.tek-tips.com/viewthread.cfm?qid=1602371
%  https://stackoverflow.com/questions/39435709/how-to-remove-duplicates-from-a-list-in-swi-prolog


compress(List, Result):-
    compress(List, [], Result).

compress([], Result, Result).               % base case

compress([H | T], Current, NewT) :-
    member(H, Current), !,                  
    compress(T, Current, NewT).             % cut if Head is a member, continue
compress([H | T], Current, NewT) :-
    append(Current, [H], NewCurrent),
    compress(T, NewCurrent, NewT).          % append and keep iterating