#include <iostream>
#include <queue>     
#include <stdexcept> 

using namespace std;

template <typename T>
class Fila
{
private:
  queue<T> fila;

public:
  void enfileirar(const T &valor)
  {
    fila.push(valor);
  }

  void desenfileirar()
  {
    if (estaVazia())
    {
      throw out_of_range("Fila está vazia. Não é possível desenfileirar.");
    }
    fila.pop();
  }

  bool estaVazia() const
  {
    return fila.empty();
  }

  T frente() const
  {
    if (estaVazia())
    {
      throw out_of_range("Fila está vazia. Não é possível acessar o elemento da frente.");
    }
    return fila.front();
  }
};

int main()
{
  Fila<int> filaInt;
  filaInt.enfileirar(10);
  filaInt.enfileirar(20);
  filaInt.enfileirar(30);

  cout << "Fila de int:\n";
  while (!filaInt.estaVazia())
  {
    cout << "Frente: " << filaInt.frente() << '\n';
    filaInt.desenfileirar();
  }

  Fila<string> filaString;
  filaString.enfileirar("Alice");
  filaString.enfileirar("Bob");
  filaString.enfileirar("Charlie");

  cout << "\nFila de string:\n";
  while (!filaString.estaVazia())
  {
    cout << "Frente: " << filaString.frente() << '\n';
    filaString.desenfileirar();
  }

  Fila<float> filaFloat;
  filaFloat.enfileirar(1.5f);
  filaFloat.enfileirar(2.3f);
  filaFloat.enfileirar(3.7f);

  cout << "\nFila de float:\n";
  while (!filaFloat.estaVazia())
  {
    cout << "Frente: " << filaFloat.frente() << '\n';
    filaFloat.desenfileirar();
  }

  return 0;
}
