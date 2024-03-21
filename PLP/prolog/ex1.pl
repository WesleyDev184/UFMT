progenitor(joao,jose).
progenitor(joao,ana).
progenitor(maria,jose).
progenitor(jose,julia).
progenitor(jose,iris).
progenitor(iris,jorge).

nasceu(joao,1910).
nasceu(jose,1930).
nasceu(ana, 1934).
nasceu(maria,1914).
nasceu(julia,1950).
nasceu(iris,1955).
nasceu(jorge,1975).

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