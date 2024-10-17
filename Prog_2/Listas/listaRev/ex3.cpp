#include <iostream>
#include <stdexcept> // Para runtime_error

using namespace std;

// Função que realiza a divisão e trata o erro de divisão por zero
double dividir(int numerador, int denominador)
{
  if (denominador == 0)
  {
    throw runtime_error("Erro: Divisão por zero não permitida!");
  }
  return static_cast<double>(numerador) / denominador;
}

int main()
{
  int numerador, denominador;

  cout << "Digite o numerador: ";
  cin >> numerador;

  cout << "Digite o denominador: ";
  cin >> denominador;

  try
  {
    // Tenta realizar a divisão
    double resultado = dividir(numerador, denominador);
    cout << "Resultado: " << resultado << endl;
  }
  catch (const exception &e)
  {
    // Captura e exibe a mensagem de erro
    cerr << e.what() << endl;
  }

  return 0;
}
