familia(
    pessoa(pedro,silva,data(1,abril,1930),empregado(cnn,1000)),
    pessoa(maria,silva,data(20,maio,1933),empregado(bnpp,1230)),
    [
        pessoa(manoel,silva,data(10,setembro,1975),desempregado),
        pessoa(ana,silva,data(12,novembro,1981),empregado(bcc,800))
    ]
).
familia(
    pessoa(paulo,santos,data(1,janeiro,1955),empregado(abb,1200)),
    pessoa(ana,santos,data(1,maio,1955),desempregado),
    [
        pessoa(manoela,santos,data(10,setembro,1981),desempregado),
        pessoa(andre,santos,data(18,novembro,1978),empregado(bb,1100)),
        pessoa(carlos,santos,data(2,fevereiro,1981),empregado(cc,3200))
    ]
).
familia(
    pessoa(eddard,stark,data(31,marco,1948),morto),
    pessoa(catelyn,stark,data(11,agosto,1953),morto),
    [
        pessoa(robb,stark,data(9,dezenbro,1977),morto),
        pessoa(sansa,stark,data(1,junho,1979),empregado(concelheira,11000)),
        pessoa(arya,stark,data(23,janeiro,1991),empregado(assasina,8800)),
        pessoa(bran,stark,data(23,outubro,1993),empregado(vidente,1)),
        pessoa(rickon,stark,data(29,maio,1999),morto)
    ]
).

membro(X,[X|C]).
membro(X, [Y|C]):- membro(X,C).

marido(X) :- familia(X,_,_).
esposa(X) :- familia(_,X,_).
filho(X) :- familia(_,_,Filhos), membro(X,Filhos).

existe(X) :- marido(X); esposa(X); filho(X).

dataNascimento(pessoa(_,_,data(_,_,D),_), D).

data(D) :- existe(X), dataNascimento(X, D).

salario(pessoa(_,_,_,empregado(_,S)),S).
salario(pessoa(_,_,_,desempregado),0).

nomes(X):- existe(pessoa(X,_,_,_)),pessoa(X,Y,_,_).

filhosBydt(Filho, Ano) :- filho(pessoa(Filho, _, data(_, _, Ano), _)).