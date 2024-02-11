#Obter Dados
dados <- read.csv2(file.choose(), h=T)

#Exibe dados
dados

# Plotar um gráfico de dispersão entre altura e peso
plot(dados$altura, dados$peso,xlim=c(1.5,2.1), xlab = "altura (m)", ylab = "peso (kg)", main = "Dispersão entre Altura e Peso")

# Calcular a correlação entre altura e peso
modelo_regressao <- lm(Peso ~ Altura, data = dados)
print(paste("Correlação entre altura e peso:", correlacao))

# Calcular a equeção da reta de regrassão
modelo_regressao <- lm(peso ~ altura, data = dados)

#Imprime o conteudo de "modelo_regressao"
modelo_regressao

#Plotar a reta de regressão no grafico de dispersão
abline(modelo_regressao) 

# Calcular o peso esperado para um aluno de 1,60 m e 2,10 m
altura1 <- 1.60

peso_esperado <- predict(modelo_regressao, newdata = data.frame(altura = altura1))

print(paste("Peso esperado para um aluno de 1,60 m:", peso_esperado, "kg"))
