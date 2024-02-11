#Bloco de dados
notas_thales <- c(10,10,5,0,0)
notas_ricardo <- c(10,5,5,5,0)
notas_marta <- c(6,4,4,5,6)

#calcular a media das notas
mean(notas_thales)

mean(notas_ricardo)

mean(notas_marta)

#calcular a mediana das notas
median(notas_thales)

median(notas_ricardo)

median(notas_marta)

#calcular a moda das notas
table(notas_ricardo)

table(notas_marta)

#calcular a amplitude das notas
resT <- range(notas_thales)
rT <- sort(resT, decreasing = TRUE)
rT[1] - rT[2]

resR <- range(notas_ricardo)
rR <- sort(resR, decreasing = TRUE)
rR[1] - rR[2]

resM <- range(notas_marta)
rM <- sort(resM, decreasing = TRUE)
rM[1] - rM[2]

#calcular a variancia das notas
var(notas_thales)

var(notas_ricardo)

var(notas_marta)

#calcular o desvio padão das notas
sd(notas_thales)

sd(notas_ricardo)

sd(notas_marta)

# calcula o coeficiente de variação das notas
cv_thales <- (sd(notas_thales) / mean(notas_thales)) * 100
cv_ricardo <- (sd(notas_ricardo) / mean(notas_ricardo)) * 100
cv_marta <- (sd(notas_marta) / mean(notas_marta)) * 100

cv_thales
cv_ricardo
cv_marta
