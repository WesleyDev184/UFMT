#include <iostream>
#include <forward_list>

using namespace std;

forward_list<int>::iterator encontrarElemento(forward_list<int> &lista, int valor)
{
  for (auto it = lista.begin(); it != lista.end(); ++it)
  {
    if (*it == valor)
    {
      return it;
    }
  }
  return lista.end();
}

int main()
{
  forward_list<int> lista = {1, 2, 3, 4, 5};

  auto it = lista.begin();
  auto itAnterior = it;
  ++it;
  lista.erase_after(itAnterior);

  cout << "Elementos restantes na lista após a remoção do segundo elemento: ";
  for (const auto &elemento : lista)
  {
    cout << elemento << " ";
  }
  cout << endl;

  int valorParaBuscar = 3;
  auto resultado = encontrarElemento(lista, valorParaBuscar);

  if (resultado != lista.end())
  {
    cout << "Elemento " << valorParaBuscar << " encontrado na lista." << endl;
  }
  else
  {
    cout << "Elemento " << valorParaBuscar << " não encontrado na lista." << endl;
  }

  return 0;
}
