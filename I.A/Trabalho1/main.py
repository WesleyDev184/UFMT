import time
from typing import List
from hill_climbing import hill_climbing_n_queens
from simulated_annealing import simulated_annealing_n_queens
from genetic_algorithm import genetic_algorithm_n_queens

def main() -> None:
    n_values: List[int] = [32, 64, 128]
    iterations: int = 80000
    temp: float = 150.0
    cool: float = 0.97
    pop_size: int = 200
    mutation: float = 0.3

    # Executar 5 vezes para cada valor de n
    for n in n_values:
        print(f"\n------ Resolvendo o problema das {n} rainhas ------")
        
        # Hill Climbing
        print("Hill Climbing:\n")
        start_time = time.time()
        for i in range(5):
            print(f"Execução {i + 1}:")
            hill_climbing_n_queens(n, iterations)
            print()
        average_time_hc = (time.time() - start_time) / 5
        print(f"Tempo médio: {average_time_hc:.4f} segundos\n")

        # Simulated Annealing
        print("Simulated Annealing:\n")
        start_time = time.time()
        for ii in range(5):
            print(f"Execução {ii + 1}:")
            simulated_annealing_n_queens(n, iterations, temp, cool)
            print()
        average_time_sa = (time.time() - start_time) / 5
        print(f"Tempo médio: {average_time_sa:.4f} segundos\n")

        # Genetic Algorithm
        print("Genetic Algorithm:\n")
        start_time = time.time()
        for iii in range(5):
            print(f"Execução {iii + 1}:")
            genetic_algorithm_n_queens(n, pop_size, iterations, mutation)
            print()
        average_time_ga = (time.time() - start_time) / 5
        print(f"Tempo médio: {average_time_ga:.4f} segundos\n")

        # Análise do desempenho
        print(f"\nAnálise do desempenho para {n} rainhas:")
        print(f"Tempo médio Hill Climbing: {average_time_hc:.4f} segundos")
        print(f"Tempo médio Simulated Annealing: {average_time_sa:.4f} segundos")
        print(f"Tempo médio Genetic Algorithm: {average_time_ga:.4f} segundos")

        # Determina o algoritmo mais rápido
        fastest_algorithm = min(
            (average_time_hc, "Hill Climbing"),
            (average_time_sa, "Simulated Annealing"),
            (average_time_ga, "Genetic Algorithm")
        )
        print(f"O algoritmo mais rápido foi: {fastest_algorithm[1]} com tempo de {fastest_algorithm[0]:.4f} segundos")

        print()

if __name__ == "__main__":
    main()
