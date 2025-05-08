import numpy as np
import pandas as pd
import csv

def gerar_dataset_sintetico_em_csv_com_etiquetas(nome_arquivo, n_amostras=1_000_000, seed=42):
  np.random.seed(seed)

  # 1. Features base (10)
  base = np.random.randn(n_amostras, 10)

  # 2. Features derivadas (10)
  derivadas = np.empty((n_amostras, 10))
  derivadas[:, 0] = base[:, 0] * 2 + np.sin(base[:, 1])
  derivadas[:, 1] = base[:, 2] * base[:, 3]
  derivadas[:, 2] = np.log(np.abs(base[:, 4]) + 1e-5)
  derivadas[:, 3] = base[:, 5] + np.random.normal(0, 0.1, n_amostras)
  derivadas[:, 4] = base[:, 6] ** 2
  derivadas[:, 5] = np.cos(base[:, 7]) * base[:, 8]
  derivadas[:, 6] = np.tanh(base[:, 9])
  derivadas[:, 7:10] = np.random.randn(n_amostras, 3)

  # 3. Features irrelevantes (10)
  irrelevantes = np.random.uniform(-10, 10, size=(n_amostras, 10))

  # 4. Concatenação das features
  X = np.hstack([base, derivadas, irrelevantes])

  # 5. Target y
  pesos = np.random.uniform(-2, 2, size=5)
  y = (pesos[0] * base[:, 0] +
  pesos[1] * base[:, 3] +
  pesos[2] * derivadas[:, 0] +
  pesos[3] * derivadas[:, 2] +
  pesos[4] * np.sin(base[:, 5])) + \
  np.random.normal(0, 1.0, n_amostras)

  # 6. Montar DataFrame
  colunas = [f"f{i}" for i in range(30)]
  df = pd.DataFrame(X, columns=colunas)
  df['target'] = y

  # 7. Etiquetas
  etiquetas = (
  ["base"] * 10 +
  ["derivada"] * 10 +
  ["irrelevante"] * 10 +
  ["target"]
  )

  # 8. Salvar manualmente com etiqueta como primeira linha
  with open(nome_arquivo, 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(etiquetas) # Linha de etiquetas
    writer.writerow(df.columns) # Cabeçalhos reais
    writer.writerows(df.values) # Dados

  print(f"Dataset com etiquetas salvo em: {nome_arquivo}")

# Uso:
gerar_dataset_sintetico_em_csv_com_etiquetas("dataset_regressao_etiquetado.csv")