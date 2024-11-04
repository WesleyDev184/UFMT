#include <iostream>
#include <list>

using namespace std;

int main()
{
  list<int> numeros = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  cout << "Valores iniciais da lista: ";
  for (list<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;

  for (list<int>::iterator it = numeros.begin(); it != numeros.end();)
  {
    if (*it % 2 == 0)
    {
      it = numeros.erase(it);
    }
    else
    {
      ++it;
    }
  }

  cout << "Valores da lista após remoção dos pares: ";
  for (list<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}
