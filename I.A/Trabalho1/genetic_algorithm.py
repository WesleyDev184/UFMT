import random

def genetic_algorithm_n_queens(n, population_size=100, generations=10000, mutation_rate=0.2):
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
    
    def crossover(parent1, parent2):
        crossover_point = random.randint(1, n - 2)
        child1 = parent1[:crossover_point] + parent2[crossover_point:]
        child2 = parent2[:crossover_point] + parent1[crossover_point:]
        return child1, child2
    
    def mutate(board):
        if random.random() < mutation_rate:
            board[random.randint(0, n - 1)] = random.randint(0, n - 1)
    
    population = [generate_random_board(n) for _ in range(population_size)]
    
    for generation in range(generations):
        population = sorted(population, key=lambda board: num_attacking_pairs(board))
        
        if num_attacking_pairs(population[0]) == 0:
            print(f"Solucao encontrada para n = {n}: {population[0]}")
            return
        
        new_population = []
        for _ in range(population_size // 2):
            parent1, parent2 = random.choices(population[:population_size // 2], k=2)
            child1, child2 = crossover(parent1, parent2)
            mutate(child1)
            mutate(child2)
            new_population.extend([child1, child2])
        
        population = new_population
    
    print(f"Nao foi encontrada solução para n = {n} depois de {generations} geracoes.")
