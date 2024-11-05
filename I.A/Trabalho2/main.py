import lightgbm as lgb
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

# Carregar o dataset
data = load_iris()
X = data.data
y = data.target

# Dividir o dataset em treino e teste
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Criar o dataset LightGBM
train_data = lgb.Dataset(X_train, label=y_train)
test_data = lgb.Dataset(X_test, label=y_test, reference=train_data)

# Definir os parâmetros do modelo
params = {
    'objective': 'multiclass',
    'num_class': 3,
    'metric': 'multi_logloss',
    'boosting_type': 'gbdt',
    'num_leaves': 31,
    'learning_rate': 0.05,
    'feature_fraction': 0.9,
    'min_data_in_leaf': 20,  # Ajustar o número mínimo de dados em uma folha
    'max_depth': 5  # Ajustar a profundidade máxima da árvore
}

# Treinar o modelo com early stopping
model = lgb.train(params, train_data, valid_sets=[test_data], num_boost_round=100, callbacks=[lgb.early_stopping(stopping_rounds=10)])

# Fazer previsões
y_pred = model.predict(X_test, num_iteration=model.best_iteration)
y_pred_max = [list(x).index(max(x)) for x in y_pred]

# Avaliar o modelo
accuracy = accuracy_score(y_test, y_pred_max)
print(f'Accuracy: {accuracy}')