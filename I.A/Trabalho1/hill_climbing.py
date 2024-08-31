import random

def hill_climbing_n_queens(n, max_steps=10000):
    
    def count_attacks(board):
        count = 0
        for row1 in range(n):
            for row2 in range(row1 + 1, n):
                if board[row1] == board[row2] or abs(board[row1] - board[row2]) == abs(row1 - row2):
                    count += 1
        return count
    
    def create_neighbor(board):
        nb = board[:]
        row1, row2 = random.sample(range(n), 2)
        nb[row1], nb[row2] = nb[row2], nb[row1]
        return nb

    board = list(range(n))
    random.shuffle(board)
    iteracoes = 0
    
    attacks = count_attacks(board)
    
    for _ in range(max_steps):
        iteracoes += 1
        nb = create_neighbor(board)
        nb_attacks = count_attacks(nb)
        
        # Se o vizinho tiver menos conflitos, atualiza o tabuleiro atual
        if nb_attacks < attacks:
            board = nb
            attacks = nb_attacks
        
        # Se a solução estiver livre de conflitos, termina a busca
        if attacks == 0:
            break
    
    if attacks == 0:
        print(f"Solução encontrada para n = {n} com {iteracoes} iterações: {board} (Ataques: {attacks})")
    else:
        print(f"Não foi encontrada solução para n = {n} após {iteracoes} iterações.")
        print(f"Melhor solução encontrada: {board} (Ataques: {attacks})")
