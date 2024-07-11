#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>   

using namespace std;

// Definição da estrutura do servidor
struct Servidor {
    string nome;
    int peso;
    int solicitacoes_atendidas;

    Servidor(string n, int p) : nome(n), peso(p), solicitacoes_atendidas(0) {}
};

// Função para implementar Round Robin
void roundRobin(vector<Servidor>& servidores, int num_requisicoes) {
    int num_servidores = servidores.size();
    int index = 0;

    for (int i = 0; i < num_requisicoes; ++i) {
        servidores[index].solicitacoes_atendidas++;
        index = (index + 1) % num_servidores;
    }
}

// Função para implementar Weighted Round Robin
void weightedRoundRobin(vector<Servidor>& servidores, int num_requisicoes) {
    int num_servidores = servidores.size();
    int total_pesos = 0;
    vector<int> pesos_acumulados(num_servidores);

    // Calculando pesos acumulados
    for (int i = 0; i < num_servidores; ++i) {
        total_pesos += servidores[i].peso;
        pesos_acumulados[i] = total_pesos;
    }

    // Distribuindo as requisições
    srand(time(nullptr)); // Inicializando a semente para gerar números aleatórios

    for (int i = 0; i < num_requisicoes; ++i) {
        int rnd = rand() % total_pesos;
        int selected_server = 0;

        // Encontrando o servidor selecionado
        for (int j = 0; j < num_servidores; ++j) {
            if (rnd < pesos_acumulados[j]) {
                selected_server = j;
                break;
            }
        }

        servidores[selected_server].solicitacoes_atendidas++;
    }
}

// Função para implementar a estratégia Random
void randomStrategy(vector<Servidor>& servidores, int num_requisicoes) {
    int num_servidores = servidores.size();

    srand(time(nullptr)); // Inicializando a semente para gerar números aleatórios

    for (int i = 0; i < num_requisicoes; ++i) {
        int rnd = rand() % num_servidores;
        servidores[rnd].solicitacoes_atendidas++;
    }
}

int main() {
    int num_servidores;
    cout << "Digite o número de servidores: ";
    cin >> num_servidores;

    vector<Servidor> servidores;
    servidores.reserve(num_servidores);

    // Entrada dos servidores
    for (int i = 0; i < num_servidores; ++i) {
        string nome;
        int peso;
        cout << "Nome do servidor " << i + 1 << ": ";
        cin >> nome;
        cout << "Peso do servidor " << i + 1 << ": ";
        cin >> peso;

        servidores.emplace_back(nome, peso);
    }

    int num_requisicoes;
    cout << "Digite o número de requisições a serem injetadas: ";
    cin >> num_requisicoes;

    // Executando as estratégias
    roundRobin(servidores, num_requisicoes);
    weightedRoundRobin(servidores, num_requisicoes);
    randomStrategy(servidores, num_requisicoes);

    // Exibindo o resultado
    cout << "\nResultado:\n";
    for (int i = 0; i < num_servidores; ++i) {
        cout << "Servidor " << servidores[i].nome << ":\n";
        cout << "  - Requisições atendidas (Round Robin): " << servidores[i].solicitacoes_atendidas << "\n";
        cout << "  - Requisições atendidas (Weighted Round Robin): " << servidores[i].solicitacoes_atendidas << "\n";
        cout << "  - Requisições atendidas (Random): " << servidores[i].solicitacoes_atendidas << "\n";
        cout << "\n";
    }

    return 0;
}
