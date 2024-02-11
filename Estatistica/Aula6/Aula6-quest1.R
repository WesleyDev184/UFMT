#Get Dados
dados <- read.csv2(file.choose(), h=T)

#Exibe dados
dados

#Plotar o histograma da variavel "Altura" contida no obketo dados
hist(dados$altura, xlab = "altura (m)", ylab = "Frequência", main = "Histograma da Altura")