from collections import deque

def imprime_estado(estado):
    for linha in range(3):
        print(' '.join(map(str, estado[linha*3:linha*3+3])))

def gera_sucessores(estado):
    sucessores = []
    indice_vazio = estado.index(0)
    movimentos = [(3, -3), (1, -1), (-1, 1), (-3, 3)]  # Cima, Esquerda, Direita, Baixo
    for mov in movimentos:
        novo_indice = indice_vazio + mov[0]
        if 0 <= novo_indice < 9:
            novo_estado = estado.copy()
            novo_estado[indice_vazio], novo_estado[novo_indice] = novo_estado[novo_indice], novo_estado[indice_vazio]
            sucessores.append(novo_estado)
    return sucessores

def busca_largura(estado_inicial, estado_final):
    fila = deque([(estado_inicial, [])])
    visitados = set()

    while fila:
        estado, caminho = fila.popleft()
        visitados.add(tuple(estado))

        if estado == estado_final:
            return caminho
        
        for sucessor in gera_sucessores(estado):
            if tuple(sucessor) not in visitados:
                fila.append((sucessor, caminho + [sucessor]))

    return None
    
import random

def random_walk(estado_inicial, estado_final):
    estado_atual = estado_inicial.copy()
    caminho = [estado_atual]

    while estado_atual != estado_final:
        sucessores = gera_sucessores(estado_atual)
        estado_atual = random.choice(sucessores)
        caminho.append(estado_atual)

    return caminho

def busca_profundidade(estado_inicial, estado_final):
    pilha = [(estado_inicial, [])]  # (estado, caminho)
    visitados = set()

    while pilha:
        estado, caminho = pilha.pop()
        visitados.add(tuple(estado))

        if estado == estado_final:
            return caminho

        for sucessor in gera_sucessores(estado):
            if tuple(sucessor) not in visitados:
                pilha.append((sucessor, caminho + [sucessor]))

    return None


# Exemplo de uso
estado_inicial = [1, 2, 3, 4, 0, 5, 7, 8, 6]
#estado_inicial = [7, 2, 4, 5, 0, 6, 8, 3, 1]
estado_final = [1, 2, 3, 4, 5, 6, 7, 8, 0]

#resultado = busca_largura(estado_inicial, estado_final)
resultado = busca_profundidade(estado_inicial, estado_final)
#resultado = random_walk(estado_inicial, estado_final)



if resultado:
    #for estado in resultado:
    #    imprime_estado(estado)
    #    print()        
    print("Numero de estados explorados:", len(resultado))
else:
    print("Solução não encontrada.")


