#Dados
dados <- read.csv2(file.choose(), h=T)
dados

# Calcular a media de "peso" dentro de cada grupo de "maquina"
tapply(dados$peso, dados$maquina, mean)

# Calcular a desvio padrão de "peso" dentro de cada grupo de "maquina"
tapply(dados$peso, dados$maquina, sd)

# Encontrando a peso minima e maxima
range(dados$peso)

# Plotar Gráfico de caixa (boxplot) para "peso" dentro de cada grupo de "maquina"
boxplot(peso ~ maquina, data=dados, main="Boxplot de peso por maquina", xlab="Tipos de maquina", ylab="peso (g)", ylim=c(110, 130))

# calcular a analise de variância
res <- aov(peso ~ maquina, data=dados)

# Mostrar a tabela de ANOVA
anova(res)
