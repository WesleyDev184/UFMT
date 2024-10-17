import numpy as np
import random
from typing import List, Tuple

def genetic_algorithm_n_queens(n: int, population_size: int = 100, generations: int = 10000, mutation_rate: float = 0.2) -> None:
    def generate_random_board(n: int) -> np.ndarray:
        return np.random.randint(0, n, size=n)
    
    def num_attacking_pairs(board: np.ndarray) -> int:
        row_conflicts = np.bincount(board)
        diag1_conflicts = np.bincount(np.arange(n) - board + (n - 1))
        diag2_conflicts = np.bincount(np.arange(n) + board)
        
        row_attacks = np.sum(row_conflicts * (row_conflicts - 1)) // 2
        diag1_attacks = np.sum(diag1_conflicts * (diag1_conflicts - 1)) // 2
        diag2_attacks = np.sum(diag2_conflicts * (diag2_conflicts - 1)) // 2
        
        return int(row_attacks + diag1_attacks + diag2_attacks)
    
    def crossover(parent1: np.ndarray, parent2: np.ndarray) -> Tuple[np.ndarray, np.ndarray]:
        crossover_point = random.randint(1, n - 2)
        child1 = np.concatenate((parent1[:crossover_point], parent2[crossover_point:]))
        child2 = np.concatenate((parent2[:crossover_point], parent1[crossover_point:]))
        return child1, child2
    
    def mutate(board: np.ndarray) -> None:
        if random.random() < mutation_rate:
            board[random.randint(0, n - 1)] = random.randint(0, n - 1)
    
    population: np.ndarray = np.array([generate_random_board(n) for _ in range(population_size)])
    current_attacks: int = num_attacking_pairs(population[0])
    iteracoes: int = 0
    
    for _ in range(generations):
        iteracoes += 1
        population = np.array(sorted(population, key=lambda board: num_attacking_pairs(board)))
        
        current_attacks = num_attacking_pairs(population[0])

        if current_attacks == 0:
            print(f"Solução encontrada para n = {n} com {iteracoes} iterações: Ataques: {current_attacks}")
            return
        
        new_population: List[np.ndarray] = []
        for _ in range(population_size // 2):
            parent1, parent2 = random.choices(population[:population_size // 2], k=2)
            child1, child2 = crossover(parent1, parent2)
            mutate(child1)
            mutate(child2)
            new_population.extend([child1, child2])
        
        population = np.array(new_population)
    
    print(f"Não foi encontrada solução para n = {n} após {iteracoes} iterações.")
    print(f"Melhor solução encontrada:Ataques: {current_attacks}")
