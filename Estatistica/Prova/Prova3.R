#Dados
idades <- c(60,22,24,39,18,20,19,20,21,27,23,24,20,22,24)

#Media
media <- mean(idades)

#Mediana
mediana <- median(idades)

#Moda
moda <- names(sort(table(idades), decreasing = TRUE))

#Amplitude
ampli <- max(idades) - min(idades)

#variância
vari <- var(idades)

#Desvio padrão
dp <- sd(idades)

#Coeficiente de variação
cv <- dp/media

#print
print(paste("Media: ", media))
print(paste("Mediana: ", mediana))
print(paste("Moda: ", moda[1],moda[2],moda[3]))
print(paste("Amplitude: ", ampli))
print(paste("Variância: ", vari))
print(paste("Desvio Padrão: ", dp))
print(paste("Coeficiente de Variação: ", cv))