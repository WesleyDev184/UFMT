  # Buscar os dados no arquivo CSV
  dados <- read.csv2(file.choose(), h = TRUE)

  dados

  # Calcular a media da Marca dentro da coluna QTD
  tapply(dados$QTD,dados$Marca, mean)

  #Calcular o desvio padrão da QTD dentro da coluna QTD
  tapply(dados$QTD,dados$Marca, sd)

  #plotar o gráfico de caixa da QTD em relação a QTD
  boxplot(dados$QTD ~ dados$Marca, xlab = "QTD", ylab = "Marca", main = "Marca por QTD de Sódio")

  #Calcular o test T independente
  t.test(dados$QTD ~ dados$Marca)
