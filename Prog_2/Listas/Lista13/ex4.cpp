#include <iostream>
#include <set>

using namespace std;

int main()
{
  set<int> numeros = {2, 4, 6, 8, 10, 12};

  cout << "Valores iniciais do set: ";
  for (set<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;

  numeros.insert(8);

  cout << "Valores do set após tentar adicionar um valor duplicado: ";
  for (set<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}
