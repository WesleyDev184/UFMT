progenitor(manuel,fernando).
progenitor(manuel,marta).
progenitor(maria,fernando).
progenitor(maria,marta).

progenitor(anibal,diana).
progenitor(anibal,francisco).
progenitor(anibal,alvaro).
progenitor(alzira,diana).
progenitor(alzira,francisco).
progenitor(alzira,alvaro).

progenitor(jose,delfina).
progenitor(marta,delfina).

progenitor(fernando,carlos).
progenitor(fernando,paulo).
progenitor(diana,carlos).
progenitor(diana,paulo).

progenitor(alvaro,sara).
progenitor(celia,sara).

progenitor(zulmira,ricardo).
progenitor(zulmira,daniel).
progenitor(carlos,ricardo).
progenitor(carlos,daniel).

progenitor(paulo,adriana).
progenitor(paulo,samuel).
progenitor(fatima,adriana).
progenitor(fatima,samuel).

homem(manuel).
homem(anibal).
homem(jose).
homem(fernando).
homem(francisco).
homem(alvaro).
homem(carlos).
homem(paulo).
homem(ricardo).
homem(daniel).
homem(samuel).
mulher(maria).
mulher(alzira).
mulher(marta).
mulher(diana).
mulher(celia).
mulher(delfina).
mulher(zulmira).
mulher(fatima).
mulher(sara).
mulher(adriana).

casados(manuel,maria).
casados(anibal,alzira).
casados(jose,marta).
casados(fernando,diana).
casados(alvaro,celia).
casados(carlos,zulmira).
casados(paulo,fatima).

filho(X,Y):- progenitor(Y,X),homem(x).
filha(X,Y):- progenitor(Y,X),mulher(X).
mae(X,Y):- progenitor(X,Y),mulher(X).
pai(X,Y):- progenitor(X,Y),homem(X).
irma(X,Y):- progenitor(Z,X), progenitor(Z,Y), mulher(X), X \= Y.
irmao(X,Y):- progenitor(Z,X), progenitor(Z,Y), homem(X), X \= Y.
irmaos(X,Y):- progenitor(Z,X), progenitor(Z,Y).
avo(X,Z):- progenitor(X,Y),progenitor(Y,Z),homem(X).
avoh(X,Z):- progenitor(X,Y),progenitor(Y,Z),mulher(X).
neto(X,Y):- progenitor(Y,Z),progenitor(Z,X),homem(X).
neta(X,Y):- progenitor(Y,Z),progenitor(Z,X),mulher(X).
tio(X,Y):- progenitor(Z,Y),irmao(X,Z),homem(X).
tia(X,Y):- progenitor(Z,Y),irma(X,Z),mulher(X).
sobrinho(X,Y):- progenitor(Z,X),irmaos(Z,Y),homem(X).
sobrinha(X,Y):- progenitor(Z,X),irmaos(Z,Y),mulher(X).
primo(X,Y):- progenitor(Z,X),progenitor(W,Y),irmaos(Z,W),homem(X).
prima(X,Y):- progenitor(Z,X),progenitor(W,Y),irmaos(Z,W),mulher(X).
cunhado(X,Y):- casados(X,Z),irmao(Z,Y),homem(X).
cunhada(X,Y):- casados(X,Z),irma(Z,Y),mulher(X).

descendente(X,Z):- progenitor(X,Z).
descendente(X,Z):- progenitor(X,Y),descendente(Y,Z).

ascendente(X,Z):- progenitor(Z,X).
ascendente(X,Z):- progenitor(Y,X),ascendente(Y,Z).