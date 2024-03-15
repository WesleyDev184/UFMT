progenitor(joao,jose).
progenitor(joao,ana).
progenitor(maria,jose).
progenitor(jose,julia).
progenitor(jose,iris).
progenitor(iris,jorge).

masculino(joao).
masculino(jose).
masculino(jorge).
feminino(maria).
feminino(julia).
feminino(ana).
feminino(iris).

filho(X,Y):- progenitor(Y,X).
mae(X,Y):- progenitor(X,Y),feminino(X).
pai(X,Y):- progenitor(X,Y),masculino(X).
avo(X,Z):- progenitor(X,Y),progenitor(Y,Z),masculino(X).
irma(X,Y):- progenitor(Z,X),progenitor(Z,Y),feminino(X).

antepassado(X,Z):- progenitor(X,Z).
antepassado(X,Y):- progenitor(X,Z),antepassado(Z,Y).