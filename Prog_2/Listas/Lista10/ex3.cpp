#include <iostream>
#include <string>
#include <functional>

using namespace std;

template <typename T>
class Item
{
private:
  string nome;
  T valor;

public:
  Item(const string &nome, T valor) : nome(nome), valor(valor) {}

  string getNome() const
  {
    return nome;
  }

  T getValor() const
  {
    return valor;
  }

  bool comparar(const Item<T> &outro) const
  {
    return less<T>()(valor, outro.getValor());
  }
};

int main()
{
  Item<int> item1("Item 1", 10);
  Item<int> item2("Item 2", 20);

  cout << "Comparando itens inteiros:\n";
  if (item1.comparar(item2))
  {
    cout << item1.getNome() << " tem um valor menor que " << item2.getNome() << '\n';
  }
  else
  {
    cout << item1.getNome() << " tem um valor maior ou igual a " << item2.getNome() << '\n';
  }

  Item<double> item3("Item 3", 15.5);
  Item<double> item4("Item 4", 10.2);

  cout << "\nComparando itens double:\n";
  if (item3.comparar(item4))
  {
    cout << item3.getNome() << " tem um valor menor que " << item4.getNome() << '\n';
  }
  else
  {
    cout << item3.getNome() << " tem um valor maior ou igual a " << item4.getNome() << '\n';
  }

  return 0;
}
