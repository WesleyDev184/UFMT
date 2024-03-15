#Dados 
volt <- c(0.66,1.55,1.98,2.64,3.30,3.96,4.51,3.28,5.94,6.60)

corr <- c(7.32,12.22,16.34,23.01,28.06,33.39,34.12,39.21,44.50,47.48)

# Ajuste da reta de regressão
fit <- lm(corr ~ volt)

# Plotando o gráfico com a linha de regressão
plot(volt, corr, main = "Gráfico de Corrente vs Tensão",
     xlab = "Tensão", ylab = "Corrente", pch = 16, col = "blue")
abline(fit, col = "red") # Adiciona a linha de regressão ao gráfico

# Calculando a correlação
correlation <- cor(volt, corr)

# Exibindo a correlação
print(correlation)

# Voltagens para previsão
voltagens <- c(9.05, 2.70)

# Previsão da corrente para as voltagens fornecidas
corrente_esperada <- predict(fit, data.frame(volt = voltagens))

# Exibindo a corrente esperada
print(corrente_esperada)