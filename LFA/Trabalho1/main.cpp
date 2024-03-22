#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Definição da estrutura de transição de estado
struct Transition
{
  int nextState;
  char input;
  int token; // Token associado à transição
};

// Definição da classe que representa a máquina de estados
class StateMachine
{
private:
  map<int, map<char, Transition>> transitions; // Mapa de transições de estado
  int currentState;

public:
  // Construtor
  StateMachine() : currentState(0) {}

  // Método para adicionar uma transição de estado
  void addTransition(int fromState, char input, int toState, int token)
  {
    transitions[fromState][input] = {toState, input, token};
  }

  // Método para carregar as transições de estado de um arquivo externo
  void loadTransitionsFromFile(const string &filename)
  {
    ifstream file(filename);
    if (file.is_open())
    {
      int fromState, toState, token;
      char input;
      while (file >> fromState >> input >> toState >> token)
      {
        addTransition(fromState, input, toState, token);
      }
      file.close();
    }
    else
    {
      cerr << "Erro ao abrir o arquivo." << endl;
    }
  }

  // Método para processar uma entrada
  void processInput(const string &input)
  {
    for (char c : input)
    {
      if (transitions[currentState].find(c) != transitions[currentState].end())
      {
        Transition transition = transitions[currentState][c];
        currentState = transition.nextState;
        cout << "Estado atual: " << currentState << " (Entrada: " << transition.input << ", Token: " << transition.token << ")" << endl;
      }
      else
      {
        cout << "Transição inválida para entrada '" << c << "' no estado " << currentState << endl;
        break;
      }
    }
  }

  void reset()
  {
    currentState = 0;
  }
};

int main()
{
  StateMachine machine;

  // Carregar as transições de estado de um arquivo externo
  machine.loadTransitionsFromFile("transitions.txt");

  // Processar algumas entradas de teste
  cout << "Processando entrada 'abba':\n";
  machine.processInput("abbabb");
  machine.reset();
  cout << "\nProcessando entrada 'aababbb':\n";
  machine.processInput("aababb");
  machine.reset();
  cout << "\nProcessando entrada 'bbaaabbbb':\n";
  machine.processInput("bbaaabb");

  return 0;
}
