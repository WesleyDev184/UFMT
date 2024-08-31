import random
import math

def simulated_annealing_n_queens(n, max_iterations=10000, initial_temperature=100.0, cooling_rate=0.95):
    def generate_random_board(n):
        return [random.randint(0, n-1) for _ in range(n)]
    
    def num_attacking_pairs(board):
        def is_attacking(i, j):
            return (board[i] == board[j] or  # same column
                    abs(board[i] - board[j]) == abs(i - j))  # same diagonal
        
        count = 0
        for i in range(len(board)):
            for j in range(i + 1, len(board)):
                if is_attacking(i, j):
                    count += 1
        return count
    
    current_board = generate_random_board(n)
    current_attacks = num_attacking_pairs(current_board)
    temperature = initial_temperature
    
    for iteration in range(max_iterations):
        if current_attacks == 0:
            print(f"Solucao encontrada para n = {n}: {current_board}")
            return
        
        next_board = list(current_board)
        col = random.randint(0, n - 1)
        row = random.randint(0, n - 1)
        
        if next_board[col] == row:
            continue
        
        next_board[col] = row
        next_attacks = num_attacking_pairs(next_board)
        delta_attacks = next_attacks - current_attacks
        
        if delta_attacks <= 0 or random.random() < math.exp(-delta_attacks / temperature):
            current_board = next_board
            current_attacks = next_attacks
        
        temperature *= cooling_rate
    
    print(f"Nao foi encontrada solução para n = {n} depois de {max_iterations} iteracoes.")
