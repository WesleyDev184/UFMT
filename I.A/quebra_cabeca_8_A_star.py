from collections import deque
import heapq

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

def heuristica(estado, estado_final):
    """Calcula o número de peças fora do lugar."""
    return sum(1 for i in range(9) if estado[i] != estado_final[i])
    
def busca_gulosa(estado_inicial, estado_final):
    """Implementa a busca gulosa."""
    aberto = [(heuristica(estado_inicial, estado_final), estado_inicial, [])]  # (h, estado, caminho)
    fechado = set()

    while aberto:
        _, estado, caminho = heapq.heappop(aberto)
        fechado.add(tuple(estado))

        if estado == estado_final:
            return caminho

        for sucessor in gera_sucessores(estado):
            if tuple(sucessor) not in fechado:
                h = heuristica(sucessor, estado_final)
                heapq.heappush(aberto, (h, sucessor, caminho + [sucessor]))

    return None


def a_star(estado_inicial, estado_final):
    """Implementa o algoritmo A*."""
    aberto = [(0, estado_inicial, [])]  # (f, estado, caminho)
    fechado = set()

    while aberto:
        f, estado, caminho = heapq.heappop(aberto)
        fechado.add(tuple(estado))

        if estado == estado_final:
            return caminho

        for sucessor in gera_sucessores(estado):
            if tuple(sucessor) not in fechado:
                g = len(caminho) + 1  # Custo do caminho até o sucessor
                h = heuristica(sucessor, estado_final)
                f = g + h
                heapq.heappush(aberto, (f, sucessor, caminho + [sucessor]))

    return None



# Exemplo de uso
#estado_inicial = [1, 2, 3, 4, 0, 5, 7, 8, 6]
estado_inicial = [7, 2, 4, 5, 0, 6, 8, 3, 1]
estado_final = [1, 2, 3, 4, 5, 6, 7, 8, 0]

resultado = busca_gulosa(estado_inicial, estado_final)
print("Busca gulosa")
print("Numero de estados explorados:", len(resultado))

resultado = a_star(estado_inicial, estado_final)
print("A star")
print("Numero de estados explorados:", len(resultado))


