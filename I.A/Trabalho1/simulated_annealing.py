import numpy as np
import random
import math

def simulated_annealing_n_queens(n, max_iterations=10000, initial_temperature=100.0, cooling_rate=0.95):
    def generate_random_board(n):
        return np.random.randint(0, n, n)
    
    def num_attacking_pairs(board):
        row_conflicts = np.bincount(board)
        
        diag1_conflicts = np.bincount(np.arange(n) - board + (n - 1))
        diag2_conflicts = np.bincount(np.arange(n) + board)
        
        row_attacks = np.sum(row_conflicts * (row_conflicts - 1)) // 2
        diag1_attacks = np.sum(diag1_conflicts * (diag1_conflicts - 1)) // 2
        diag2_attacks = np.sum(diag2_conflicts * (diag2_conflicts - 1)) // 2
        
        return row_attacks + diag1_attacks + diag2_attacks
    
    current_board = generate_random_board(n)
    current_attacks = num_attacking_pairs(current_board)
    temperature = initial_temperature
    iteracoes = 0
    
    for _ in range(max_iterations):
        iteracoes += 1
        if current_attacks == 0:
            print(f"Solução encontrada para n = {n} com {iteracoes} iterações: {current_board} (ataques: {current_attacks})")
            return
        
        next_board = current_board.copy()
        col = random.randint(0, n - 1)
        row = random.randint(0, n - 1)
        
        if next_board[col] == row:
            continue
        
        next_board[col] = row
        next_attacks = num_attacking_pairs(next_board)
        delta_attacks = next_attacks - current_attacks
        
        # Limitar o valor de delta_attacks / temperature para evitar overflow
        if delta_attacks <= 0 or random.random() < math.exp(-min(delta_attacks / temperature, 700)):  # Limite 700 para evitar overflow
            current_board = next_board
            current_attacks = next_attacks
        
        temperature *= cooling_rate
    
    print(f"Não foi encontrada solução para n = {n} após {iteracoes} iterações.")    
    print(f"Melhor solução encontrada: {current_board} (Ataques: {current_attacks})")
