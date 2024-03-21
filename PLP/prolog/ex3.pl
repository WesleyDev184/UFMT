construir(X,Y,[X|Y]).

membro(X,[X|C]).
membro(X, [X|C]):- membro(X,C).

concat([],L,L).
concat([X|L1],L2,[X|L3]):- concat(L1,L2,L3).            

remove(X,L,L1).