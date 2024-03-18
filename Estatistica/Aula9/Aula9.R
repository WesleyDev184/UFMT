#Dados
dados <- read.csv2(file.choose(), h=T)

# Exibir os dados lidos
print(dados)

# Plotar Gráfico de caixa (boxplot) para "nota" dentro de cada grupo de "teste"
boxplot(nota ~ teste, data=dados, main="Boxplot de nota por teste", xlab="Testes", ylab="Nota")

# Calcular a média de "nota" dentro de cada grupo de "teste"
media<-tapply(dados$nota, dados$teste, mean)
print(media)

# Calcular o desvio padrão de "nota" dentro de cada grupo de "teste"
dp <- tapply(dados$nota, dados$teste, sd)
print(dp)

# Encontrar a nota mínima e máxima
minMax <- range(dados$nota)
print(minMax)

# Calcular o teste t pareado de nota=f(teste)
test<-t.test(nota ~ teste, data=dados, paired=T)
print(test)