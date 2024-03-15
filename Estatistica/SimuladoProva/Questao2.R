# Dados
alunos <- c(57, 43, 32)
cursos <- c("Letras", "Jornalismo", "Geografia")

# Calculando as porcentagens
porcentagens <- alunos / sum(alunos) * 100

# Criando a tabela
tabela <- data.frame(Curso = cursos, Frequencia_Absoluta = alunos, Porcentagem = porcentagens)

# Imprimindo a tabela
print(tabela)

# Criando o gráfico de barras com as frequências relativas
barplot(porcentagens, names.arg = cursos, xlab = "Curso", ylab = "Porcentagem", main = "Frequência Relativa de Alunos por Curso")
