# Buscar os dados no arquivo CSV
dados <- read.csv2(file.choose(), h = TRUE)

# Gráfico de dispersão da pressão arterial em relação ao peso
plot(dados$Peso, dados$PA, xlab = "Peso (Kg)", ylab = "Pressão Arterial (mm Hg)", main = "Pressão Arterial por Peso")

# Ajustar uma linha de regressão linear entre a pressão arterial e o peso
ret <- lm(PA ~ Peso, data = dados)
abline(ret, col = "red")

# Coeficiente de correlação entre as variáveis
correlacao <- cor(dados$PA, dados$Peso)
print(paste("Coeficiente de correlação:", correlacao))

# Estimativa da pressão arterial de um cão com 17 kg
pressao_17kg <- predict(ret, newdata = data.frame(Peso = 17))
print(paste("Estimativa da pressão arterial para um cão de 17 kg:", pressao_17kg))

# Estimativa da pressão arterial de um cão com 4 kg
pressao_4kg <- predict(ret, newdata = data.frame(Peso = 4))
print(paste("Estimativa da pressão arterial para um cão de 4 kg:", pressao_4kg))
