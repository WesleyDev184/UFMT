#Dados
dados <- read.csv2(file.choose(), h=T)
dados

# Calcular a media de "altura" dentro de cada grupo de "fertilizante"
tapply(dados$altura, dados$fertilizante, mean)

# Calcular a desvio padrão de "altura" dentro de cada grupo de "fertilizante"
tapply(dados$altura, dados$fertilizante, sd)

# Encontrando a Altura minima e maxima
range(dados$altura)

# Plotar Gráfico de caixa (boxplot) para "altura" dentro de cada grupo de "fertilizante"
boxplot(altura ~ fertilizante, data=dados, main="Boxplot de Altura por Fertilizante", xlab="Tipos de Fertilizante", ylab="Altura (cm)", ylim=c(45, 65))

# Calcular o teste t independente de alturaa=f(fertilizante0
t.test(altura ~ fertilizante, data=dados)