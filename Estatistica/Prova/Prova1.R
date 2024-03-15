#dados
vendas <- c(508,288,477)
marcas <- c("Lacta", "Nestle", "garoto")

#Calculo da Porcentagem
porcentagens <- vendas / sum(vendas) * 100

# Criando a tabela
tabela <- data.frame(Marca = marcas, Numero_Vendas = vendas, Porcentagem = porcentagens)
print(tabela)

#Gafico de Porentagem
barplot(porcentagens, names.arg = marcas, xlab = "Marca", ylab = "Porcentagem", main = "Grafico de Porcentagem")