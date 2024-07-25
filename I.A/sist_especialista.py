class SistemaEspecialista:
    def __init__(self):
        self.regras = []

    def adicionar_regra(self, antecedente, consequente):
        self.regras.append((antecedente, consequente))

    def inferir(self, sintomas):
        for antecedente, consequente in self.regras:
            if all(sintoma in sintomas for sintoma in antecedente):
                return consequente
        return "Diagnóstico Indeterminado"

# Criar o sistema especialista
sistema = SistemaEspecialista()

# Adicionar regras ao sistema
sistema.adicionar_regra(["febre", "tosse"], "Possível Gripe")
sistema.adicionar_regra(["dor de cabeça", "dor no corpo"], "Possível Dengue")
sistema.adicionar_regra(["dor de garganta", "febre"], "Possível Faringite")

# Testar o sistema com diferentes sintomas
sintomas1 = ["febre", "tosse"]
sintomas2 = ["dor de cabeça", "dor no corpo"]
sintomas3 = ["dor de garganta", "febre"]
sintomas4 = ["dor no corpo"]

print(f"Sintomas: {sintomas1} -> Diagnóstico: {sistema.inferir(sintomas1)}")
print(f"Sintomas: {sintomas2} -> Diagnóstico: {sistema.inferir(sintomas2)}")
print(f"Sintomas: {sintomas3} -> Diagnóstico: {sistema.inferir(sintomas3)}")
print(f"Sintomas: {sintomas4} -> Diagnóstico: {sistema.inferir(sintomas4)}")