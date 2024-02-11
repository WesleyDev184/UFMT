# importar o arquivo csv para o objeto "dados"
dados <- read.csv2(file.choose(), h=T)

dados

# calcular a média de "altura" agrupada pela variavel "sexo"
tapply (dados$altura, dados$sexo, mean)

#calcular mediana de "altura" agrupada pela variavel "sexo"
tapply (dados$altura, dados$sexo, median)

#calcular moda de "altura" agrupada pela variavel "sexo"
tapply (dados$altura, dados$sexo, table)

#calcular amplitude de "altura" agrupada pela variavel "sexo"
res <- tapply (dados$altura, dados$sexo, range)

resF <- range(res[1])
rF <- sort(resF, decreasing = TRUE)
rF[1] - rF[2]

resM <- range(res[2])
rM <- sort(resM, decreasing = TRUE)
rM[1] - rM[2]

#calcular variancia de "altura" agrupada pela variavel "sexo"
tapply (dados$altura, dados$sexo, var)

#calcular desvio padrão de "altura" agrupada pela variavel "sexo"
tapply (dados$altura, dados$sexo, sd)

#calcular coeficiente de variação de "altura" agrupada pela variavel "sexo"
tapply (dados$altura, dados$sexo, sd) / tapply (dados$altura, dados$sexo, mean)

#----------Peso----------

# calcular a média de "Peso" agrupada pela variavel "sexo"
tapply (dados$peso, dados$sexo, mean)

#calcular mediana de "Peso" agrupada pela variavel "sexo"
tapply (dados$peso, dados$sexo, median)

#calcular moda de "Peso" agrupada pela variavel "sexo"
tapply (dados$peso, dados$sexo, table)

#calcular amplitude de "Peso" agrupada pela variavel "sexo"
res <- tapply (dados$peso, dados$sexo, range)

resF <- range(res[1])
rF <- sort(resF, decreasing = TRUE)
rF[1] - rF[2]

resM <- range(res[2])
rM <- sort(resM, decreasing = TRUE)
rM[1] - rM[2]

#calcular variancia de "Peso" agrupada pela variavel "sexo"
tapply (dados$peso, dados$sexo, var)

#calcular desvio padrão de "Peso" agrupada pela variavel "sexo"
tapply (dados$peso, dados$sexo, sd)

#calcular coeficiente de variação de "Peso" agrupada pela variavel "sexo"
tapply (dados$peso, dados$sexo, sd) / tapply (dados$peso, dados$sexo, mean)
