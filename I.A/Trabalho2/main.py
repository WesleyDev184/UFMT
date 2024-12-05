import pandas as pd
import numpy as np
import lightgbm as lgb
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt
from sklearn.datasets import fetch_california_housing

# Carregar o dataset
data = fetch_california_housing()
df = pd.DataFrame(data.data, columns=data.feature_names)
df['MedHouseVal'] = data.target

# Exibir as primeiras linhas do dataframe
print('Primeiras linhas do dataframe:')
print(df.head())

# Verificar valores ausentes
print('Valores ausentes:')
print(df.isnull().sum())

# Dividir os dados em conjuntos de treinamento e teste
X = df.drop('MedHouseVal', axis=1)
y = df['MedHouseVal']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Criar o dataset LightGBM
train_data = lgb.Dataset(X_train, label=y_train)
test_data = lgb.Dataset(X_test, label=y_test, reference=train_data)

# Treinar o modelo
model = lgb.train(
    {
    'objective': 'regression',
    'metric': 'rmse',
    'boosting_type': 'gbdt',
    'num_leaves': 31,
    'learning_rate': 0.05,
    'feature_fraction': 0.9
    },
    train_data,
    valid_sets=[test_data],
    num_boost_round=1000,
    callbacks=[lgb.early_stopping(stopping_rounds=10)]
)

# Fazer previsões
y_pred = model.predict(X_test, num_iteration=model.best_iteration)

# Calcular o RMSE
rmse = np.sqrt(mean_squared_error(y_test, y_pred))
print('Métricas do modelo:')
print(f'RMSE: {rmse}')

# Plotar a importância das features e salvar o plot
lgb.plot_importance(model, max_num_features=10)
plt.savefig('feature_importance.png')
plt.close()

# Plotar os valores reais vs previstos e salvar o plot
plt.figure(figsize=(10, 6))
plt.scatter(y_test, y_pred, alpha=0.3)
plt.xlabel('Valores Reais')
plt.ylabel('Valores Previstos')
plt.title('Valores Reais vs Previstos')
plt.savefig('real_vs_predicted.png')
plt.close()