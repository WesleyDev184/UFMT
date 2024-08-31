import random

def hill_climbing_n_queens(n, max_iterations=10000, max_sideways_moves=100):
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
    
    def get_best_neighbor(board):
        min_attacks = num_attacking_pairs(board)
        best_board = list(board)
        
        for col in range(n):
            original_row = board[col]
            for row in range(n):
                if original_row != row:
                    board[col] = row
                    attacks = num_attacking_pairs(board)
                    if attacks < min_attacks:
                        min_attacks = attacks
                        best_board = list(board)
            board[col] = original_row
        
        return best_board, min_attacks
    
    current_board = generate_random_board(n)
    current_attacks = num_attacking_pairs(current_board)
    iterations = 0
    sideways_moves = 0
    
    while current_attacks > 0 and iterations < max_iterations:
        next_board, next_attacks = get_best_neighbor(current_board)
        
        if next_attacks < current_attacks:
            current_board = next_board
            current_attacks = next_attacks
            sideways_moves = 0  # reset sideways move count
        elif next_attacks == current_attacks and sideways_moves < max_sideways_moves:
            current_board = next_board
            sideways_moves += 1
        else:
            # If no improvement and no more sideways moves, restart
            current_board = generate_random_board(n)
            current_attacks = num_attacking_pairs(current_board)
            sideways_moves = 0
        
        iterations += 1
    
    if current_attacks == 0:
        print(f"Solucao encontrada para n = {n}: {current_board}")
    else:
        print(f"Nao foi encontrada solução para n = {n} depois de {max_iterations} iteracoes.")