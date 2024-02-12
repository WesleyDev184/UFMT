import matplotlib.pyplot as plt
import math

# Função para calcular o valor de dx
def dx(a, b, N):
    return (b - a) / N

# Função para calcular a integral usando o método do trapézio
def Trapezio(f, a, b, N):
    h = dx(a, b, N)
    integral = (f(a) + f(b)) / 2 + sum(f(a + i * h) for i in range(1, N))
    return integral * h

# Função para calcular a integral usando o método do ponto médio
def PontoMedio(f, a, b, N):
    h = dx(a, b, N)
    integral = sum(f(a + i * h + h/2) for i in range(N))
    return integral * h

# Definição da função f(x) que deseja integrar
def f(x):
    parte_1 = math.sqrt((math.log(x))**2 - 9)
    parte_2 = x * math.log(x)
    resultado = parte_1 / parte_2
    return resultado

# Define o valor máximo de N
Nmax = 40

# Limite inferior e superior da integral
a = 21
b = 100

with open('resultados.txt', 'w') as file:
    pass # Cria um arquivo vazio

# Loop sobre diferentes valores de N
with open('resultados.txt', 'w') as file:
    for N in range(1, Nmax + 1):
        Sn = 0
        Tn = 0
        # Loop para calcular a integral usando ponto médio e trapézio
        for i in range(1, N + 1):
            Sn = PontoMedio(f, a, b, i)
            Tn = Trapezio(f, a, b, i)
        
        # Escreve os resultados no arquivo
        file.write(f'{N} {Sn} {Tn}\n')

# Lê os resultados do arquivo para plotagem do gráfico
valores_n = []
resultados_sn = []
resultados_tn = []

with open('resultados.txt', 'r') as file:
    for line in file:
        data = line.split()
        valores_n.append(int(data[0]))
        resultados_sn.append(float(data[1]))
        resultados_tn.append(float(data[2]))

# Plotagem do gráfico
plt.figure(figsize=(10, 6))
plt.plot(valores_n, resultados_sn, label='Método do Ponto Médio', marker='o')
plt.plot(valores_n, resultados_tn, label='Método do Trapézio', marker='s')
plt.grid(True)
plt.xlabel('N')
plt.ylabel('Integral Aproximada')
plt.title('Integração Numérica')
plt.legend(loc='lower right')

# Salva o gráfico em um arquivo PDF
plt.savefig('grafico_integral.pdf')
