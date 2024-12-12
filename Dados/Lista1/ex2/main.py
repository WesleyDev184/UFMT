import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Carregar os dados
df = pd.read_csv('soja_milho.csv', delimiter=',')

# Caracterizar os tipos dos atributos
print(df.dtypes)
print(' ')

# Converter os preços para float
df['PreçosMilho'] = df['PreçosMilho'].str.replace(',', '.').astype(float)
df['PreçosSoja'] = df['PreçosSoja'].str.replace(',', '.').astype(float)

# Medidas de locação (centralidade)
print("Medidas de Centralidade:")
print(df[['PreçosMilho', 'PreçosSoja']].mean())
print(df[['PreçosMilho', 'PreçosSoja']].median())
print(' ')

# Medidas de dispersão (variabilidade)
print("Medidas de Variabilidade:")
print(df[['PreçosMilho', 'PreçosSoja']].std())
print(df[['PreçosMilho', 'PreçosSoja']].var())
print(' ')

# Analisar o espalhamento das observações
plt.figure(figsize=(12, 6))
plt.subplot(1, 2, 1)
sns.histplot(df['PreçosMilho'], kde=True)
plt.title('Distribuição dos Preços do Milho')

plt.subplot(1, 2, 2)
sns.histplot(df['PreçosSoja'], kde=True)
plt.title('Distribuição dos Preços da Soja')
plt.savefig('distribuicao_precos.png')

# Verificar a presença de outliers com Boxplots
plt.figure(figsize=(12, 6))
plt.subplot(1, 2, 1)
sns.boxplot(y=df['PreçosMilho'])
plt.title('Boxplot dos Preços do Milho')

plt.subplot(1, 2, 2)
sns.boxplot(y=df['PreçosSoja'])
plt.title('Boxplot dos Preços da Soja')
plt.savefig('boxplot_precos.png')

# Análise de correlação e covariância
print("Correlação:")
print(df[['PreçosMilho', 'PreçosSoja']].corr())
print(' ')
print("Covariância:")
print(df[['PreçosMilho', 'PreçosSoja']].cov())