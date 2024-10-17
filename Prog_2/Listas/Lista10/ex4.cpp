#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

using namespace std;

template <typename K, typename V>
class Mapa
{
private:
  map<K, V> mapa;

public:
  void adicionar(const K &chave, const V &valor)
  {
    mapa[chave] = valor;
  }

  V buscar(const K &chave) const
  {
    auto it = mapa.find(chave);
    if (it != mapa.end())
    {
      return it->second;
    }
    else
    {
      throw out_of_range("Chave não encontrada no mapa.");
    }
  }

  void listarChaves() const
  {
    cout << "Chaves no mapa:\n";
    for (const auto &par : mapa)
    {
      cout << par.first << '\n';
    }
  }
};

int main()
{
  Mapa<string, int> mapaStringInt;
  mapaStringInt.adicionar("Alice", 25);
  mapaStringInt.adicionar("Bob", 30);
  mapaStringInt.adicionar("Charlie", 22);

  cout << "Valor associado à chave 'Bob': " << mapaStringInt.buscar("Bob") << '\n';

  mapaStringInt.listarChaves();

  Mapa<int, string> mapaIntString;
  mapaIntString.adicionar(1, "Carro");
  mapaIntString.adicionar(2, "Moto");
  mapaIntString.adicionar(3, "Bicicleta");

  cout << "\nValor associado à chave 2: " << mapaIntString.buscar(2) << '\n';

  mapaIntString.listarChaves();

  return 0;
}
