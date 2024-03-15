# Alturas dos alunos
alturas <- c(1.75, 1.45, 1.80, 1.61, 1.55, 1.66, 1.76, 1.55)

# Média
media <- mean(alturas)

# Mediana
mediana <- median(alturas)

# Moda
moda <- names(sort(table(alturas), decreasing = TRUE))[1]

# Amplitude
amplitude <- max(alturas) - min(alturas)

# Variância
variancia <- var(alturas)

# Desvio-padrão
desvio_padrao <- sd(alturas)

# Coeficiente de variação
coef_variacao <- desvio_padrao / media * 100

# Imprimir resultados
print(paste("Média:", media))
print(paste("Mediana:", mediana))
print(paste("Moda:", moda))
print(paste("Amplitude:", amplitude))
print(paste("Variância:", variancia))
print(paste("Desvio-padrão:", desvio_padrao))
print(paste("Coeficiente de variação:", coef_variacao))
