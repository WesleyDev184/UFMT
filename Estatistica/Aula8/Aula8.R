#Dados
dados <- read.csv2(file.choose(), h=T)
dados

# Calcular a media de "tempo" dentro de cada grupo de "grupo"
tapply(dados$tempo, dados$grupo, mean)

# Calcular a desvio padrão de "tempo" dentro de cada grupo de "grupo"
tapply(dados$tempo, dados$grupo, sd)

# Encontrando a tempo minima e maxima
range(dados$tempo)

# Plotar Gráfico de caixa (boxplot) para "tempo" dentro de cada grupo de "grupo"
boxplot(tempo ~ grupo, data=dados, main="Boxplot de tempo por grupo", xlab="Grupos", ylab="tempo (Min.)")

# Calcular o teste t independente de tempo=f(grupo)
t.test(tempo ~ grupo, data=dados)