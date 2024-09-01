import time
from hill_climbing import hill_climbing_n_queens
from simulated_annealing import simulated_annealing_n_queens
from genetic_algorithm import genetic_algorithm_n_queens

def main():
    n_values = [32, 64, 128]
    iterations = 50000

    for n in n_values:
        print(f"\n------ Resolvendo o problema das {n} rainhas ------")

        # Monitorando o tempo do Hill-Climbing
        # start_time = time.time()
        # print("\nMétodo: Hill-Climbing")
        # hill_climbing_n_queens(n, max_steps=iterations)
        # end_time = time.time() 
        # print(f"Tempo de execução: {end_time - start_time:.4f} segundos")

        # Monitorando o tempo do Simulated Annealing
        # temp = 100.0
        # cool = 0.95
        # start_time = time.time()
        # print("\nMétodo: Simulated Annealing")
        # simulated_annealing_n_queens(n,max_iterations=iterations, initial_temperature=temp, cooling_rate=cool)
        # end_time = time.time()
        # print(f"Tempo de execução: {end_time - start_time:.4f} segundos")

        # Monitorando o tempo do Algoritmo Genético
        start_time = time.time()
        print("\nMétodo: Algoritmo Genético")
        genetic_algorithm_n_queens(n,generations=iterations)
        end_time = time.time()
        print(f"Tempo de execução: {end_time - start_time:.4f} segundos")

if __name__ == "__main__":
    main()
