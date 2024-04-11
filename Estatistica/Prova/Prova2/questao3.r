#Dados
dados <- read.csv2(file.choose(), h=T)
dados

# Calcular a media de "Peso" dentro de cada grupo de "Racao"
tapply(dados$Peso, dados$Racao, mean)

# Calcular a desvio padrão de "Peso" dentro de cada grupo de "Racao"
tapply(dados$Peso, dados$Racao, sd)

# Encontrando a Peso minima e maxima
range(dados$Peso)

# Plotar Gráfico de caixa (boxplot) para "Peso" dentro de cada grupo de "Racao"
boxplot(Peso ~ Racao, data=dados, main="Boxplot de Peso por Racao", xlab="Tipos de Racao", ylab="Peso (kg)")

# calcular a analise de variância
res <- aov(Peso ~ Racao, data=dados)

# Mostrar a tabela de ANOVA
anova(res)
