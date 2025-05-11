import pandas as pd
import json
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsRegressor
from sklearn.ensemble import RandomForestRegressor, GradientBoostingRegressor
from sklearn.linear_model import Ridge
from sklearn.svm import SVR
from sklearn.metrics import r2_score, mean_squared_error


# 1. Ler o arquivo CSV (pular a linha de etiquetas)
nome_arquivo = 'dataset_regressao_etiquetado.csv'
df = pd.read_csv(nome_arquivo, skiprows=1)

# 2. Separar atributos e rótulo
X = df.drop(columns=['target'])
y = df['target']

# 3. Dividir em treino e teste
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# 4. Configuração dos modelos e grids
modelos = {
    'KNN': {
        'pipeline': Pipeline([
            ('scaler', StandardScaler()),
            ('model', KNeighborsRegressor())
        ]),
        'params': {
            'model__n_neighbors': [3, 5, 7, 9, 11],
            'model__weights': ['uniform', 'distance']
        }
    },
    'RandomForest': {
        'pipeline': Pipeline([
            ('model', RandomForestRegressor(random_state=42))
        ]),
        'params': {
            'model__n_estimators': [50, 100, 150, 200, 250],
            'model__max_depth': [None, 10, 20, 30, 40]
        }
    },
    'SVR': {
        'pipeline': Pipeline([
            ('scaler', StandardScaler()),
            ('model', SVR())
        ]),
        'params': {
            'model__kernel': ['rbf', 'linear'],
            'model__C': [0.1, 1, 10],
            'model__epsilon': [0.1, 0.2, 0.5]
        }
    },
    'Ridge': {
        'pipeline': Pipeline([
            ('scaler', StandardScaler()),
            ('model', Ridge())
        ]),
        'params': {
            'model__alpha': [0.1, 1.0, 10.0, 100.0]
        }
    },
    'GradientBoosting': {
        'pipeline': Pipeline([
            ('model', GradientBoostingRegressor(random_state=42))
        ]),
        'params': {
            'model__n_estimators': [50, 100, 150],
            'model__learning_rate': [0.01, 0.1, 0.2],
            'model__max_depth': [3, 5, 7]
        }
    }
}

# 5. Treinar e salvar melhores resultados
melhores_modelos = {}

for nome, cfg in modelos.items():
    print(f"\nTreinando {nome}...")
    grid = GridSearchCV(cfg['pipeline'], cfg['params'], cv=5, scoring='r2', n_jobs=-1)
    grid.fit(X_train, y_train)
    y_pred = grid.predict(X_test)

    r2 = r2_score(y_test, y_pred)
    mse = mean_squared_error(y_test, y_pred)

    print(f"Melhores parâmetros: {grid.best_params_}")
    print(f"R² no teste: {r2:.4f}")
    print(f"MSE no teste: {mse:.4f}")

    melhores_modelos[nome] = {
        'melhores_parametros': grid.best_params_,
        'r2_teste': r2,
        'mse_teste': mse
    }

# 6. Salvar resultados em JSON
with open('melhores_modelos.json', 'w') as f:
    json.dump(melhores_modelos, f, indent=4)

print("\nConfigurações salvas em 'melhores_modelos.json'")