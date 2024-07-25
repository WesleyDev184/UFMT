import numpy as np
import skfuzzy as fuzz
from skfuzzy import control as ctrl
import tkinter as tk
import matplotlib.pyplot as plt

#pip install scikit-fuzzy

# Definir as variáveis fuzzy
temperatura = ctrl.Antecedent(np.arange(0, 41, 1), 'temperatura')
potencia = ctrl.Consequent(np.arange(0, 101, 1), 'potencia')

# Definir as funções de pertinência para a temperatura
temperatura['baixa'] = fuzz.trimf(temperatura.universe, [0, 0, 20])
temperatura['media'] = fuzz.trimf(temperatura.universe, [15, 25, 35])
#temperatura['media'] = fuzz.gaussmf(temperatura.universe, 25, 5)
temperatura['alta'] = fuzz.trimf(temperatura.universe, [30, 40, 40])

# Definir as funções de pertinência para a potência do ar-condicionado
potencia['baixa'] = fuzz.trimf(potencia.universe, [0, 0, 50])
potencia['media'] = fuzz.trimf(potencia.universe, [30, 50, 70])
potencia['alta'] = fuzz.trimf(potencia.universe, [60, 100, 100])

# Definir as regras fuzzy
regra1 = ctrl.Rule(temperatura['baixa'], potencia['baixa'])
regra2 = ctrl.Rule(temperatura['media'], potencia['media'])
regra3 = ctrl.Rule(temperatura['alta'], potencia['alta'])

# Criar o sistema de controle fuzzy
controle_potencia = ctrl.ControlSystem([regra1, regra2, regra3])
simulador = ctrl.ControlSystemSimulation(controle_potencia)

# Função para ajustar a potência do ar-condicionado
def ajustar_potencia(temp):
    simulador.input['temperatura'] = temp
    simulador.compute()
    return simulador.output['potencia']

# Interface gráfica
def atualizar_potencia():
    temp = escala_temp.get()
    potencia_ac = ajustar_potencia(temp)
    label_resultado.config(text=f'Potência do Ar Condicionado: {potencia_ac:.2f}%')

# Configurar a interface gráfica
root = tk.Tk()
root.title("Controle de Ar Condicionado Fuzzy")

label_temp = tk.Label(root, text="Temperatura (°C):")
label_temp.pack()

escala_temp = tk.Scale(root, from_=0, to=40, orient=tk.HORIZONTAL)
escala_temp.pack()

botao_calcular = tk.Button(root, text="Calcular Potência", command=atualizar_potencia)
botao_calcular.pack()

label_resultado = tk.Label(root, text="Potência do Ar Condicionado: ")
label_resultado.pack()

temperatura_valores = np.arange(0, 41, 1)
potencia_valores = np.zeros_like(temperatura_valores)

for i in range(len(temperatura_valores)):
    simulador.input['temperatura'] = temperatura_valores[i]
    simulador.compute()
    potencia_valores[i] = simulador.output['potencia']


# Plotar as funções de pertinência da temperatura
fig, (ax0, ax1) = plt.subplots(nrows=2, figsize=(8, 6))

ax0.plot(temperatura.universe, temperatura['baixa'].mf, 'b', linewidth=1.5, label='Baixa')
ax0.plot(temperatura.universe, temperatura['media'].mf, 'g', linewidth=1.5, label='Média')
ax0.plot(temperatura.universe, temperatura['alta'].mf, 'r', linewidth=1.5, label='Alta')
ax0.set_title('Funções de Pertinência da Temperatura')
ax0.legend()

# Plotar as funções de pertinência da potência
ax1.plot(potencia.universe, potencia['baixa'].mf, 'b', linewidth=1.5, label='Baixa')
ax1.plot(potencia.universe, potencia['media'].mf, 'g', linewidth=1.5, label='Média')
ax1.plot(potencia.universe, potencia['alta'].mf, 'r', linewidth=1.5, label='Alta')
ax1.set_title('Funções de Pertinência da Potência do Ar Condicionado')
ax1.legend()

plt.tight_layout()
#plt.show()

# Plotar a superfície de decisão
plt.figure()
plt.plot(temperatura_valores, potencia_valores, 'b', linewidth=1.5)
plt.title('Superfície de Decisão')
plt.xlabel('Temperatura (°C)')
plt.ylabel('Potência do Ar Condicionado (%)')
plt.grid(True)
plt.show()

root.mainloop()
