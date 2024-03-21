pop(eua,203).
pop(india,800).
pop(brasil,108).

area(eua,8).
area(india,3).
area(brasil, 8 ).

dens(X,Y) :- pop(X,P),area(X,A), Y is P/A.

fatorial(0,1).
fatorial(X,Y) :- X1 is X-1,fatorial(X1, Y1),Y is X*Y1.