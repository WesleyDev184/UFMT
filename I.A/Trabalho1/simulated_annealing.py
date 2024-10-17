import numpy as np
import random
import math

def simulated_annealing_n_queens(n: int, max_iterations: int = 10000, initial_temperature: float = 100.0, cooling_rate: float = 0.95) -> None:
    def generate_random_board(n: int) -> np.ndarray:
        return np.random.randint(0, n, n)
    
    def num_attacking_pairs(board: np.ndarray) -> int:
        row_conflicts = np.bincount(board)
        
        diag1_conflicts = np.bincount(np.arange(n) - board + (n - 1))
        diag2_conflicts = np.bincount(np.arange(n) + board)
        
        row_attacks = np.sum(row_conflicts * (row_conflicts - 1)) // 2
        diag1_attacks = np.sum(diag1_conflicts * (diag1_conflicts - 1)) // 2
        diag2_attacks = np.sum(diag2_conflicts * (diag2_conflicts - 1)) // 2
        
        return int(row_attacks + diag1_attacks + diag2_attacks)
    
    current_board: np.ndarray = generate_random_board(n)
    current_attacks: int = num_attacking_pairs(current_board)
    temperature: float = initial_temperature
    iteracoes: int = 0
    
    for _ in range(max_iterations):
        iteracoes += 1
        if current_attacks == 0:
            print(f"Solução encontrada para n = {n} com {iteracoes} iterações: Ataques: {current_attacks}")
            return
        
        next_board: np.ndarray = current_board.copy()
        col: int = random.randint(0, n - 1)
        row: int = random.randint(0, n - 1)
        
        if next_board[col] == row:
            continue
        
        next_board[col] = row
        next_attacks: int = num_attacking_pairs(next_board)
        delta_attacks: int = next_attacks - current_attacks
        
        # Limitar o valor de delta_attacks / temperature para evitar overflow
        if delta_attacks <= 0 or random.random() < math.exp(-min(delta_attacks / temperature, 700)):  # Limite 700 para evitar overflow
            current_board = next_board
            current_attacks = next_attacks
        
        temperature *= cooling_rate
    
    print(f"Não foi encontrada solução para n = {n} após {iteracoes} iterações.")    
    print(f"Melhor solução encontrada: Ataques: {current_attacks}")
