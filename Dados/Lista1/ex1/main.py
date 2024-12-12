import csv
from statistics import mean, median, stdev, variance

# Carregar o arquivo CSV
data = []
with open('data.csv', newline='', encoding='utf-8') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    next(reader)  # Pular o cabeçalho
    for row in reader:
        data.append([row[0], float(row[1].replace(',', '.')), float(row[2].replace(',', '.'))])

# Inspecionar os dados
print("Primeiras linhas dos dados:")
for row in data[:5]:
    print(row)

# Caracterizar os tipos de atributos
print("\nTipos de atributos:")
print("Mes/Ano: String")
print("Estadual 1: Float")
print("Estadual 2: Float")

# Calcular medidas de centralidade
estadual = [row[1] for row in data]
nacional = [row[2] for row in data]

print("\nMedidas de Centralidade:")
print(f"Média Estadual: {mean(estadual):.2f}")
print(f"Mediana Estadual: {median(estadual):.2f}")
print(f"Média Nacional: {mean(nacional):.2f}")
print(f"Mediana Nacional: {median(nacional):.2f}")

# Calcular medidas de dispersão
print("\nMedidas de Dispersão:")
print(f"Desvio Padrão Estadual: {stdev(estadual):.2f}")
print(f"Variância Estadual: {variance(estadual):.2f}")
print(f"Desvio Padrão Nacional: {stdev(nacional):.2f}")
print(f"Variância Nacional: {variance(nacional):.2f}")

def association(x, y):
    n = len(x)
    sum_x = sum(x)
    sum_y = sum(y)
    sum_x_sq = sum([i**2 for i in x])
    sum_y_sq = sum([i**2 for i in y])
    psum = sum([x[i] * y[i] for i in range(n)])
    num = psum - (sum_x * sum_y / n)
    den = ((sum_x_sq - sum_x**2 / n) * (sum_y_sq - sum_y**2 / n))**0.5
    if den == 0: return 0
    return num / den

correlation = association(estadual, nacional)
print("\nMedidas de Associação:")
print(f"Correlação de Pearson entre Estadual e Nacional: {correlation}")